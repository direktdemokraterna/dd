<?php
namespace I18n;

class word_selector 
{
	public static $previous_word_pattern = '/^(\[\w+[\w\|\-]+\w*\]|\[\w*\])/';
	public static $next_word_pattern = '/(\[\w+[\w\|\-]+\w*\]|\[\w*\])$/';

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

	public function match($identifier) 
	{
		if ($identifier) {
			if ($this->words)
				for ($i = 0; $i < count($this->words); $i++)
					if (self::match_word($identifier, $this->words[$i]) 
						|| self::match_word_form($identifier, $i))
						return true;
		}
		else if (!$this->words)
			return true;
		else
			foreach ($this->words as $word)
					if (!$word) 
						return true;			
		return false;
	}

	public function rough_match($word_expected) 
	{
		if (!$this->words)
			return !$word_expected;
		foreach ($this->words as $word)
			if (!$word == !$word_expected) 
				return true;			
		return false;
	}

	public function match_word_form($identifier, $i) 
	{
		return self::match_class($identifier, $this->classes[$i])
		&& (self::match_tempus($identifier, $this->forms[$i])
			|| self::match_numerus($identifier, $this->forms[$i])
			|| self::match_definite($identifier, $this->forms[$i] == 'definite'));
	}

	public function match_word($identifier, $word) 
	{
		return $identifier->base_form == $word; 
	}

	public function match_class($identifier, $class) 
	{
		return $identifier->class == $class; 
	}

	public function match_tempus($identifier, $tempus) 
	{
		return !$tempus || $identifier->tempus == $tempus; 
	}

	public function match_numerus($identifier, $numerus) 
	{
		return !$numerus || $identifier->numerus == $numerus; 
	}

	public function match_definite($identifier, $definite) 
	{
		return $identifier->definite == $definite; 
	}
}
?>
