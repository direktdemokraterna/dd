<?php
namespace I18n;

class template_candidate 
{
	public $template_nodes;
	public $last_template_node;
	public $word_index;
	public $template_count;
	public $double_noun_indices;
	public $priority;

	public function __construct($template_nodes, $word_index, $double_noun_indices) 
	{
		$this->template_nodes = $template_nodes;
		$this->template_count = count($template_nodes);
		$this->last_template_node = end($template_nodes);
		$this->word_index = $word_index;
		$this->double_noun_indices = $double_noun_indices;
		$this->priority = $this->last_template_node->best_priority - $word_index;
	}

	public function __toString() {
		$str = '';
		foreach ($this->template_nodes as $template_node) {
			if ($template_node->template)
				$str .= $template_node->template->compact_form;
			else 
				$str .= $template_node->word_form->compact_form;
			$str .= '|';
		}
		return $str . $this->priority;
	}

	public function matches($translator_matches) 
	{
		if (count($translator_matches) <= $this->word_index)
			return false;
		$translator_match = $translator_matches[$this->word_index];
		$word_form = $this->last_template_node->word_form;
		foreach ($translator_match->translators as $translator) 
			if ($word_form->matches($translator))
				return true;
		return false;
	}

	public function is_full_match($translator_matches) 
	{
		return $this->word_index == count($translator_matches) - 1;
	}

	public function match_complete($translator_matches) 
	{
		$templates = array_map(function ($template_node) {return $template_node->template;}, $this->template_nodes);
		$selected_translator_matches = self::select_translator_matches($translator_matches
			, $templates);
		return $selected_translator_matches
			? new template_match($templates, $selected_translator_matches, $this->double_noun_indices)
			: null;
	}

	public function select_translator_matches($translator_matches, $templates) 
	{
		$filtered_translator_matches = self::filter_translator_matches($translator_matches
			, $templates);
		if (!$filtered_translator_matches) return null;
		$alternative_translator_sequences = self::expand_translator_sequences($filtered_translator_matches);
		$selected_translator_sequense = self::select_translator_sequence($alternative_translator_sequences);
		if (!$selected_translator_sequense) return null;
		self::set_selected_translators($filtered_translator_matches, $selected_translator_sequense);
		return $filtered_translator_matches;
	}

	private function filter_translator_matches($translator_matches, $templates) 
	{
		$translator_index = 0;
		$filtered_translator_matches = null;
		foreach ($templates as $template) {
			$next_filtered_translator_matches = $template->filter_translator_matches(
				$translator_matches, $this->double_noun_indices, $translator_index);
			if (!$next_filtered_translator_matches) return null;
			$filtered_translator_matches = $filtered_translator_matches 
				? array_merge($filtered_translator_matches, $next_filtered_translator_matches)
				: $next_filtered_translator_matches;
		}
		return $filtered_translator_matches;
	}

	public function is_potential_double_noun($translator_matches) 
	{
		//echo 'is_potential_double_noun:<br>';
		//var_dump($this->word_index, count($translator_matches)
		//	, $this->last_template_node->word_form->class);
		return $this->word_index < count($translator_matches) - 1
			&& $this->last_template_node->word_form->class == 'noun'
			&& $translator_matches[$this->word_index]->is_potentially_first_of_double_noun();
	}

    private static function select_translator_sequence($matching_translator_sequences) 
    {
    	foreach ($matching_translator_sequences as $translators) 
    		if ($translators && self::match_selectors($translators))
    			return $translators;
    	return null;
    }

    private static function match_selectors($translators) 
    {
    	$previous_identifier = null;
    	$current_identifier = null;
    	foreach ($translators as $next_translator) {
    		if ($current_identifier 
    			&& !$current_identifier->match_selectors($previous_identifier
    				, $next_translator->identifier))
    			return false;
    		$previous_identifier = $current_identifier;
    		$current_identifier = $next_translator->identifier;
    	}
    	return $current_identifier->match_selectors($previous_identifier, null);
    }
	
	private static function expand_translator_sequences($translator_matches) 
	{
		if (!$translator_matches) return array();
		$first_translators = $translator_matches[0]->translators;
		$sequencies = count($translator_matches) == 1
			? array(array())
			: self::expand_translator_sequences(array_slice($translator_matches, 1));
		return self::combine_translator_sequences($first_translators, $sequencies);
	}

	private static function combine_translator_sequences($first_translators, $sequenses) 
	{
		foreach ($sequenses as $sequense)
			foreach ($first_translators as $first_translator) {
				$next_sequence = $sequense;
				array_unshift($next_sequence, $first_translator);
				yield $next_sequence;				
			}			
	}

	private static function set_selected_translators(&$translator_matches
		, $selected_translator_sequense) 
	{
		$index = 0;
		foreach ($translator_matches as $translator_match) {
			$translator_match->translators = null;
			$translator_match->translator = $selected_translator_sequense[$index++];			
		}
	}
}
?>
