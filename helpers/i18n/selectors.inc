<?php
namespace I18n;

class previous_word_selector 
{
	public static $pattern = '/^\[\w*\]/';

	public $word;

	function __construct($word) 
	{
		$this->word = $word;
	}

	public function match($previous_matches, $following_matches, $restrictive = true) 
	{
		return $this->word 
			? $previous_matches && end($previous_matches)->translator->identifier->base_form == $this->word
			: !$previous_matches;
	}
}

class next_word_selector 
{
	public static $pattern = '/\[\w+[\w\|\-]+\w+\]|\[\w*\]$/';

	public $words;
	public $classes;
	public $forms;

	function __construct($matches_str) 
	{
		self::extract_matches($matches_str);
	}

	private function extract_matches($matches_str) 
	{
		$matches = $matches_str
			? explode('|', $matches_str)
			: array();
		$this->words = array();
		$this->classes = array();
		$this->forms = array();
		foreach ($matches as $match) {
			$words = $match;
			$parts = explode('-', $match);
			$class = $parts[0];
			$this->classes[] = $class;
			$this->forms[] = count($parts) > 1 ? $parts[1] : null;
		}
	}

	public function match($previous_matches, $following_matches, $restrictive = true) 
	{
		return $this->classes || $this->words
			? $following_matches && $this->match_translator($following_matches[0]->translator)
			: !$following_matches;
	}

	private function match_translator($translator) 
	{
		if (is_array($translator)) {
			foreach ($translator as $candidate)
				if ($this->match_translator($candidate))
					return true;
			return false;
		}
		for ($i = 0; $i < count($this->words); $i++)
			if (self::match_word($translator, $this->words[$i]) 
				|| (self::match_class($translator, $this->classes[$i]) 
				&& self::match_form($translator, $this->forms[$i])))
				return true;
		return false;
	}

	public function match_word($translator, $word) 
	{
		return $translator->identifier->key == $word; 
	}

	public function match_class($translator, $class) 
	{
		return $translator->identifier->class == $class; 
	}

	public function match_form($translator, $form) 
	{
		return !$form || $translator->identifier->form == $form; 
	}
}

class noun_numerus_selector 
{
	protected function get_quantifier($previous_matches) 
	{
		$current_is_noun = true;
		foreach (array_reverse($previous_matches) as $match) {
			$translator = $match->translator;
			if ($translator->is_quantifier())
				return (int)$match->phrase;
			if ($translator->is_adjective())
				$current_is_noun = false; 
			else if (!($translator->is_noun() && $current_is_noun))
				break; 
		}
		return null; 
	}

	protected static function is_one($quantifier) 
	{
		return in_array($quantifier, array("1", "a", "an", "one"));
	}
}

class singular_noun_selector extends noun_numerus_selector
{
	public function match($previous_matches, $following_matches, $restrictive = true) 
	{
		$quantifier = parent::get_quantifier($previous_matches);
		return $quantifier && self::is_one($quantifier);
	}
}

class plural_noun_selector extends noun_numerus_selector
{
	public function match($previous_matches, $following_matches, $restrictive = true) 
	{
		$quantifier = parent::get_quantifier($previous_matches);
		return $quantifier && !self::is_one($quantifier);
	}
}
?>
