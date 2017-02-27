<?php
namespace I18n;

class noun_modifier extends translator 
{
	private $translation_noun2;
	private $translation_plural;

	function __construct($identifier, $compact_translation) 
	{
		$forms = self::create_word_forms($compact_translation);
		parent::__construct($identifier, $forms[0]);
		$this->translation_plural = $forms[1];
		$this->translation_noun2 = $forms[2];
	}

	private static function create_word_forms($compact_translation) 
	{
		$word_parts = explode(' ', $compact_translation, 2);
		$form_parts = util::split_word_forms($word_parts[0]);
		$type_parts = explode('|', $form_parts[0]);
		$singular = $type_parts[0];
		$forms = array($singular
			,count($form_parts) > 1
				? parent::create_word_form($singular, $form_parts[1])
				: $singular
			,count($type_parts) > 1
				? parent::create_word_form($singular, $type_parts[1])
				: $singular);
		if (count($word_parts) > 1) {
			$endings = self::create_word_forms($word_parts[1]);
			for ($i = 0; $i < 3; $i++)
				$forms[$i] .= ' ' . $endings[$i];
		}
		return $forms;
	}

	public function translate($lower_phrase, $translations_before, $translations_after
		, $translation_hints = null) 
	{
		if ($translation_hints && isset($translation_hints['numerus']) && $translation_hints['numerus'] == 'plural')
			return $this->translation_plural;
		$has_plurifying_pronoun = $this->has_plurifying_pronoun($translations_before);
		if ($has_plurifying_pronoun)
			return $this->translation_plural;
		$significant_noun = $this->get_significant_noun($translations_before, $translations_after);
		return $significant_noun
			? self::get_translation_for_noun($significant_noun->identifier)
			: $this->translation;
	}

	private function has_plurifying_pronoun($translations_before) 
	{
		foreach (array_reverse($translations_before) as $translation) {
			if ($translation->identifier->key == 'this' 
				|| $translation->identifier->class == 'definite'
				|| $translation->identifier->class == 'pron-poss')
				return true;
			if (!$translation->is_noun_modifier()) break;
		}
		return false;
	}

	protected function get_translation_for_noun($noun_identifier) 
	{
		switch ($noun_identifier->numerus) {
			case 'plural':
				if ($this->identifier->numerus != 'singular')
					return $this->translation_plural;
			case 'singular':
				switch ($noun_identifier->type) {
					case 1:
						return $this->translation;
					case 2:
						return $this->translation_noun2;
					default:
						throw new \Exception('Invalid noun type: ' . $noun_identifier->type);
				}
			default:
				throw new \Exception('Invalid numerus: ' . $noun_identifier->numerus);
		}
	}
	
	protected function get_significant_noun($translations_before, $translations_after) 
	{
		$found_noun = null;
		foreach ($translations_after as $translation) {
			if ($translation->is_noun())
				$found_noun = $translation;				
			else if ($found_noun || !($translation->is_conjunction() 
				|| $translation->is_noun_modifier())) break;
		}
		return $found_noun;
	}
}

class quantifier extends noun_modifier 
{
	function __construct($identifier, $compact_translation) 
	{
		parent::__construct($identifier, $compact_translation);
		if (self::is_one($identifier->key))
			$identifier->numerus = 'singular';
	}

	public function translate($lower_phrase, $translations_before, $translations_after
		, $translation_hints = null) 
	{
		return $this->translation;
	}

	private static function is_one($quantifier) 
	{
		return in_array($quantifier, array("1", "a", "an", "one"));
	}	
}

class definite_marker extends noun_modifier 
{
}
?>
