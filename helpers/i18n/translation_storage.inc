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
		//self::expand_translations($translators, \Thesaurus\phrases::create_translations());
		self::expand_translations($translators, \Thesaurus\new_phrases::create_translations());
		return $translators;
	}

	private static function expand_phrase_translations() 
	{
		$translators = array();
		self::expand_translations($translators, \Thesaurus\new_phrases::create_translations());
		//self::expand_translations($translators, \Thesaurus\phrases::create_translations());
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
			case 'verb-pass':
			case 'interjection':
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
				$imperative = new verb_imperative($identifier, $compact_translation[$lang]);
				$translators[] = $imperative;
				$infinitive = null;
				$perfect = null;
				if ($imperative->has_infinitive) {
					$infinitive = new verb_infinitive($identifier->copy(), $compact_translation[$lang]);					
					$translators[] = $infinitive;
				}
				if ($imperative->has_perfect){
					$perfect = new verb_perfect($identifier->copy(), $compact_translation);
					$translators[] = $perfect;
				}
				if ($imperative->has_preteritum) {
					$preteritum = new verb_preteritum($identifier->copy(), $compact_translation);
					$translators[] = $preteritum;
					if ($preteritum->singular_key)
						$translators[] = new verb_preteritum_singular($identifier->copy()
							, $preteritum->singular_key, $preteritum->translation);
				}
				if ($imperative->has_present) {
					$present = new verb_present($identifier->copy(), $compact_translation);
					$translators[] = $present;
					if ($present->singular_key != $present->identifier->key)
						$translators[] = new verb_present_singular($identifier->copy(
							array('key' => $present->singular_key))
							, $present->singular_translation);
					if ($present->participle_key != $present->identifier->key) {
						$translators[] = new verb_present_participle($identifier, $present
							, $infinitive);						
					}
				}
				if ($imperative->has_perfect_participle)
					$translators[] = new verb_perfect_participle($identifier->copy(), $compact_translation);
				if ($imperative->has_passive) {
					$translators[] = new verb_preteritum($identifier->copy(), $compact_translation,
						true);
					$translators[] = new verb_perfect($identifier->copy(), $compact_translation,
						true);
					if ($present->participle_key != $present->identifier->key) {
						$present_participle_passive = new verb_present_participle($identifier, $present
							, $infinitive, true);
						$translators[] = $present_participle_passive;
					}
					if ($infinitive && $present && $perfect) {
						$translators[] = new verb_present_passive($identifier, $infinitive
						, $present, $perfect);	
					}
				}
				break;
			case 'noun':
				$singular = noun_singular::create($identifier, $compact_translation[$lang]);
				$translators[] = $singular;
				$translators[] = $singular->make_genitive();
				if ($singular->has_plural) {
					$plural = noun_plural::create(noun_plural::make_plural_identifier($identifier, $compact_translation), $compact_translation);
					$singular->plural_translator = $plural;
					$translators[] = $plural;
					$translators[] = $plural->make_genitive();					
				}
				break;
			default:
				throw new \Exception("Unknown word class: " . $identifier->class);
		}
		return $translators;
	}
}

class genitive_translator
{
	public static function create_translations() {
		return array(
			"sv" => array("s", "'")
			,"en" => array("'s", "'")
		);
	}

	private static $is_initialized = false;
	private static $org1, $org2, $tran1, $tran2;
	private static $special_endings = array('s', 'x', 'z');

	private static function init() 
	{
		if (!self::$is_initialized) {
			$translations = self::create_translations();
			self::$org1 = $translations[BASE_LANG][0];
			self::$org2 = $translations[BASE_LANG][1];
			self::$tran1 = $translations[controller::get_language()][0];
			self::$tran2 = $translations[controller::get_language()][1];
			self::$is_initialized = true;
		}
	}

	public static function make_translated_gentitive(&$translation) 
	{
		self::init();
		$ending = self::get_translated_genitive_ending($translation);
		$translation .= $ending;
	}

	public static function make_original_gentitive(&$original) 
	{
		self::init();
		$ending = self::get_original_genitive_ending($original);
		$original .= $ending;
	}

	private static function get_translated_genitive_ending($translation) 
	{
		$last_character = self::get_last($translation);
		return in_array($last_character, self::$special_endings)
			? self::$tran2 : self::$tran1;
	}
	
	private static function get_original_genitive_ending($original) 
	{
		$last_character = self::get_last($original);
		return in_array($last_character, self::$special_endings)
			? self::$org2 : self::$org1;
	}
	
	private static function get_last($text) 
	{
		return strtolower(substr($text, strlen($text) - 1));
	}
}
?>
