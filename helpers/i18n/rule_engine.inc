<?php
namespace I18n;

class rule_engine 
{
	public static function translate($original, $translation_hints = null) 
	{
		$trimmed_original = trim($original);
		$translation = self::translate_whole_phrase($trimmed_original, $translation_hints);
		if (!$translation) {
			$phrases = translation_helper::split_phrases($trimmed_original);
			$translations = array_map(function($phrase) use ($translation_hints){
				return self::translate_original_phrase($phrase, $translation_hints);
			}, $phrases);
			$translation = translation_helper::apply_translations($trimmed_original, $phrases, $translations);			
		}
		$translation = translation_helper::preserve_space($original, $translation);
		return $translation;
	}

	private static function translate_whole_phrase($original, $translation_hints) {
		$lower_phrase = strtolower($original);
		$translation = self::get_predefined_translation($lower_phrase, $translation_hints);
		if (!$translation)
			$translation = translation_storage::get_stored_translation($lower_phrase);
		return $translation ? translation_helper::preserve_case($translation, $original) : null;
	}

	private static function get_predefined_translation($lower_phrase, $translation_hints) 
	{
		$candidates = translation_storage::get_translators($lower_phrase, $translation_hints);
		$translation = $candidates 
			? self::try_select_translator($candidates, array(), array(), $translation_hints) 
			: null;
		return $translation 
			?  $translation->translate($lower_phrase, array(), array(), $translation_hints)
			: null;
	}

	private static function translate_original_phrase($phrase, $translation_hints)
	{
		$numbers = translation_helper::extract_numbers($phrase);
		$translation = self::translate_phrase($phrase, $numbers, $translation_hints);
		$translation = translation_helper::restore_numbers($translation, $numbers);
		$translation = translation_helper::preserve_case($translation, $phrase);
		return $translation;
	}

	private static function translate_phrase($phrase, $numbers, $translation_hints) 
	{
		$stored_translation = translation_storage::get_stored_translation(strtolower($phrase));
		$translated_phrase = $stored_translation 
			? $stored_translation
			: self::translate_unknown_phrase($phrase, $numbers, $translation_hints);
		return $translated_phrase;
	}

	private static function translate_unknown_phrase($phrase, $numbers, $translation_hints) 
	{
		$translation_matches = self::get_translation_matches($phrase, $numbers, $translation_hints);
		return count($translation_matches) == 1
			? $translation_matches[0]->translate(array(), array(), $translation_hints)
			: self::translate_new_phrase($phrase, $translation_matches, $translation_hints);
	}

	private static function translate_new_phrase($phrase, $translation_matches, $translation_hints) 
	{
		$localized_strings = self::get_translated_parts($translation_matches, $translation_hints);
		$translated_phrase = implode('', $localized_strings);
		if (count($localized_strings) > 1)
			translation_storage::store_translation($phrase, $translated_phrase);			
		return $translated_phrase;
	}

	private static function get_translation_matches($phrase, $numbers, $translation_hints) 
	{
		$translation_matches = self::get_candidates_matches($phrase);
		self::select_matches($translation_matches, $numbers, $translation_hints);
		return $translation_matches;
	}

	private static function get_candidates_matches($phrase) 
	{
		$candidates_matches = array();
		$remaining_words = null;
		do {
			$words = $remaining_words;
			$remaining_words = array();
			$candidates_match = self::get_candidates_match($phrase, $words, $remaining_words);
			array_unshift($candidates_matches, $candidates_match);
		}
		while (count($remaining_words));
		return $candidates_matches; 
	}

	private static function get_candidates_match($phrase, &$words, &$remaining_words) 
	{
		while (true) {
			if ($words)
				$phrase = implode(' ', $words);
			$candidates = self::match_phrase($phrase);
			if (is_array($candidates)) 
				return new translation_match($phrase, $candidates);
			if ($words == null)
				$words = translation_helper::split_words($phrase);
			if (count($words) == 1)
				return new translation_match($phrase, $candidates);
			$remaining_words[] = array_shift($words);
		}
	}

	private static function match_phrase($phrase) 
	{
		$candidates = translation_storage::get_translators(strtolower($phrase));
		return $candidates ? $candidates : new untranslated($phrase);
	}

	private static function select_matches(&$candidates_matches, $numbers, $translation_hints) {
		$previous_matches = array();
		$remaining_mathes = array_values($candidates_matches);
		while ($remaining_mathes) {
			$match = array_shift($remaining_mathes);
			$candidates = $match->translator;
			if (is_array($candidates)) {
				$translator = self::try_select_translator($candidates, $previous_matches, $remaining_mathes, $translation_hints);
				if ($numbers) 
					$match->phrase = translation_helper::restore_numbers($match->phrase, $numbers);
				$match->translator = $translator ? $translator : new untranslated($match->phrase);
				$previous_matches[] = $match;
			}
		}
	}

	private static function get_translated_parts($translation_matches, $translation_hints) 
	{
		$translators_after = array_map(function($match) {return $match->translator;}, $translation_matches);
		$translators_before = array();
		$localized_strings = array();
		foreach ($translation_matches as $match) {
			$translator = array_shift($translators_after);
			$localized_strings[] = $match->translate($translators_before, $translators_after, $translation_hints);
			$translators_before[] = $translator;
		}
		return $localized_strings;
	}

	private static function try_select_translator($candidates, $previous_matches, $following_matches, $translation_hints) {
		$strictness = 2;
		do $translator = self::select_translator($candidates, $previous_matches, $following_matches, $strictness, $translation_hints);
		while (!$translator && $strictness--);
		return $translator;
	}

	private static function select_translator($candidates, $previous_matches, $following_matches, $strictness, $translation_hints = null) {
		$with_selector = array();
		$without_selector = array();
		if ($strictness > 0 && $translation_hints)
			$candidates = self::filter_translator_candidates($candidates, $translation_hints);
		foreach ($candidates as $candidate)
			if ($candidate->identifier->selector)
				$with_selector[] = $candidate;
			else $without_selector[] = $candidate;
		foreach ($with_selector as $candidate)
			if ($candidate->match($previous_matches, $following_matches, $strictness > 1))
				return $candidate;
		foreach ($without_selector as $candidate)
			if ($candidate->match($previous_matches, $following_matches, $strictness > 1))
				return $candidate;
		return null;
	}

	private static function filter_translator_candidates($candidates, $translation_hints) {
		if (isset($translation_hints['class']))
			$candidates = array_filter($candidates, function ($translator) use ($translation_hints) {
				return $translator->identifier->class == $translation_hints['class'];
			});
		if (isset($translation_hints['form']))
			$candidates = array_filter($candidates, function ($translator) use ($translation_hints) {
				return $translator->identifier->form == $translation_hints['form'];
			});
		return $candidates;
	}
}
?>
