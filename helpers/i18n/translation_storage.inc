<?php
namespace I18n;

class translation_storage 
{
	private static $translators = null;
	private static $phrase_translators = null;
	private static $stored_translators = array();

	public static function get_stored_translation($phrase_lower) 
	{
		return isset(self::$stored_translators[$phrase_lower]) 
			? self::$stored_translators[$phrase_lower]->translation
			: null;
	}

	public static function get_translators($phrase_lower) 
	{
		self::init_translations();
		return isset(self::$translators[$phrase_lower]) 
			? self::$translators[$phrase_lower]
			: array();
	}

	public static function get_phrase_translators($phrase_lower) 
	{
		self::init_translations();
		return isset(self::$phrase_translators[$phrase_lower]) 
			? self::$phrase_translators[$phrase_lower]
			: array();
	}

	public static function store_translation($phrase, $translated_phrase) 
	{
		$key = strtolower($phrase);
		$translation = strtolower($translated_phrase);
		$identifier = translation_identifier::create($key);
		self::$stored_translators[$phrase] = new translator($identifier, $translation);
	}

	public static function filter_translators($translators, $translation_hints) {
		//var_dump($translators);
		if (isset($translation_hints['class']))
			$translators = array_filter($translators, function ($translator) use ($translation_hints) {
				return $translator->identifier->class == $translation_hints['class'];
			});
		if (isset($translation_hints['numerus']))
			$translators = array_filter($translators, function ($translator) use ($translation_hints) {
				return !$translator->identifier->numerus 
					|| $translator->identifier->numerus == $translation_hints['numerus'];
			});
		if (isset($translation_hints['tempus']))
			$translators = array_filter($translators, function ($translator) use ($translation_hints) {
				return !$translator->identifier->tempus 
					|| $translator->identifier->tempus == $translation_hints['tempus'];
			});
		//var_dump($translators);
		return $translators;
	}

	private static function init_translations() 
	{
		if (self::$translators == null) {
			self::$translators = self::expand_all_translations();
			self::$phrase_translators = self::expand_phrase_translations();			
		}
	}

	private static function expand_all_translations() 
	{
		$translators = array();
		self::expand_translations($translators, \Thesaurus\modifiers::create_translations());
		self::expand_translations($translators, \Thesaurus\conjunctions::create_translations());
		self::expand_translations($translators, \Thesaurus\interjections::create_translations());
		self::expand_translations($translators, \Thesaurus\prepositions::create_translations());
		self::expand_translations($translators, \Thesaurus\pronouns::create_translations());
		self::expand_translations($translators, \Thesaurus\quantifiers::create_translations());
		self::expand_translations($translators, \Thesaurus\adjectives::create_translations());
		self::expand_translations($translators, \Thesaurus\verbs::create_translations());
		self::expand_translations($translators, \Thesaurus\nouns::create_translations());
		self::expand_translations($translators, \Thesaurus\time_and_date::create_translations());
		self::expand_translations($translators, \Thesaurus\names::create_translations());
		self::expand_translations($translators, \Thesaurus\abbreviations::create_translations());
		self::expand_translations($translators, \Thesaurus\adverbs::create_translations());
		self::expand_translations($translators, \Thesaurus\new_phrases::create_translations());
		return $translators;
	}

	private static function expand_phrase_translations() 
	{
		$translators = array();
		self::expand_translations($translators, \Thesaurus\new_phrases::create_translations());
		self::expand_translations($translators, \Thesaurus\phrases::create_translations());
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
						$translators[] = new verb_present_singular($identifier->copy(
							array('key' => $present->singular_key))
							, $present->singular_translation);
					if ($present->participle_key != $present->identifier->key)
						$translators[] = new verb_present_participle($identifier->copy(
							array('key' => $present->participle_key))
							, $present->participle_translation);
				}
				if ($verb_imperative->has_perfect_participle)
					$translators[] = new verb_perfect_participle($identifier->copy(), $compact_translation);
				$translators[] = $verb_imperative;
				break;
			case 'noun':
				$translators[] = new noun_singular($identifier->copy(array('selector' => new singular_noun_selector())), 
					$compact_translation[$lang]);
				$translators[] = new noun_plural($identifier->copy(array('selector' => new plural_noun_selector())), 
					$compact_translation);
				$translators[] = new noun_singular($identifier, $compact_translation[$lang]);
				$translators[] = new noun_plural(noun_plural::make_plural_identifier($identifier, $compact_translation), $compact_translation);
				break;
			default:
				throw new \Exception("Unknown word class: " . $identifier->class);
		}
		return $translators;
	}
}
?>
