<?php
namespace I18n;

class adjective extends translator
{
	public $translation_noun2;
	public $translation_plural;
	public $has_definite_form;

	function __construct($identifier, $compact_translation) 
	{
		$parts = explode(':', $compact_translation);
		$singular_parts = explode('|', $parts[0]);
		$singular = $singular_parts[0];
		parent::__construct($identifier, $singular);
		$this->translation_plural = count($parts) > 1
			? parent::create_word_form($singular, $parts[1])
			: $singular;
		$this->has_definite_form = (count($parts) > 2);
		$this->translation_noun2 = count($singular_parts) > 1
			? parent::create_word_form($singular, $singular_parts[1])
			: $singular;
	}

	protected function do_translate($lower_phrase, $translations_before, $translations_after, &$connector) 
	{
		$significant_noun = self::get_significant_noun($translations_after);
		return $significant_noun
			? self::get_translation_for_noun($significant_noun->identifier)
			: $this->translation;
	}

	protected function get_translation_for_noun($noun_identifier) 
	{
		if ($noun_identifier->form == 'plural')
			return $this->translation_plural;
		if ($noun_identifier->form == 'singular') {
			if ($noun_identifier->type == 1)
				return $this->translation;
			if ($noun_identifier->type == 2)
				return $this->translation_noun2;
			throw new \Exception('Invalid noun type: ' . $noun_identifier->type);
		}
		throw new \Exception('Invalid noun form: ' . $noun_identifier->form);
	}

	private static function get_significant_noun($translations_after) 
	{
		$found_noun = null;
		foreach ($translations_after as $next_translation) {
			if ($next_translation->is_noun())
				$found_noun = $next_translation;				
			else if ($found_noun)
				return $found_noun; 
		}
		return $found_noun;
	}
}

class adjective_definite extends translator
{
	function __construct($identifier, $compact_translation, $indefinite_translator) 
	{
		$definite_key = self::assemble_word_form(explode(':', $compact_translation[BASE_LANG]), 1, 
			$identifier->key);
		$definite_translation = self::assemble_word_form(explode(':', $compact_translation[LANG]), 2,
			$indefinite_translator->translation);
		parent::__construct($identifier->copy($definite_key), $definite_translation);
	}
}
?>
