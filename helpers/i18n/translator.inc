<?php
namespace I18n;

class translator 
{
	public $identifier;		
	public $translation;

	function __construct($identifier, $translation = null) 
	{
		$this->identifier = $identifier;
		$this->translation = $translation;
	}

	public function translate($lower_phrase, $translations_before, $translations_after, $translation_hints = null) 
	{
		$connector = $translations_after ? ' ' : '';
		$translation = $this->do_translate($lower_phrase, $translations_before, $translations_after, $connector, $translation_hints);
		return $translation ? $translation . $connector : '';
	}

	public function is_adjective() 
	{
		return $this->identifier->class == 'adj';
	}

	public function is_noun() 
	{
		return $this->identifier->class == 'noun';
	}

	public function is_verb() 
	{
		return $this->identifier->class == 'verb';
	}

	public function is_pronoun() 
	{
		return in_array($this->identifier->class, array('pron', 'pron-it'));
	}

	public function is_preposition() 
	{
		return $this->identifier->class == 'prep';
	}

	public function is_quantifier() 
	{
		return $this->identifier->class == 'quant';
	}

	public function is_noun_modifier() {
		return $this->is_adjective() 
		|| $this->is_quantifier() 
		|| $this->identifier->class == 'pron-poss'
		|| $this->identifier->class == 'definite'
		|| in_array($this->identifier->key, array('as', 'this'));
	}

	protected function do_translate($lower_phrase, $translations_before, $translations_after, &$connector, $translation_hints = null) 
	{
		return $this->translation;
	}

	protected static function assemble_word_form($parts, $n, $base_form = null) 
	{
		if (!$base_form)
			$base_form = $parts[0];
		return count($parts) > $n 
			? self::create_word_form($base_form, $parts[$n])
			: $base_form;
	}

	protected static function create_word_form($base_form, $ending) 
	{
		$suffix = ltrim($ending, '_');
		$del_char_count = strlen($ending) - strlen($suffix);
		$word_stem = substr($base_form, 0, strlen($base_form) - $del_char_count);
		return $word_stem . $suffix;
	}
}

class untranslated extends translator
{
	function __construct($phrase) 
	{
		parent::__construct(new translation_identifier('', 'untranslated'), $phrase);
	}
}

?>
