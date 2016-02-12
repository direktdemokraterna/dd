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
		return $this->translation;
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

	public function is_conjunction() 
	{
		return $this->identifier->class == 'conj';
	}

	public function is_noun_modifier() {
		return $this->is_adjective() 
		|| $this->is_quantifier() 
		|| $this->identifier->class == 'pron-poss'
		|| $this->identifier->class == 'definite'
		|| in_array($this->identifier->key, array('as', 'this'));
	}

	protected static function generate_word($compact_form, $inflection_num, $passive = false
		, $passive_infl_num = 0) 
	{
		$words = explode(' ', $compact_form, 2);
		$word_forms = util::split_word_forms($words[0]);
		$word = $inflection_num
			? self::assemble_word_form($word_forms, $inflection_num)
			: $word_forms[0];
		if ($passive && count($word_forms) > $passive_infl_num) 
			$word = self::assemble_word_form($word_forms, $passive_infl_num, $word);
		if (count($words) > 1)
			$word = $word . ' ' . $words[1];
		return $word;
	}	

	protected static function assemble_word_form($parts, $n, $base_form = null) 
	{
		if (!$base_form)
			$base_form = $parts[0];
		$n = min($n, count($parts) - 1);
		return $n == 0 
			? $base_form 
			: self::create_word_form($base_form, $parts[$n]);
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
