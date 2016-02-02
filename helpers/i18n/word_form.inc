<?php
namespace I18n;

class word_form 
{
	public static $word_form_counter = 0;
	
	public $class;
	public $numerus;
	public $tempus;
	public $definite;
	public $compact_form;

	public function __construct($class, $modifiers, $compact_form) 
	{
		$this->compact_form = $compact_form;
		$this->class = $class;
		if (isset($modifiers['numerus']))
			$this->numerus = $modifiers['numerus'];
		if (isset($modifiers['tempus']))
			$this->tempus = $modifiers['tempus'];
		if (isset($modifiers['definite']))
			$this->definite = $modifiers['definite'];
	}

	public function __toString() {
		return $this->compact_form;
	}

	public function matches_in_context($translator, $previous_word_form_match, $next_word_form_match) 
	{
		$match = $this->matches($translator) 
			&& $translator->identifier->match($previous_word_form_match, $next_word_form_match);
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
