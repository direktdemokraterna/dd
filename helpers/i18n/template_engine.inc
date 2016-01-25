<?php
namespace I18n;

class template_engine 
{
	private static $templates = null;

	public static function translate($original, $translation_hints = null) 
	{
//		echo "translate: $original<br>";
		$trimmed_original = trim($original);
		$numbers = translation_helper::extract_numbers($trimmed_original);
		$translation = self::translate_whole_phrase(strtolower($trimmed_original), $translation_hints);
		//var_dump($translation);
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
		//var_dump($candidates);
		foreach ($candidates as $candidate)
			if ($candidate->identifier->match(array(), array()))
				return $candidate->translate($lower_phrase, array(), array());
		return null;
	}

	private static function translate_phrase($phrase, $translation_hints = null) 
	{
		$candidate_matches = self::get_candidate_matches($phrase, $translation_hints);
		//var_dump($candidate_matches[2]->translator);
		$template_matches = self::combine_candidate_matches($candidate_matches);
		if (!$template_matches) return $phrase;
		$template_match = self::select_best_template($template_matches);
		//var_dump($template_match->templates);
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

	private static function combine_candidate_matches($candidate_matches) 
	{
		$first_match = array_shift($candidate_matches);
		$first_matches = $first_match->split();
		if (!$candidate_matches) 
			return array_map(function ($match) {
				return template_match::start($match);
			}, $first_matches);
		$remainder_matches = self::combine_candidate_matches($candidate_matches);
		return $remainder_matches
			? self::combine_matches($first_matches, $remainder_matches)
			: null;
	}

	private static function combine_matches($first_matches, $remainder_matches) 
	{
		$candidates = array();
		foreach ($first_matches as $first_match)
			foreach ($remainder_matches as $remainder_match) {
				$candidate = $remainder_match->prepend($first_match);
				if ($candidate)
					$candidates[] = $candidate;						
			}
		return $candidates;
	}

	private static function select_best_template($candidates) 
	{
		$best_candidate = null;
		foreach ($candidates as $candidate) {
			$candidate->match_complete();
			if (!$candidate->templates) continue;
			if (!$best_candidate || 
				$best_candidate->templates[0]->priority > $candidate->templates[0]->priority)
				$best_candidate = $candidate;
		}
		return $best_candidate;
	}
}
?>
