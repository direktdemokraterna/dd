<?php
namespace I18n;

class template_match
{
	public $templates;
	public $translator_matches;
	public $double_noun_indices;
	
	public function __construct($templates, $translator_matches, $double_noun_indices) 
	{
		$this->templates = $templates;
		$this->translator_matches = $translator_matches;
		$this->double_noun_indices = $double_noun_indices;
	}

	public function apply_numbers(&$numbers) {
		for ($index = 0; $index < count($this->translator_matches); $index++) {
			$match = $this->translator_matches[$index];
			$translator = $match->translator;
			if ($translator->is_number()) {
				$translator->translation = $numbers[0];				
				array_shift($numbers);
			}
		}
	}

	public function translate($translation_hints = null) 
	{
		self::pluralify();
		$translator_index = 0;
		$translated_words = null;
		$translators_before = array();
		$translators_after = array_map(function($match) {return $match->translator;}
			, $this->translator_matches);
		foreach ($this->templates as $template) {
			$next_translated_words = $template->get_translated_parts($this->translator_matches
				, $translation_hints, $this->double_noun_indices, $translator_index
				, $translators_before, $translators_after);
			$translated_words = $translated_words
				? array_merge($translated_words, $next_translated_words)
				: $next_translated_words;
		}
		$translation = implode(' ', $translated_words);
		return $translation;
	}

	private function pluralify() 
	{
		for ($index = 0; $index < count($this->translator_matches); $index++) {
			$match = $this->translator_matches[$index];
			$translator = $match->translator;
			if (self::is_single_noun($translator->identifier) 
				&& self::has_plurifying_quantifier(array_slice($this->translator_matches, 0, $index)))
				$match->translator = $match->translator->plural_translator;
		}
	}

	private function is_single_noun($identifier) 
	{
		return $identifier->class == 'noun' && $identifier->numerus == 'singular';
	}

	private function has_plurifying_quantifier($previous_matches) 
	{
		$quantifier = self::get_quantifier($previous_matches);
		return $quantifier && !self::is_one($quantifier);
	}

	private function get_quantifier($previous_matches) 
	{
		$current_is_noun = true;
		foreach (array_reverse($previous_matches) as $match) {
			$translator = $match->translator;
			if ($translator->is_number())
				return (int)$translator->translation;
			if ($translator->is_quantifier())
				return strtolower($match->phrase);
			if ($translator->is_adjective())
				$current_is_noun = false; 
			else if (!$translator->is_noun() || !$current_is_noun)
				break; 
		}
		return null; 
	}

	private static function is_one($quantifier) 
	{
		return in_array($quantifier, array("1", "a", "an", "one", "no"));
	}
}
?>
