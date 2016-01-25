<?php
namespace I18n;

class template
{
	public $priority;
	public $from_sequence;
	public $to_sequence;

	public function __construct($priority, $from_sequence, $to_sequence) 
	{
		$this->priority = $priority;
		$this->from_sequence = $from_sequence;
		$this->to_sequence = $to_sequence;
	}

	public function matches($translator_matches) 
	{
		if (count($this->from_sequence) > count($translator_matches))
			return false;
		$matches_after = $translator_matches;
		$matches_before = array();
		$localized_strings = array();
		$index = 0;
		while ($matches_after && $index < count($this->from_sequence)) {
			$match = array_shift($matches_after);
			$translator = $match->translator;
			if (!self::is_compound_noun($translator, $matches_after)) {
				$word_form = $this->from_sequence[$index++];
				if (!$word_form->matches_in_context($translator, $matches_before, $matches_after))
					return false;
			}
			$matches_before[] = $match;
		}
		return $index == count($this->from_sequence);
	}

	public function partially_matches($remaining_matches, $offset) 
	{
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
