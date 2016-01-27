<?php
namespace I18n;

class word_form 
{
	public static $word_form_counter = 0;
	
	public $class;
	public $numerus;
	public $tempus;
	public $definite;

	public function __construct($class, $modifiers) 
	{
		$this->class = $class;
		if (isset($modifiers['numerus']))
			$this->numerus = $modifiers['numerus'];
		if (isset($modifiers['tempus']))
			$this->tempus = $modifiers['tempus'];
		if (isset($modifiers['definite']))
			$this->definite = $modifiers['definite'];
	}

	public function matches_in_context($translator, $matches_before, $matches_after) 
	{
		$match = $this->matches($translator) 
			&& $translator->identifier->match($matches_before, $matches_after);
		return $match;
	}

	public function matches($translator) 
	{
		self::$word_form_counter++;
		if ($this->class == '%d') return $translator->identifier->key == '%d';
		$match = (!$this->class || $this->class == $translator->identifier->class)
			&& (!$this->numerus || !$translator->identifier->numerus || $this->numerus == $translator->identifier->numerus)
			&& (!$this->tempus || !$translator->identifier->tempus || $this->tempus == $translator->identifier->tempus);
		return $match;
	}

	public function merge_hints($hints) {
		if ($this->numerus)
		{
			if (!$hints) $hints = array();
			$hints['numerus'] = $this->numerus;
		}
		if ($this->definite !== null)
		{
			if (!$hints) $hints = array();
			$hints['definite'] = $this->definite;
		}
		return $hints;
	}
}
?>
