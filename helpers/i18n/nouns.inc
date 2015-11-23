<?php
namespace I18n;

class noun extends translator 
{
	private $base_translation;
	private $definite_translation;
	private $connector;

	function __construct($identifier, $form, $compact_translation, $indef_index, $def_index) 
	{
		$identifier->form = $form;
		parent::__construct($identifier);
		$parts = explode(':-', $compact_translation);
		$inflections = $parts[0];
		$this->connector = count($parts) == 2 ? $parts[1] : null;
		self::set_inflections($inflections, $indef_index, $def_index);
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

	protected function do_translate($lower_phrase, $translations_before, $translations_after, &$connector) 
	{
		if ($this->is_compound($translations_after)) {
			$connector = '';
			return parent::create_word_form($this->base_translation, $this->connector);
		}
		return self::is_definite($translations_before)
			? $this->definite_translation
			: $this->translation; 
	}

	private static function is_definite($translations_before) 
	{
		return $translations_before && get_class(end($translations_before)) == 'adjective_definite';
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
		if (!$identifier->key) {
			$key_parts = explode(':', $compact_translation[BASE_LANG]);
			$identifier->key = self::assemble_word_form($key_parts, 1);			
		}
		parent::__construct($identifier, 'plural', $compact_translation[LANG], 1, 3);
	}
}
?>
