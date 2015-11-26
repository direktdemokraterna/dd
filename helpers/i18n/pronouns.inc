<?php
namespace I18n;

class pronoun_it extends translator 
{
	public $translation_noun2;

	function __construct($identifier, $compact_translation) 
	{
		$parts = explode('|', $compact_translation);
		parent::__construct($identifier, $parts[0]);
		$this->translation_noun2 = $parts[1];
	}

	protected function do_translate($lower_phrase, $translations_before, $translations_after, &$connector) 
	{
		$significant_noun = self::get_significant_noun($translations_before);
		return $significant_noun
			? self::get_translation_for_noun($significant_noun->identifier)
			: $this->translation_noun2;
	}

	protected function get_translation_for_noun($noun_identifier) 
	{
		if ($noun_identifier->form == 'singular') {
			if ($noun_identifier->type == 1)
				return $this->translation;
			if ($noun_identifier->type == 2)
				return $this->translation_noun2;
			throw new \Exception('Invalid noun type: ' . $noun_identifier->type);
		}
		throw new \Exception('Invalid noun form: ' . $noun_identifier->form);
	}

	private static function get_significant_noun($translations_before) 
	{
		foreach (array_reverse($translations_before) as $previous_translation)
			if (self::is_significant_noun($previous_translation))
				return $previous_translation;
		return null;
	}

	private static function is_significant_noun($previous_translation) 
	{
		return $previous_translation->is_noun() 
		&& $previous_translation->identifier->form == 'singular' 
		&& $previous_translation->is_definite;
	}
}

class quantifier extends translator 
{
	function __construct($identifier, $compact_translation) 
	{
		parent::__construct($identifier, $compact_translation);
	}
}

class definite_marker extends translator 
{
	private $translation_noun2;
	private $translation_plural;

	function __construct($identifier, $compact_translation) 
	{
		$word_parts = explode(' ', $compact_translation, 2);
		$form_parts = explode(':', $word_parts[0]);
		$type_parts = explode('|', $form_parts[0]);
		$singular = $type_parts[0];
		$translation_plural = count($form_parts) > 1
			? parent::create_word_form($singular, $form_parts[1])
			: $singular;
		$translation_noun2 = count($type_parts) > 1
			? parent::create_word_form($singular, $type_parts[1])
			: $singular;
		if (count($word_parts) == 2) {
			$singular .= ' ' . $word_parts[1];
			$translation_plural .= ' ' . $word_parts[1];
			$translation_noun2 .= ' ' . $word_parts[1];
		}
		parent::__construct($identifier, $singular);
		$this->translation_plural = $translation_plural;
		$this->translation_noun2 = $translation_noun2;
	}

	protected function do_translate($lower_phrase, $translations_before, $translations_after, &$connector) 
	{
		$significant_noun = self::get_significant_noun($translations_after);
		return $significant_noun
			? self::get_translation_for_noun($significant_noun->identifier)
			: $this->translation_noun2;
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
		foreach ($translations_after as $next_translation) {
			if ($next_translation->is_noun())
				return $next_translation;
			if (!$next_translation->is_noun_modifier()) break;
		}
		return null;
	}
}
?>
