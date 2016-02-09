<?php
namespace I18n;

class noun extends translator 
{
	public $is_definite;
	private $base_translation;
	private $definite_translation;
	public $connector;
	public $has_plural;

	protected function init($numerus, $compact_translation, $indef_index, $def_index) 
	{
		$this->identifier->numerus = $numerus;
		$this->connector = self::extract_connector($compact_translation);
		self::set_inflections($compact_translation, $indef_index, $def_index);
	}

	protected function copy_from($template) 
	{
		$this->translation = $template->translation;
		$this->base_translation = $template->base_translation;
		$this->definite_translation = $template->definite_translation;
	}

	public function translate($lower_phrase, $translations_before, $translations_after, $translation_hints = null) 
	{
		$this->is_definite = self::check_is_definite($translations_before, $translations_after, $translation_hints);
		return $this->is_definite ? $this->definite_translation	: $this->translation; 
	}

	public function make_noun_prefix($lower_phrase) 
	{
		return self::create_word_form($this->base_translation, $this->connector);
	}

	public function make_genitive() 
	{
		$genitive = $this->copy(); 
		$genitive->identifier->class = 'noun-gen';
		genitive_translator::make_translated_gentitive($genitive->translation);
		genitive_translator::make_translated_gentitive($genitive->definite_translation);
		genitive_translator::make_original_gentitive($genitive->identifier->key);
		return $genitive;
	}

	public function is_potentially_first_of_double_noun() 
	{
		return $this->connector !== null &&	!$this->identifier->definite;
	}

	protected function copy() 
	{
	}

	private static function extract_connector(&$compact_translation) 
	{
		$parts = explode(':-', $compact_translation);
		$compact_translation = $parts[0];
		return count($parts) == 2 ? $parts[1] : null;
	}

	private function set_inflections($inflections, $indef_index, $def_index) {
		$parts = util::split_word_forms($inflections);
		$this->has_plural = count($parts) > 1;
		$this->base_translation = $parts[0];
		$this->translation = $indef_index 
			? self::assemble_word_form($parts, $indef_index)
			: $this->base_translation;
		$this->definite_translation = count($parts) > $def_index
			? self::create_word_form($this->translation, $parts[$def_index])
			: $this->translation;
	}

	private function check_is_definite($translations_before, $translations_after, $translation_hints) 
	{
		if ($translation_hints && isset($translation_hints['definite']))
			return $translation_hints['definite'];
		return $translations_before &&
	 		(self::is_definite_adjective(end($translations_before)->identifier)
	 			|| self::has_definite_marker($translations_before));
	}

	private static function is_definite_adjective($identifier) 
	{
		return $identifier->class == 'adj' && $identifier->definite;
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
}

class noun_singular extends noun 
{
	public $plural_translator;

	public static function create($identifier, $compact_translation) 
	{
		$noun = new noun_singular($identifier);
		$noun->init('singular', $compact_translation, 0, 2);
		return $noun;
	}

	protected function copy() 
	{
		$noun = new noun_singular($this->identifier->copy());
		$noun->copy_from($this);
		$noun->plural_translator = $this->plural_translator;
		return $noun;
	}
}

class noun_plural extends noun 
{
	public static function create($identifier, $compact_translation) 
	{
		$noun = new noun_plural($identifier);
		$noun->init('plural', $compact_translation[controller::get_language()], 1, 3);
		return $noun;
	}

	public function is_potentially_first_of_double_noun() 
	{
		return false;
	}

	protected function copy() {
		$noun = new noun_plural($this->identifier->copy());
		$noun->copy_from($this);
		return $noun;
	}

	public static function make_plural_identifier($identifier, $compact_translation) {
		$key_parts = util::split_word_forms($compact_translation[BASE_LANG]);
		return $identifier->copy(array('key' => self::assemble_word_form($key_parts, 1)));
	}
}
?>
