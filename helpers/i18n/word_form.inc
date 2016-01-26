<?php
namespace I18n;

class word_form 
{
	public $class;
	public $numerus;

	public function __construct($class, $modifiers) 
	{
		$this->class = $class;
		if (isset($modifiers['numerus']))
			$this->numerus = $modifiers['numerus'];
	}

	public function matches_in_context($translator, $matches_before, $matches_after) 
	{
		$match = $this->matches($translator) 
			&& $translator->identifier->match($matches_before, $matches_after);
		return $match;
	}

	public function matches($translator) 
	{
		//var_dump($this, $translator);
		if ($this->class == '%d') return $translator->identifier->key == '%d';
		$match = (!$this->class || $this->class == $translator->identifier->class)
			&& (!$this->numerus || !$translator->identifier->numerus || $this->numerus == $translator->identifier->numerus);
		//echo 'matches<br>';
		//var_dump($translator, $this, $match);
		return $match;
	}

	public function merge_hints($hints) {
		if ($this->numerus)
		{
			if (!$hints) $hints = array();
			$hints['numerus'] = $this->numerus;
		}
		return $hints;
	}
}
?>
