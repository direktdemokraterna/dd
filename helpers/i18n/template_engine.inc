<?php
namespace I18n;

class template_engine 
{
	private static $templates = null;

	public static function translate($original, $translation_hints = null) 
	{
		$trimmed_original = trim($original);
		$numbers = translation_helper::extract_numbers($trimmed_original);
		$translation = self::translate_whole_phrase(strtolower($trimmed_original), $translation_hints);
		if (!$translation) {
			$phrases = translation_helper::split_phrases($trimmed_original);
			$translations = array_map(function($phrase) use ($translation_hints) {
				return self::translate_phrase($phrase, $translation_hints);
			}, $phrases);
			$translation = translation_helper::apply_translations($trimmed_original, $phrases, $translations);
		}
		$translation = translation_helper::restore_numbers($translation, $numbers);
		$translation = translation_helper::preserve_case($translation, $original);
		return $translation;
	}

	private static function translate_whole_phrase($lower_phrase) 
	{
		$candidates = translation_storage::get_phrase_translators($lower_phrase);
		foreach ($candidates as $candidate)
			if ($candidate->identifier->match_selectors(null, null))
				return $candidate->translate($lower_phrase, array(), array());
		return null;
	}

	private static function translate_phrase($phrase, $translation_hints = null) 
	{
		$translator_matches = self::get_translator_matches($phrase, $translation_hints);
		//var_dump($translator_matches[2]->translators);
		$template_match = self::get_best_template_match($translator_matches);
		return $template_match 
			? $template_match->translate($translation_hints) 
			: $phrase;
	}

	private static function get_translator_matches($phrase, $translation_hints = null) 
	{
		$translator_matches = array();
		$remaining_words = null;
		do {
			$words = $remaining_words;
			$remaining_words = array();
			$translator_match = self::get_next_translator_match($phrase, $words, $remaining_words, $translation_hints);
			array_unshift($translator_matches, $translator_match);
		}
		while (count($remaining_words));
		return $translator_matches; 
	}

	private static function get_next_translator_match($fragment, &$words, &$remaining_words, $translation_hints) 
	{
		while (true) {
			if ($words)
				$fragment = implode(' ', $words);
			$translators = self::match_translator($fragment, $translation_hints);
			if ($translators) 
				return new translator_match($fragment, $translators);
			if ($words == null)
				$words = translation_helper::split_words($fragment);
			if (count($words) == 1)
				return new translator_match($fragment, array(new untranslated($fragment)));
			$remaining_words[] = array_shift($words);
		}
	}

	private static function match_translator($fragment, $translation_hints = null) 
	{
		$candidates = translation_storage::get_translators(strtolower($fragment));
		if ($translation_hints && $candidates)
			$candidates = translation_storage::filter_translators($candidates, $translation_hints);
		return $candidates;
	}

	private static function get_best_template_match($translator_matches) 
	{
		$candidate_queue = self::get_template_candidates(template_storage::get_templates());
		while ($candidate_queue) {
			$next_candidate = array_shift($candidate_queue);
			if ($next_candidate->template_node->template) // leaf node
			{
				$next_candidate->word_index--;
				$template_match = $next_candidate->match_complete($translator_matches);
				if ($template_match)
					return $template_match;
				continue;			
			}
			if ($next_candidate->matches($translator_matches)) {
				$new_candidates = self::get_template_candidates($next_candidate->template_node->children, $next_candidate->word_index + 1, $next_candidate->double_noun_indices);
				foreach ($new_candidates as $new_candidate)
					self::add_template_candidate($new_candidate, $candidate_queue);
			}
			if ($next_candidate->is_potential_double_noun($translator_matches)) {
				$next_candidate->double_noun_indices[] = $next_candidate->word_index;
				$next_candidate->word_index++;
				array_unshift($candidate_queue, $next_candidate);
			}
		}
		return null;
	}

	private static function get_template_candidates($template_nodes, $word_index = 0, $double_noun_indices = null) 
	{
		return array_map(function($template_node) use ($word_index, $double_noun_indices) {
				return new template_candidate($template_node, $word_index
					, $double_noun_indices ? $double_noun_indices : array());
			}, $template_nodes);
	}

	private static function add_template_candidate($new_candidate, &$candidate_queue) {
		$index = self::get_insertion_index($new_candidate, $candidate_queue);
		if ($index < 0) 
			$candidate_queue[] = $new_candidate;
		else 
			array_splice($candidate_queue, $index, 0, array($new_candidate));
	}

	private static function get_insertion_index($new_candidate, &$candidate_queue) {
		for ($index = 0; $index < count($candidate_queue); $index++) {
			$candidate = $candidate_queue[$index];
			if ($candidate->template_node->best_priority > 
				$new_candidate->template_node->best_priority)
				return $index;	
		}
		return -1;
	}
}

class template_candidate 
{
	public $template_node;
	public $word_index;
	public $double_noun_indices;

	public function __construct($template_node, $word_index, $double_noun_indices) 
	{
		$this->template_node = $template_node;
		$this->word_index = $word_index;
		$this->double_noun_indices = $double_noun_indices;
	}

	public function matches($translator_matches) 
	{
		if (count($translator_matches) <= $this->word_index)
			return false;
		$translator_match = $translator_matches[$this->word_index];
		$word_form = $this->template_node->word_form;
		foreach ($translator_match->translators as $translator) 
			if ($word_form->matches($translator))
				return true;
		return false;
	}

	public function match_complete($translator_matches) 
	{
		if (!$this->is_full_match($translator_matches)) return null;
		$template = $this->template_node->template;
		$filtered_translator_matches = $template->filter_translator_matches($translator_matches
			, $this->double_noun_indices);
		if (!$filtered_translator_matches) return null;
		$alternative_translator_sequences = self::expand_translator_sequences($filtered_translator_matches);
		$selected_translator_sequense = $template->select_translator_sequence($alternative_translator_sequences);
		if (!$selected_translator_sequense) return null;
		self::convolute_translators($filtered_translator_matches
			, $selected_translator_sequense);
		return new template_match($this->template_node->template, $filtered_translator_matches
			, $this->double_noun_indices);
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
		foreach ($sequenses as $sequense) {
			foreach ($first_translators as $first_translator) {
				$next_sequence = $sequense;
				array_unshift($next_sequence, $first_translator);
				yield $next_sequence;				
			}			
		}
	}

	private static function convolute_translators(&$translator_matches, $selected_translator_sequense) 
	{
		$index = 0;
		foreach ($translator_matches as $translator_match) 
		{
			$translator_match->translators = null;
			$translator_match->translator = $selected_translator_sequense[$index++];			
		}
	}

	public function is_potential_double_noun($translator_matches) 
	{
		return $this->word_index < count($translator_matches) - 1
			&& $this->template_node->word_form->class == 'noun'
			&& $translator_matches[$this->word_index]->is_potentially_first_of_double_noun();
	}

	private function is_full_match($translator_matches) 
	{
		return $this->template_node->template && $this->word_index == count($translator_matches) - 1;
	}
}
?>
