<?php
namespace I18n;

class engine 
{
	private static $translators = null;
	private static $stored_translators = array();

	public static function translate($original, $translation_hints = null) 
	{
		$trimmed_original = trim($original);
		$translation = self::translate_whole_phrase($original, $translation_hints);
		if (!$translation) {
			$phrases = preg_split('/\s*[.,;:!?&=()*]+\s*/', $trimmed_original, -1, PREG_SPLIT_NO_EMPTY);
			$translations = array_map(function($phrase) use ($translation_hints){
				return self::translate_original_phrase($phrase, $translation_hints);
			}, $phrases);
			$translation = self::apply_translations($trimmed_original, $phrases, $translations);			
		}
		$translation = self::preserve_space($original, $translation);
		return $translation;
	}

	private static function translate_whole_phrase($original, $translation_hints) {
		$lower_phrase = strtolower($original);
		$translation = self::get_predefined_translation($lower_phrase, $translation_hints);
		if (!$translation)
			$translation = self::get_stored_translation($lower_phrase);
		return $translation ? self::preserve_case($translation, $original) : null;
	}

	private static function get_predefined_translation($lower_phrase, $translation_hints) 
	{
		$candidates = self::get_translator_candidates($lower_phrase, $translation_hints);
		$translation = $candidates 
			? self::try_select_translator($candidates, array(), array(), $translation_hints) 
			: null;
		return $translation 
			?  $translation->translate($lower_phrase, array(), array(), $translation_hints)
			: null;
	}

	public static function apply_translations($original, $phrases, $translations) 
	{
		$translation = $original;
		for ($i = 0; $i < count($phrases); $i++)
			$translation = str_replace($phrases[$i], $translations[$i], $translation);
		return $translation;
	}

	private static function preserve_space($original, $translation) {
		preg_match('/^\s+/', $original, $leading_space_matches);
		preg_match('/\s+$/', $original, $trailing_space_mathes);
		$translation = ($leading_space_matches ? $leading_space_matches[0] : '') 
			. $translation 
			. ($trailing_space_mathes ? $trailing_space_mathes[0] : '');
		return $translation;
	}

	private static function translate_original_phrase($phrase, $translation_hints)
	{
		preg_match_all('/\d+/', $phrase, $matches);
		$numbers = $matches[0];
		if ($numbers) 
			$phrase = preg_replace('/\d+/', '%d', $phrase);
		$translation = self::translate_phrase($phrase, $numbers, $translation_hints);
		$translation = self::preserve_case($translation, $phrase);
		return $translation;
	}

	private static function preserve_case($target, $template) 
	{
		$ret_val = (ctype_upper($template[0]) 
				? strtoupper($target[0]) 
				: strtolower($target[0]))
		. substr($target, 1);
		return $ret_val;
	}		

	private static function translate_phrase($phrase, $numbers, $translation_hints) 
	{
		$stored_translation = self::get_stored_translation(strtolower($phrase));
		$translated_phrase = $stored_translation 
			? $stored_translation
			: self::translate_unknown_phrase($phrase, $numbers, $translation_hints);
		$translated_phrase = self::restore_numbers($translated_phrase, $numbers);
		return $translated_phrase;
	}

	private static function get_stored_translation($phrase_lower) 
	{
		return isset(self::$stored_translators[$phrase_lower]) 
			? self::$stored_translators[$phrase_lower]->translation
			: null;
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
			self::store_new_translation($phrase, $translated_phrase);			
		return $translated_phrase;
	}

