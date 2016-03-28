<?php
namespace I18n;

define("MAX_ATTEMPTS", 5);
define("MAX_TEMPLATES", 6);

class template_engine 
{
	private static $templates = null;

	public static function translate($original, $translation_hints = null) 
	{
		$trimmed_original = trim($original);
		$numbers = util::extract_numbers($trimmed_original);
		$translation = self::translate_whole_phrase($trimmed_original, $translation_hints);
		if ($translation) {
			$translation = util::restore_numbers($translation, $numbers);
		}
		else {
			$phrases = util::split_phrases($trimmed_original);
			$translations = array_map(function($phrase) use (&$numbers, $translation_hints) {
				return self::translate_phrase($phrase, $numbers, $translation_hints);
			}, $phrases);
			$translation = util::apply_translations($trimmed_original, $phrases, $translations);
		}
		$translation = util::preserve_space($original, $translation);
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

	private static function translate_phrase($phrase, &$numbers, $translation_hints = null) 
	{
		$translator_matches = self::get_translator_matches($phrase, $translation_hints);
		$template_match = self::get_template_match($translator_matches);
		/*
		var_dump(array_map(function ($tm) {
			return array_map(function ($t) {return $t->identifier;}, $tm->translators);
			}, $translator_matches));
		var_dump($template_match);
		*/
		//var_dump($template_match->templates[0], $template_match->translator_matches[1]->translator);
		if (!$template_match) {
			util::restore_numbers($phrase, $numbers);
			return $phrase;			
		}
		$template_match->apply_numbers($numbers);
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
		$is_first_in_phrase = true;
		$is_last_in_phrase = !$words;
		while (true) {
			if ($words)
				$fragment = implode(' ', $words);
			$translators = self::match_translator($fragment, $is_first_in_phrase, $is_last_in_phrase
				, $translation_hints);
			if ($translators) 
				return new translator_match($fragment, $translators);
			if ($words == null)
				$words = util::split_words($fragment);
			if (count($words) == 1)
				return new translator_match($fragment, array(new untranslated($fragment)));
			$remaining_words[] = array_shift($words);
			$is_first_in_phrase = false;
		}
	}

	private static function match_translator($fragment, $is_first_in_phrase, $is_last_in_phrase
		, $translation_hints) 
	{
		$candidates = translation_storage::get_translators(strtolower($fragment), $is_first_in_phrase, $is_last_in_phrase);
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

	private static function get_template_matches($translator_matches, $parent_candidate
		, $depth = 0, &$attempts = 0) 
	{
		$new_candidates = self::get_next_template_candidates($translator_matches, $parent_candidate);
		foreach ($new_candidates as $candidate) {
			if ($candidate->word_index == count($translator_matches) - 1) {
				$attempts++;
				$template_match = $candidate->match_complete($translator_matches);
				if ($template_match)
					yield $template_match;
			}
			else if ($depth < MAX_TEMPLATES){
				foreach (self::get_template_matches($translator_matches, $candidate
					, $depth + 1, $attempts) as $match)
					yield $match;
			}
			if ($attempts >= MAX_ATTEMPTS)
				break;					
		}
	}

	private static function get_next_template_candidates($translator_matches, $parent_candidate) 
	{
		$translator_count = count($translator_matches);
		$candidate_queue = self::get_base_template_candidates($parent_candidate
			, template_storage::get_templates(), $translator_count);
		while ($candidate_queue) {
			$next_candidate = array_shift($candidate_queue);
			if ($next_candidate->last_template_node->template) // leaf node
			{
				yield $next_candidate;									
			}
			else {
				if ($next_candidate->matches($translator_matches)) {
					$new_candidates = self::get_template_candidates($next_candidate
						, $next_candidate->last_template_node->children, $translator_count);
					self::add_template_candidates($new_candidates, $candidate_queue
						, $translator_count);
				}
				if ($next_candidate->is_potential_double_noun($translator_matches)) {
					$next_candidate->double_noun_indices[] = $next_candidate->word_index;
					$next_candidate->word_index++;
					array_unshift($candidate_queue, $next_candidate);
				}				
			}
		}
	}

	private static function print_candidates($candidates) 
	{
		foreach ($candidates as $candidate) {
			$node = $candidate->last_template_node;
			if ($node->template)
				echo 'T:' . $node->template->compact_form;
			else if ($node->word_form)
				echo 'W:' . $node->word_form->compact_form;
			echo '<br>';
		}
	}

	private static function get_base_template_candidates($parent_candidate, $new_template_nodes
		, $translator_count) 
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
		$candidates = array();
		foreach (array_reverse($new_template_nodes) as $template_node) {
			if ($template_node->min_length > $translator_count) continue;
			$new_candidate = new template_candidate($previous_template_nodes, $template_node
				, $word_index, $double_noun_indices);
			self::add_template_candidate($new_candidate, $candidates, $translator_count);
		}
		return $candidates;
	}

	private static function get_template_candidates($parent_candidate, $new_template_nodes
		, $translator_count) 
	{
		$previous_template_nodes = $parent_candidate->template_nodes;
		array_pop($previous_template_nodes);
		$parent_word_index = $parent_candidate->word_index;
		$double_noun_indices = $parent_candidate->double_noun_indices
			? $parent_candidate->double_noun_indices
			: array();
		$candidates = array();
		foreach ($new_template_nodes as $template_node) {
			if ($template_node->min_length > $translator_count) continue;
			$word_index = $template_node->template ? $parent_word_index : $parent_word_index + 1;
			$candidates[] = new template_candidate($previous_template_nodes, $template_node
				, $word_index, $double_noun_indices);
		}
		return $candidates;
	}

	private static function add_template_candidates($new_candidates, &$candidate_queue, $translator_count) 
	{
		foreach ($new_candidates as $new_candidate)
			self::add_template_candidate($new_candidate, $candidate_queue, $translator_count);
	}

	private static function add_template_candidate($new_candidate, &$candidate_queue
		, $translator_count) {
		$index = self::get_insertion_index($new_candidate, $candidate_queue, $translator_count);
		if ($index < 0) 
			$candidate_queue[] = $new_candidate;
		else 
			array_splice($candidate_queue, $index, 0, array($new_candidate));
	}

	private static function get_insertion_index($new_candidate, &$candidate_queue
		, $translator_count) {
		for ($index = 0; $index < count($candidate_queue); $index++) {
			$candidate = $candidate_queue[$index];
			if ($new_candidate->is_better_than($candidate, $translator_count))
				return $index;	
		}
		return -1;
	}
}
?>
