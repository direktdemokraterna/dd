<?php
namespace I18n;

class engine 
{
	private static $translations = null;

	public static function translate($text) 
	{
		$phrases = preg_split('/\s*[[:punct:]]+\s*/', $text, -1, PREG_SPLIT_NO_EMPTY);
		$translations = array_map('self::translate_original_phrase', $phrases);
		for ($i = 0; $i < count($phrases); $i++)
			$text = str_replace($phrases[$i], $translations[$i], $text);
		return $text;
	}

	private static function translate_original_phrase($phrase) 
	{
		preg_match_all('/\d+/', $phrase, $matches);
		$numbers = $matches[0];
		if ($numbers) 
			$phrase = preg_replace('/\d+/', '%d', $phrase);
		return self::translate_phrase($phrase, $numbers);
	}

	private static function translate_phrase($phrase, $numbers) 
	{
		$translation_matches = self::get_translation_matches($phrase, $numbers);
		$translated_phrase = count($translation_matches) == 1
			? $translation_matches[0]->translate(array(), array())
			: self::translate_new_phrase($phrase, $translation_matches);
		$translated_phrase = self::restore_numbers($translated_phrase, $numbers);
		return $translated_phrase;
	}

	private static function translate_new_phrase($phrase, $translation_matches) 
	{
		$localized_strings = self::get_translated_parts($translation_matches);
		$translated_phrase = implode('', $localized_strings);
		self::store_new_translation($phrase, $translated_phrase);			
		return $translated_phrase;
	}

	private static function get_translation_matches($phrase, $numbers) 
	{
		$translation_matches = self::get_candidates_matches($phrase);
		self::select_matches($translation_matches, $numbers);
		return $translation_matches;
	}

	private static function select_matches(&$candidates_matches, $numbers) {
		$previous_matches = array();
		foreach (array_keys($candidates_matches) as $key) {
			$match = $candidates_matches[$key];
			$candidates = $match->translation;
			if (is_array($candidates)) {
				$match->translation = count($candidates) > 1
					? self::select_translation($candidates, $previous_matches)
					: $candidates[0];
				if ($numbers) 
					$match->phrase = self::restore_numbers($match->phrase, $numbers);
				$previous_matches[] = $match;
			}
		}
	}

	private static function restore_numbers($phrase, &$numbers) {
		$old_phrase = null;
		while ($numbers) {
			$old_phrase = $phrase;
			$replace_count;
			$phrase = preg_replace('/%d/', $numbers[0], $phrase, 1, $replace_count);
			if ($replace_count == 0) break;
			array_shift($numbers);
		}
		return $phrase;
	}

	private static function get_translated_parts($translation_matches) 
	{
		$translations_after = array_map(function($match) {return $match->translation;}, $translation_matches);
		$translations_before = array();
		$localized_strings = array();
		foreach ($translation_matches as $match) {
			$translation = array_shift($translations_after);
			$localized_strings[] = $match->translate($translations_before, $translations_after);
			$translations_before[] = $translation;
		}
		return $localized_strings;
	}

	private static function store_new_translation($phrase, $translated_phrase) 
	{
		$key = strtolower($phrase);
		$translation = strtolower($translated_phrase);
		$identifier = translation_identifier::create($key);
		self::add_translation(self::$translations, new translator($identifier, $translation));
	}

	private static function select_translation($candidates, $previous_matches) {
		foreach ($candidates as $candidate)
			if ($candidate->identifier->match($previous_matches))
				return $candidate;
		return null;
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
				$words = preg_split('/\s+/', $phrase, 0, PREG_SPLIT_NO_EMPTY);
			if (count($words) == 1)
				return new translation_match($phrase, $candidates);
			$remaining_words[] = array_shift($words);
		}
	}

	private static function match_phrase($phrase) 
	{
		$candidates = self::get_translation_candidates(strtolower($phrase));
		return $candidates ? $candidates : new untranslated($phrase);
	}

	private static function get_translation_candidates($phrase_lower) 
	{
		self::init_translations();
		return isset(self::$translations[$phrase_lower]) 
			? self::$translations[$phrase_lower]
			: null;
	}

	private static function init_translations() 
	{
		if (self::$translations == null)
			self::$translations = self::expand_translations(translations::create_translations());
	}

	private static function expand_translations($compact_translations) 
	{
		$translations = array();
		foreach (array_keys($compact_translations) as $key)
			self::expand_translation($translations, $key, $compact_translations[$key]);
		return $translations;
	}

	private static function expand_translation(&$translations, $identifier_str, $compact_translation) 
	{
		$identifier = translation_identifier::create($identifier_str);
		$new_translations = self::get_expanded_translations($identifier, $compact_translation);
		foreach ($new_translations as $translation)
			self::add_translation($translations, $translation);
	}

	private static function add_translation(&$translations, $translation) {
		$key = $translation->identifier->key;
		if (empty($translations[$key]))
			$translations[$key] = array($translation);
		else 
			$translations[$key][] = $translation;	
	}

	private static function get_expanded_translations($identifier, $compact_translation) 
	{
		switch ($identifier->class) {
			case 'phrase':
				yield new translator($identifier, $compact_translation[LANG]);
				break;
			case 'adj':
				$adjective_indefinite = new adjective($identifier, $compact_translation[LANG]);
				yield $adjective_indefinite;
				if ($adjective_indefinite->has_definite_form)
					yield new adjective_definite($identifier, $compact_translation, $adjective_indefinite);
				break;
			case 'noun':
				yield new noun_singular($identifier->copy($identifier->key, new singular_noun_selector()), 
					$compact_translation[LANG]);
				yield new noun_plural($identifier->copy($identifier->key, new plural_noun_selector()), 
					$compact_translation);
				yield new noun_singular($identifier, $compact_translation[LANG]);
				yield new noun_plural($identifier->copy(null), $compact_translation);
				break;
			case 'verb':
				$verb_infinitive = new verb_infinitive($identifier, $compact_translation[LANG]);
				yield $verb_infinitive;
				if ($verb_infinitive->has_perfect_participle)
					yield new verb_perfect_participle($identifier, $compact_translation);
				if ($verb_infinitive->has_perfect)
					yield new verb_perfect($identifier, $compact_translation);
				break;
			default:
				throw new Exception("Unknown word class: " . $word_type);
		}
	}

	private function add_singular_noun_selector($identifier, $key) {
		$identifier->key = $key;
		$identifier->selector = new singular_noun_selector();
		return $identifier;
	}
}

class untranslated 
{
	public $phrase;

	function construct($phrase) 
	{
		$this->phrase = $phrase;
	}

	public function translate($lower_phrase, $translations_before, $translations_after) 
	{
		return $this->phrase;
	}
}
?>
