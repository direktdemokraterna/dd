<?php
namespace I18n;

class template
{
	public static $template_partial_counter = 0;
	public static $template_complete_counter = 0;

	public $priority;
	public $from_sequence;
	public $to_sequence;
	public $compact_form;

	public function __construct($priority, $from_sequence, $to_sequence, $compact_form) 
	{
		$this->priority = $priority;
		$this->from_sequence = $from_sequence;
		$this->to_sequence = $to_sequence;
		$this->compact_form = $compact_form;
	}

	public function __toString() {
        return $this->compact_form;
    }

	public function map_to_word_forms($translator_matches) 
	{
		self::$template_complete_counter++;
		$mapped_word_forms = array();
		if (count($this->from_sequence) > count($translator_matches))
			return false;
		$matches_after = $translator_matches;
		$matches_before = array();
		$localized_strings = array();
		$index = 0;
		while ($matches_after && $index < count($this->from_sequence)) {
			$match = array_shift($matches_after);
			echo $match->translator->identifier->key . '<br>';
			$translator = $match->translator;
			if (self::is_compound_noun($translator, $matches_after)) {
				if (!$translator->identifier->match($matches_before, $matches_after))
					return false;
				$mapped_word_forms[] = null;
			}
			else {
				$word_form = $this->from_sequence[$index++];
				if (!$word_form->matches_in_context($translator, $matches_before, $matches_after))
					return false;
				$mapped_word_forms[] = $word_form;
			}
			$matches_before[] = $match;
		}
		return $index == count($this->from_sequence)
			? $mapped_word_forms
			: null;
	}

	public function partially_matches($remaining_matches, $offset) 
	{
		self::$template_partial_counter++;
		$index = $offset;
		while ($remaining_matches && $index < count($this->from_sequence)) {
			$match = array_shift($remaining_matches);
			$translator = $match->translator;
			if (!self::is_compound_noun($translator, $remaining_matches)) {
				$word_form = $this->from_sequence[$index++];
				if (!$word_form->matches($translator))
					return false;
			}
		}
		return $index == count($this->from_sequence);
	}

	public function matches_last_translator($translator) {
		return end($this->from_sequence)->matches($translator);
	}

	public static function is_compound_noun($translator, $matches_after) 
	{
		return $translator->is_noun() 
			&& $matches_after && $matches_after[0]->translator->is_noun();
	}
}
?>
