<?php
namespace I18n;

class template
{
	public static $template_partial_counter = 0;
	public static $template_complete_counter = 0;

	public $priority;
	public $from_sequence;
	public $to_sequence;
	public $compact_form;

	public function __construct($priority, $from_sequence, $to_sequence, $compact_form) 
	{
		$this->priority = $priority;
		$this->from_sequence = $from_sequence;
		$this->to_sequence = $to_sequence;
		$this->compact_form = $compact_form;
	}

	public function __toString() {
        return $this->compact_form;
    }

    public function select_translator_sequence($matching_translator_sequences) 
    {
    	foreach ($matching_translator_sequences as $translators) 
    	{
    		if ($translators && $this->match_selectors($translators))
    			return $translators;    		
    	}
    }

    public function filter_translator_matches($translator_matches, $double_noun_indices) 
    {
    	$filtered_translator_matches = array();
    	$translator_index = 0;
    	foreach ($this->from_sequence as $word_form) {
    		if (in_array($translator_index, $double_noun_indices)){
	    		$translator_match = $translator_matches[$translator_index++];
	    		$filtered_match = self::filter_translator_match($translator_match
	    			, function($translator) {return $translator->identifier->is_noun_base_form();});
	    		if (!$filtered_match) return null;
				$filtered_translator_matches[] = $filtered_match;
    		}
    		$translator_match = $translator_matches[$translator_index++];
    		$filtered_match = self::filter_translator_match($translator_match
    			, function($translator) use ($word_form) {return $word_form->matches($translator);});
    		if (!$filtered_match) return null;
			$filtered_translator_matches[] = $filtered_match;
    	}
    	return $filtered_translator_matches;
    }

    public function filter_translator_match($translator_match, $predicate) 
    {
    	$filtered_translators = array();
    	foreach ($translator_match->translators as $translator)
			if ($predicate($translator))
    			$filtered_translators[] = $translator;
		return $filtered_translators
			? new translator_match($translator_match->phrase, $filtered_translators)
			: null;
    }

	public function get_translated_parts($translator_matches, $translation_hints = null
		, $double_noun_indices) 
	{
		$translators_after = array_map(function($match) {return $match->translator;}
			, $translator_matches);
		$translators_before = array();
		$localized_strings = array();
		$word_index = 0;
    	$translator_index = 0;
		foreach ($translator_matches as $match) {
			$translator = array_shift($translators_after);
			$hints = in_array($translator_index++, $double_noun_indices)
				? null
				: self::merge_hints($translation_hints, $word_index++);
			$localized_strings[] = $match->translate($translators_before, $translators_after, $hints);
			$translators_before[] = $translator;
		}
		return $localized_strings;
	}

	private function merge_hints($translation_hints, $word_index) 
	{
		$word_form = $this->from_sequence[$word_index];
		return $word_form->merge_hints($translation_hints);
	}

    private function match_selectors($translators) 
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
}

class word_form_match 
{
	public $word_form;
	public $word;

	public function __construct($word_form, $word) 
	{
		$this->word_form = $word_form;
		$this->word = $word;
	}
}
?>
