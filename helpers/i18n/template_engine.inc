<?php
namespace I18n;

class template_engine 
{
	private static $templates = null;

	public static function translate($original, $translation_hints = null) 
	{
		$trimmed_original = trim($original);
		$numbers = util::extract_numbers($trimmed_original);
		$translation = self::translate_whole_phrase($trimmed_original, $translation_hints);
		if (!$translation) {
			$phrases = util::split_phrases($trimmed_original);
			$translations = array_map(function($phrase) use ($translation_hints) {
				return self::translate_phrase($phrase, $translation_hints);
			}, $phrases);
			$translation = util::apply_translations($trimmed_original, $phrases, $translations);
		}
		$translation = util::restore_numbers($translation, $numbers);
		return $translation;
	}

	private static function translate_whole_phrase($phrase) 
	{
		$lower_phrase = strtolower($phrase);
		$candidate = self::get_candidate_for_whole_phrase($lower_phrase);
		if (!$candidate) return null;
		$translation = $candidate->translate($lower_phrase, array(), array());
		$translation = util::preserve_case($translation, $phrase);
		return $translation;
	}

	private static function get_candidate_for_whole_phrase($lower_phrase) 
	{
		$candidates = translation_storage::get_phrase_translators($lower_phrase);
		foreach ($candidates as $candidate)
			if ($candidate->identifier->match_selectors(null, null))
				return $candidate;
		return null;
	}

	private static function translate_phrase($phrase, $translation_hints = null) 
	{
		$translator_matches = self::get_translator_matches($phrase, $translation_hints);
		$template_match = self::get_template_match($translator_matches);
		if (!$template_match)
			return $phrase;
		$translation = $template_match->translate($translation_hints);
		$translation = util::preserve_case($translation, $phrase);
		return $translation;
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
				$words = util::split_words($fragment);
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

	private static function get_template_match($translator_matches) 
	{
		foreach (self::get_template_matches($translator_matches, array()) as $match)
			return $match;
		return null;
	}

	private static function get_template_matches($translator_matches, $parent_candidate) 
	{
		//echo 'get_template_matches: <br>';
		//var_dump($translator_matches, $parent_candidate);
		$new_candidates = self::get_next_template_candidates($translator_matches, $parent_candidate);
		foreach ($new_candidates as $candidate) {
			//echo 'candidate: <br>';
			//var_dump($candidate);
			if ($candidate->word_index == count($translator_matches) - 1) {
				//echo 'found template match: <br>';
				$template_match = $candidate->match_complete($translator_matches);
				//var_dump($candidate, $template_match);
				if ($template_match)
					yield $template_match;				
			}
			else {
				//continue;
				foreach (self::get_template_matches($translator_matches, $candidate) as $match)
					yield $match;
			}
		}
	}

	private static function get_next_template_candidates($translator_matches, $parent_candidate) 
	{
		$candidate_queue = self::get_base_template_candidates($parent_candidate
			, template_storage::get_templates());
		while ($candidate_queue) {
			$next_candidate = array_shift($candidate_queue);
			if ($next_candidate->last_template_node->template) // leaf node
			{
				//echo 'template:<br>';
				//var_dump($next_candidate->last_template_node->template->compact_form
				//	, $next_candidate->double_noun_indices);
				yield $next_candidate;									
			}
			else {
				if ($next_candidate->matches($translator_matches)) {
					//echo 'word:<br>';
					//var_dump($next_candidate->last_template_node->word_form->compact_form);
					$new_candidates = self::get_template_candidates($next_candidate
						, $next_candidate->last_template_node->children);
					self::add_template_candidates($new_candidates, $candidate_queue, $next_candidate);
				}
				if ($next_candidate->is_potential_double_noun($translator_matches)) {
					$next_candidate->double_noun_indices[] = $next_candidate->word_index;
					$next_candidate->word_index++;
					//echo 'double noun:<br>';
					//var_dump($next_candidate);
					array_unshift($candidate_queue, $next_candidate);
					//var_dump($candidate_queue);
				}				
			}
		}
	}

	private static function get_base_template_candidates($parent_candidate, $new_template_nodes) 
	{
		$previous_template_nodes = $parent_candidate 
			? $parent_candidate->template_nodes
			: array();
		$word_index = $parent_candidate 
			? $parent_candidate->word_index + 1
			: 0;
		$double_noun_indices = $parent_candidate && $parent_candidate->double_noun_indices
			? $parent_candidate->double_noun_indices
			: array();
		return array_map(function($template_node) 
			use ($previous_template_nodes, $word_index, $double_noun_indices, $parent_candidate)
			{
				$template_nodes = $previous_template_nodes;
				$template_nodes[] = $template_node;
				return new template_candidate($template_nodes, $word_index, $double_noun_indices, $parent_candidate);
			}, $new_template_nodes);
	}

	private static function get_template_candidates($parent_candidate, $new_template_nodes) 
	{
		//echo 'next_candidate: ' . (string)$parent_candidate . '<br>';
		$previous_template_nodes = $parent_candidate->template_nodes;
		array_pop($previous_template_nodes);
		$parent_word_index = $parent_candidate->word_index;
		$double_noun_indices = $parent_candidate->double_noun_indices
			? $parent_candidate->double_noun_indices
			: array();
		//echo 'get_template_candidates<br>';
		//var_dump($parent_candidate, $double_noun_indices);
		return array_map(function($template_node) 
			use ($previous_template_nodes, $parent_word_index, $double_noun_indices, $parent_candidate) {
				$template_nodes = $previous_template_nodes;
				$template_nodes[] = $template_node;
				$word_index = $template_node->template ? $parent_word_index : $parent_word_index + 1;
				return new template_candidate($template_nodes, $word_index, $double_noun_indices, $parent_candidate);
			}, $new_template_nodes);
	}

	private static function add_template_candidates($new_candidates, &$candidate_queue) 
	{
		foreach ($new_candidates as $new_candidate)
			self::add_template_candidate($new_candidate, $candidate_queue);			
	}

	private static function add_template_candidate($new_candidate, &$candidate_queue) {
		$index = self::get_insertion_index($new_candidate, $candidate_queue);
		if ($index < 0) 
			$candidate_queue[] = $new_candidate;
		else 
			array_splice($candidate_queue, $index, 0, array($new_candidate));
	}

	private static function get_insertion_index($new_candidate, &$candidate_queue) {
		$priority = $new_candidate->priority;
		for ($index = 0; $index < count($candidate_queue); $index++) {
			$candidate = $candidate_queue[$index];
			if ($priority < $candidate->priority)
				return $index;	
		}
		return -1;
	}
}
?>
