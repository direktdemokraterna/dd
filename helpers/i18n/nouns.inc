<?php
namespace I18n;

class noun extends translator 
{
	public  $is_definite;

	private $base_translation;
	private $definite_translation;
	private $connector;

	function __construct($identifier, $form, $compact_translation, $indef_index, $def_index) 
	{
		$identifier->form = $form;
		parent::__construct($identifier);
		$this->connector = self::extract_connector($compact_translation);
		self::set_inflections($compact_translation, $indef_index, $def_index);
	}
	
	private static function extract_connector(&$compact_translation) 
	{
		$parts = explode(':-', $compact_translation);
		$compact_translation = $parts[0];
		return count($parts) == 2 ? $parts[1] : null;
	}

	private function set_inflections($inflections, $indef_index, $def_index) {
		$parts = explode(':', $inflections);
		$this->base_translation = $parts[0];
		$this->translation = $indef_index 
			? self::assemble_word_form($parts, $indef_index)
			: $this->base_translation;
		$this->definite_translation = count($parts) > $def_index
			? self::create_word_form($this->translation, $parts[$def_index])
			: $this->translation;
	}

	protected function do_translate($lower_phrase, $translations_before, $translations_after, &$connector, $translation_hints = null) 
	{
		if ($this->is_compound($translations_after)) {
			$connector = '';
			return parent::create_word_form($this->base_translation, $this->connector);
		}
		$this->is_definite = self::check_is_definite($translations_before);
		return $this->is_definite ? $this->definite_translation	: $this->translation; 
	}

	private static function check_is_definite($translations_before) 
	{
		return $translations_before && 
		(
			self::is_definite_adjective(end($translations_before)->identifier)
			|| self::has_definite_marker($translations_before)
		);
	}

	private static function is_definite_adjective($identifier) 
	{
		return $identifier->class == 'adj' && $identifier->form == 'definite';
	}

	private static function has_definite_marker($translations_before) 
	{
		foreach (array_reverse($translations_before) as $previous_translation) {
			if ($previous_translation->identifier->class == 'definite')
				return true;
			if (!($previous_translation->is_noun_modifier() || $previous_translation->is_noun()))
				break;
		}
		return false;
	}

	protected function is_compound($translations_after) 
	{
		return $this->connector !== null && $translations_after && $translations_after[0]->is_noun();
	}
}

class noun_singular extends noun 
{
	function __construct($identifier, $compact_translation) 
	{
		parent::__construct($identifier, 'singular', $compact_translation, 0, 2);
	}
}

class noun_plural extends noun 
{
	function __construct($identifier, $compact_translation) 
	{
		parent::__construct($identifier, 'plural', $compact_translation[LANG], 1, 3);
	}

	public static function make_plural_identifier($identifier, $compact_translation) {
		$key_parts = explode(':', $compact_translation[BASE_LANG]);
		return $identifier->copy(self::assemble_word_form($key_parts, 1));
	}
}
?>