	private static function get_translation_matches($phrase, $numbers, $translation_hints) 
	{
		$translation_matches = self::get_candidates_matches($phrase);
		self::select_matches($translation_matches, $numbers, $translation_hints);
		return $translation_matches;
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
					$match->phrase = self::restore_numbers($match->phrase, $numbers);
				$match->translator = $translator ? $translator : new untranslated($match->phrase);
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

	private static function store_new_translation($phrase, $translated_phrase) 
	{
		$key = strtolower($phrase);
		$translation = strtolower($translated_phrase);
		$identifier = translation_identifier::create($key);
		self::$stored_translators[$phrase] = new translator($identifier, $translation);
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
		$candidates = self::get_translator_candidates(strtolower($phrase));
		return $candidates ? $candidates : new untranslated($phrase);
	}

	private static function get_translator_candidates($phrase_lower) 
	{
		self::init_translations();
		return isset(self::$translators[$phrase_lower]) 
			? self::$translators[$phrase_lower]
			: array();
	}

	private static function init_translations() 
	{
		if (self::$translators == null)
			self::$translators = self::expand_all_translations();
	}

	private static function expand_all_translations() 
	{
		$translators = array();
		self::expand_translations($translators, \Thesaurus\phrases::create_translations());
		self::expand_translations($translators, \Thesaurus\modifiers::create_translations());
		self::expand_translations($translators, \Thesaurus\conjunctions::create_translations());
		self::expand_translations($translators, \Thesaurus\prepositions::create_translations());
		self::expand_translations($translators, \Thesaurus\pronouns::create_translations());
		self::expand_translations($translators, \Thesaurus\quantifiers::create_translations());
		self::expand_translations($translators, \Thesaurus\adjectives::create_translations());
		self::expand_translations($translators, \Thesaurus\verbs::create_translations());
		self::expand_translations($translators, \Thesaurus\nouns::create_translations());
		self::expand_translations($translators, \Thesaurus\time_and_date::create_translations());
		self::expand_translations($translators, \Thesaurus\names::create_translations());
		return $translators;
	}

	private static function expand_translations(&$translators, $compact_translations) 
	{
		foreach (array_keys($compact_translations) as $key)
			self::expand_translation($translators, $key, $compact_translations[$key]);
	}

	private static function expand_translation(&$translators, $identifier_str, $compact_translation) 
	{
		$identifier = translation_identifier::create($identifier_str);
		$new_translators = self::get_expanded_translations($identifier, $compact_translation);
		foreach ($new_translators as $translator)
			self::add_translator($translators, $translator);
	}

	private static function add_translator(&$translators, $translator) {
		$key = $translator->identifier->key;
		if (empty($translators[$key]))
			$translators[$key] = array($translator);
		else 
			$translators[$key][] = $translator;	
	}

	private static function get_expanded_translations($identifier, $compact_translation) 
	{
		$lang = controller::get_language();
		$translators = array();
		switch ($identifier->class) {
			case 'genitive':
			case 'indefinite':
			case 'phrase':
			case 'conj':
			case 'pron':
			case 'prep':
			case 'adverb':
				$translators[] = new translator($identifier, $compact_translation[$lang]);
				break;
			case 'quant':
				$translators[] = new quantifier($identifier, $compact_translation[$lang]);
				break;
			case 'pron-it':
				$translators[] = new pronoun_it($identifier, $compact_translation[$lang]);
				break;
			case 'pron-poss':
				$translators[] = new pronoun_possessive($identifier, $compact_translation[$lang]);
				break;
			case 'definite':
				$translators[] = new definite_marker($identifier, $compact_translation[$lang]);
				break;
			case 'adj':
				$adjective_indefinite = new adjective($identifier, $compact_translation[$lang]);
				$translators[] = $adjective_indefinite;
				if ($adjective_indefinite->has_definite_form)
					$translators[] = new adjective_definite($identifier->copy(), $compact_translation, $adjective_indefinite);
				break;
			case 'verb':
			case 'verb-aux':
				$verb_imperative = new verb_imperative($identifier, $compact_translation[$lang]);
				if ($verb_imperative->has_infinitive)
					$translators[] = new verb_infinitive($identifier->copy(), $compact_translation[$lang]);
				if ($verb_imperative->has_perfect)
					$translators[] = new verb_perfect($identifier->copy(), $compact_translation);
				if ($verb_imperative->has_present) {
					$present = new verb_present($identifier->copy(), $compact_translation);
					$translators[] = $present;
					if ($present->singular_key != $present->identifier->key)
						$translators[] = new verb_present_singular($identifier->copy($present->singular_key), $present->singular_translation);
					if ($present->participle_key != $present->identifier->key)
						$translators[] = new verb_present_participle($identifier->copy($present->participle_key), $present->participle_translation);
				}
				if ($verb_imperative->has_perfect_participle)
					$translators[] = new verb_perfect_participle($identifier->copy(), $compact_translation);
				$translators[] = $verb_imperative;
				break;
			case 'noun':
				$translators[] = new noun_singular($identifier->copy(null, new singular_noun_selector()), 
					$compact_translation[$lang]);
				$translators[] = new noun_plural($identifier->copy(null, new plural_noun_selector()), 
					$compact_translation);
				$translators[] = new noun_singular($identifier, $compact_translation[$lang]);
				$translators[] = new noun_plural(noun_plural::make_plural_identifier($identifier, $compact_translation), $compact_translation);
				break;
			default:
				throw new \Exception("Unknown word class: " . $identifier->class);
		}
		return $translators;
	}

	private function add_singular_noun_selector($identifier, $key) {
		$identifier->key = $key;
		$identifier->selector = new singular_noun_selector();
		return $identifier;
	}
}
?>
