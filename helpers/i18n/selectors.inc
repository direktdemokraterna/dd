<?php
namespace I18n;

class word_selector 
{
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
			$this->words[] = $match;
			$parts = explode('-', $match);
			$class = $parts[0];
			$this->classes[] = $class;
			$this->forms[] = count($parts) > 1 ? $parts[1] : null;
		}
	}

	public function match($previous_matches, $following_matches, $restrictive = true) 
	{
		$match = $this->get_match($previous_matches, $following_matches);
		return $this->classes || $this->words
			? $match && $this->match_translator($match->translator)
			: !$match;
	}

	protected function get_match($previous_matches, $following_matches) 
	{
		return null;
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
				&& (self::match_tempus($translator, $this->forms[$i])
				|| self::match_numerus($translator, $this->forms[$i])
				|| self::match_definite($translator, $this->forms[$i] == 'definite'))))
				return true;
		return false;
	}

	public function match_word($translator, $word) 
	{
		return $translator->identifier->base_form == $word; 
	}

	public function match_class($translator, $class) 
	{
		return $translator->identifier->class == $class; 
	}

	public function match_tempus($translator, $tempus) 
	{
		return !$tempus || $translator->identifier->tempus == $tempus; 
	}

	public function match_numerus($translator, $numerus) 
	{
		return !$numerus || $translator->identifier->numerus == $numerus; 
	}

	public function match_definite($translator, $definite) 
	{
		return $translator->identifier->definite == $definite; 
	}
}

class previous_word_selector extends word_selector
{
	public static $pattern = '/^(\[\w+[\w\|\-]+\w+\]|\[\w*\])/';

	protected function get_match($previous_matches, $following_matches) 
	{
		return $previous_matches ? end($previous_matches) : null;
	}
}

class next_word_selector extends word_selector
{
	public static $pattern = '/(\[\w+[\w\|\-]+\w+\]|\[\w*\])$/';

	protected function get_match($previous_matches, $following_matches) 
	{
		return $following_matches ? $following_matches[0] : null;
	}
}

class noun_numerus_selector 
{
	protected function get_quantifier($previous_matches, $restrictive) 
	{
		$current_is_noun = true;
		foreach (array_reverse($previous_matches) as $match) {
			$translator = $match->translator;
			if ($translator->is_quantifier())
				return (int)$match->phrase;
			if ($translator->is_adjective())
				$current_is_noun = false; 
			else if ($restrictive || !$translator->is_noun() || !$current_is_noun)
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
		$quantifier = parent::get_quantifier($previous_matches, $restrictive);
		return $quantifier && self::is_one($quantifier);
	}
}

class plural_noun_selector extends noun_numerus_selector
{
	public function match($previous_matches, $following_matches, $restrictive = true) 
	{
		$quantifier = parent::get_quantifier($previous_matches, $restrictive);
		return $quantifier && !self::is_one($quantifier);
	}
}
?>
