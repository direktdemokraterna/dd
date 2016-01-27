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

		echo "word_form->matches: " . word_form::$word_form_counter++ . '<br>';
		echo "template->partial: " . template::$template_partial_counter++ . '<br>';
		echo "template->complete: " . template::$template_complete_counter++ . '<br>';

		return $translation;
	}

	private static function translate_whole_phrase($lower_phrase) 
	{
		$candidates = translation_storage::get_phrase_translators($lower_phrase);
		foreach ($candidates as $candidate)
			if ($candidate->identifier->match(array(), array()))
				return $candidate->translate($lower_phrase, array(), array());
		return null;
	}

	private static function translate_phrase($phrase, $translation_hints = null) 
	{
		$candidate_matches = self::get_candidate_matches($phrase, $translation_hints);
		echo "candidate_translators: " . count($candidate_matches) . '<br>';
		//var_dump(array_map(function($match){return $match->translator;}, $candidate_matches));
		$template_matches = self::match_translators_with_templates($candidate_matches);
		echo "candidate_templates1: " . count($template_matches) . '<br>';
		if ($template_matches)
			$template_matches = self::complete_match_templates($template_matches);
		echo "candidate_templates2: " . count($template_matches) . '<br>';
		echo '<br>';
		//var_dump($template_matches);
		if (!$template_matches) return $phrase;
		$template_match = self::select_best_template($template_matches);
		if (!$template_match) return $phrase;
		return $template_match->translate($translation_hints);
	}

	private static function get_candidate_matches($phrase, $translation_hints = null) 
	{
		$candidate_matches = array();
		$remaining_words = null;
		do {
			$words = $remaining_words;
			$remaining_words = array();
			$candidate_match = self::get_next_candidate_match($phrase, $words, $remaining_words, $translation_hints);
			array_unshift($candidate_matches, $candidate_match);
		}
		while (count($remaining_words));
		return $candidate_matches; 
	}

	private static function get_next_candidate_match($fragment, &$words, &$remaining_words, $translation_hints) 
	{
		while (true) {
			if ($words)
				$fragment = implode(' ', $words);
			$candidates = self::match_translator($fragment, $translation_hints);
			if ($candidates) 
				return new translation_match($fragment, $candidates);
			if ($words == null)
				$words = translation_helper::split_words($fragment);
			if (count($words) == 1)
				return new translation_match($fragment, array(new untranslated($fragment)));
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

	private static function match_translators_with_templates($phrase_translator_matches) 
	{
		$first_translator_match = array_shift($phrase_translator_matches);
		$first_translator_matches = $first_translator_match->split();
		if (!$phrase_translator_matches) 
			return array_map(function ($match) {
				return template_match::start($match);
			}, $first_translator_matches);
		$remainder_template_matches = self::match_translators_with_templates($phrase_translator_matches);
		return $remainder_template_matches
			? self::combine_matches($first_translator_matches, $remainder_template_matches)
			: null;
	}

	private static function combine_matches($translator_matches, $template_matches) 
	{
		$candidates = array();
		foreach ($translator_matches as $translator_match)
			foreach ($template_matches as $template_match) {
				$candidate = $template_match->prepend($translator_match);
				if ($candidate)
					$candidates[] = $candidate;						
			}
		return $candidates;
	}

	private static function complete_match_templates($candidates) 
	{
		foreach ($candidates as $candidate) 
			$candidate->match_complete();
		$unique_candidates = array_filter($candidates, function($match) {return $match->template;});
		return $unique_candidates;
		return array_unique($unique_candidates);
	}

	private static function select_best_template($candidates) 
	{
		$best_candidate = null;
		foreach ($candidates as $candidate) {
			if (!$best_candidate 
				|| $best_candidate->template->priority > $candidate->template->priority)
				$best_candidate = $candidate;
		}
		return $best_candidate;
	}
}
?>
