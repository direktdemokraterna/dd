<?php
namespace I18n;

class translator_match
{
	public $phrase;
	public $translators;
	public $translator;

	function __construct($phrase, $translators) 
	{
		$this->phrase = $phrase;
		$this->translators = $translators;
	}

	public function is_potentially_first_of_double_noun() 
	{
		foreach ($this->translators as $translator)
			if ($translator instanceof noun && $translator->is_potentially_first_of_double_noun())
				return true;							
		return false;
	}

	public function translate($translators_before, $translators_after, $translation_hints) 
	{
		return $this->translator->translate(strtolower($this->phrase), $translators_before, $translators_after, $translation_hints);
	}

	public function make_noun_prefix() 
	{
		return $this->translator->make_noun_prefix(strtolower($this->phrase));
	}
}
?>
