<?php
namespace I18n;

class verb_imperative extends translator 
{
	public $has_infinitive;
	public $has_present;
	public $has_preteritum;
	public $has_perfect;
	public $has_perfect_participle;
	public $has_passive;

	function __construct($identifier, $compact_translation) 
	{
		$identifier->tempus = 'imperative';
		$identifier->passive = false;
		$words = explode(' ', $compact_translation, 2);
		$parts = util::split_word_forms($words[0]);
		$translation = $parts[0];
		if (count($words) == 2)
			$translation .= ' ' . $words[1];
		parent::__construct($identifier, $translation);
		self::set_form_availability(count($parts));
	}

	private function set_form_availability($part_count) 
	{
		$this->has_infinitive = $part_count > 1;
		$this->has_present = $part_count > 2;
		$this->has_preteritum = $part_count > 3;
		$this->has_perfect = $part_count > 4;
		$this->has_perfect_participle = $part_count > 5;
		$this->has_passive = $part_count > 6;
	}
}

class verb_infinitive extends translator 
{
	function __construct($identifier, $compact_translation) 
	{
		$identifier->tempus = 'infinitive';
		$words = explode(' ', $compact_translation, 2);
		$parts = util::split_word_forms($words[0]);
		$translation = parent::assemble_word_form($parts, 1);
		if (count($words) == 2)
			$translation .= ' ' . $words[1];
		parent::__construct($identifier, $translation);
	}
}

class verb_present extends translator 
{
	public $singular_key;
	public $singular_translation;
	public $participle_key;
	public $participle_translation;
	public $passive_translation_ending;

	function __construct($identifier, $compact_forms) 
	{
		$keys = self::get_word_forms($compact_forms[BASE_LANG]);
		$compact_translation = $compact_forms[controller::get_language()];
		$translations = self::get_word_forms($compact_translation);
		$identifier->tempus = 'present';
		$identifier->key = $keys[0];
		parent::__construct($identifier, $translations[0]);
		$this->singular_key = $keys[1];
		$this->singular_translation = $translations[1];
		$this->participle_key = $keys[2];
		$this->participle_translation = $translations[2];
		if (count($translations) > 3)
			$this->passive_translation_ending = $translations[3];
	}

	protected static function get_word_forms($compact_translation) 
	{
		$words = explode(' ', $compact_translation, 2);
		$parts = util::split_word_forms($words[0]);
		$word = parent::assemble_word_form($parts, 2);
		$alternatives = self::extract_alternatives($word);
		if (count($words) == 2)
			$alternatives = array_map(function ($alt) use ($words) {return $alt . ' ' . $words[1];}
				, $alternatives);
		if (count($parts) > 6)
			$alternatives[] = $parts[6];
		return $alternatives;
	}

	private static function extract_alternatives($compact_forms) 
	{
		$alternatives = array();
		$parts = explode('|', $compact_forms, 3);
		$alternatives[] = $parts[0];
		for ($i = 1; $i < 3; $i++)
			$alternatives[] = ($i < count($parts) 
				? self::assemble_word_form($parts, $i) 
				: $parts[0]);
		return $alternatives;
	}

	public function translate($lower_phrase, $translations_before, $translations_after, $translation_hints = null) 
	{
		if ($this->singular_translation) {
			$subject = self::get_subject($translations_before);
			if ($subject && $subject->identifier->numerus == 'singular')
				return $this->singular_translation;
		}
		return parent::translate($lower_phrase, $translations_before, $translations_after, $translation_hints);
	}

	private static function get_subject($translators_before) 
	{
		foreach (array_reverse($translators_before) as $translator) {
			if (self::is_subject($translator)) 
				return $translator;
			if ($translator->identifier->key != 'who')
				break;			
		}
		return null;
	}

	private static function is_subject($translator) 
	{
		return $translator->is_noun() || $translator->is_pronoun();
	}
}

class verb_present_passive extends translator 
{
	function __construct($identifier, $infinitive, $present, $perfect) 
	{
		$words = explode(' ', $infinitive->translation, 2);
		$translation = self::create_word_form($words[0], $present->passive_translation_ending);
		if (count($words) > 1)
			$translation .= ' ' . $words[1];
		parent::__construct($identifier->copy(array(
			'key' => $perfect->identifier->key
			,'tempus' => 'present'
			,'passive' => true)), $translation);
	}
}

class verb_present_singular extends translator 
{
	function __construct($identifier, $translation) 
	{
		$identifier->tempus = 'present';
		$identifier->numerus = 'singular';
		parent::__construct($identifier, $translation);
	}
}

class verb_present_participle extends translator 
{
	private $base_translation;

	function __construct($identifier, $present, $infinitive, $passive = false) 
	{
		$this->base_translation = $infinitive->translation;
		$translation = $passive
			? self::create_word_form($this->base_translation, $present->passive_translation_ending)
			: $present->participle_translation;
		$identifier = $present->identifier->copy(array(
			'key' => $present->participle_key
			,'tempus' => 'present_participle'
			,'passive' => $passive));
		parent::__construct($identifier, $translation);
	}

	public function translate($lower_phrase, $translations_before, $translations_after, $translation_hints = null) 
	{
		return $translations_before && end($translations_before)->is_verb()
			? $this->base_translation
			: parent::translate($lower_phrase, $translations_before, $translations_after, $translation_hints);
	}
}

class verb_preteritum extends translator 
{
	public $singular_key;

	function __construct($identifier, $compact_forms, $passive = false) 
	{
		$key = self::generate_word($compact_forms[BASE_LANG], 3, $passive, 6);
		$parts = explode('|', $key);
		if (count($parts) > 1) {
			$key = $parts[0];
			$this->singular_key = self::create_word_form($key, $parts[1]);
		}
		$translation = self::generate_word($compact_forms[controller::get_language()], 3, $passive, 6);
		parent::__construct($identifier->copy(array(
			'key' => $key
			,'tempus' => 'preteritum'
			,'numerus' => $this->singular_key ? 'plural' : null
			,'passive' => $passive)), $translation);
	}
}

class verb_preteritum_singular extends translator 
{
	function __construct($identifier, $key, $translation) 
	{
		parent::__construct($identifier->copy(array(
			'key' => $key
			,'tempus' => 'preteritum'
			,'numerus' => 'singular')), $translation);
	}
}

class verb_perfect extends translator 
{
	function __construct($identifier, $compact_forms, $passive = false) 
	{
		$key = self::generate_word($compact_forms[BASE_LANG], 4, $passive, 6);
		$translation = self::generate_word($compact_forms[controller::get_language()], 4, $passive, 6);
		parent::__construct($identifier->copy(array(
			'key' => $key
			,'tempus' => 'perfect'
			,'passive' => $passive)), $translation);
	}
}

class verb_perfect_participle extends adjective
{
	function __construct($identifier, $compact_translation_pair) 
	{
		$adjective_key = self::assemble_word_form(util::split_word_forms($compact_translation_pair[BASE_LANG]), 5);
		$adjective_compact_translation = self::make_adjective_compact_translation($compact_translation_pair[controller::get_language()]);
		parent::__construct(new translation_identifier($adjective_key, 'adj'),
			$adjective_compact_translation);
	}

	private static function make_adjective_compact_translation($verb_compact_translation) 
	{
		$verb_base_form_and_endings = util::split_word_forms($verb_compact_translation);
		$verb_base_form = $verb_base_form_and_endings[0];
		$perfect_participle_endings = $verb_base_form_and_endings[5];
		$adjective_compact_translation = parent::create_word_form($verb_base_form, $perfect_participle_endings);
		return $adjective_compact_translation;
	}
}
?>
