<?php
namespace I18n;

class translation_match
{
	public $phrase;
	public $translator;

	function __construct($phrase, $translator) 
	{
		$this->phrase = $phrase;
		$this->translator = $translator;
	}

	public function translate($translators_before, $translators_after, $translation_hints) 
	{
		return $this->translator->translate(strtolower($this->phrase), $translators_before, $translators_after, $translation_hints);
	}

	public function split() 
	{
		return array_map(function($single_translator) {
					return new translation_match($this->phrase, $single_translator);
				}, $this->translator);
	}
}
?>
