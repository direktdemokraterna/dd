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
		return (!$this->class || $this->class == $translator->identifier->class)
			&& (!$this->numerus || $this->numerus == $translator->identifier->numerus);
	}
}
?>
