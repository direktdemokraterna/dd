<?php
namespace I18n;

class verb_imperative extends translator 
{
	public $has_infinitive;
	public $has_present;
	public $has_perfect;
	public $has_perfect_participle;

	function __construct($identifier, $compact_translation) 
	{
		$words = explode(' ', $compact_translation, 2);
		$parts = explode(':', $words[0]);
		$translation = $parts[0];
		if (count($words) == 2)
			$translation .= ' ' . $words[1];
		parent::__construct($identifier, $translation);
		self::set_form_availability(count($parts));
	}
	
	private function set_form_availability($part_count) 
	{
		$this->has_infinitive = $part_count > 1;
		$this->has_present = $part_count > 2;
		$this->has_perfect = $part_count > 3;
		$this->has_perfect_participle = $part_count > 4;
	}
}

class verb_infinitive extends translator 
{
	function __construct($identifier, $compact_translation) 
	{
		$words = explode(' ', $compact_translation, 2);
		$parts = explode(':', $words[0]);
		$translation = parent::assemble_word_form($parts, 1);
		if (count($words) == 2)
			$translation .= ' ' . $words[1];
		parent::__construct($identifier, $translation);
	}

	protected function match_static($previous_matches) 
	{
		return $previous_matches && self::is_indefinite_marker(end($previous_matches));
	}

	private static function is_indefinite_marker($previous_match) 
	{
		return $previous_match->translator->is_verb() || $previous_match->translator->identifier->class == 'indefinite';
	}
}

class verb_present extends translator 
{
	public $singular_translation;

	function __construct($identifier, $compact_translation) 
	{
		$words = explode(' ', $compact_translation, 2);
		$parts = explode(':', $words[0]);
		$translation = parent::assemble_word_form($parts, 2);
		$singular_translation = self::extract_singular_translation($translation);
		if (count($words) == 2) {
			$translation .= ' ' . $words[1];
			if ($singular_translation)
				$singular_translation .= ' ' . $words[1];
		}
		parent::__construct($identifier, $translation);
		$this->singular_translation = $singular_translation;
	}

	protected function match_static($previous_matches) 
	{
		return $previous_matches && self::is_subject(end($previous_matches)->translator);
	}

	private function is_subject($translator) 
	{
		return $translator->is_noun() || $translator->is_pronoun();
	}

	protected function do_translate($lower_phrase, $translations_before, $translations_after, &$connector) 
	{
		if ($this->singular_translation) {
			$significant_noun = self::get_significant_noun($translations_before);
			if ($significant_noun && $significant_noun->identifier->form == 'singular')
				return $this->singular_translation;			
		}
		return parent::do_translate($lower_phrase, $translations_before, $translations_after, $connector);
	}

	private function extract_singular_translation(&$translation) 
	{
		$parts = explode('|', $translation, 2);
		if (count($parts) == 1) 
			return null;
		$translation = $parts[0];
		$singular_translation = self::assemble_word_form($parts, 1);
		return $singular_translation;
	}

	private static function get_significant_noun($translations_before) 
	{
		if ($translations_before) {
			$previous_translation = end($translations_before);
			if ($previous_translation->is_noun())
				return $previous_translation;
		}
		return null;
	}
}

class verb_perfect extends translator 
{
	function __construct($identifier, $compact_translation) 
	{
		$perfect_key = self::assemble_word_form(explode(':', $compact_translation[BASE_LANG]), 3);
		$perfect_translation = self::assemble_word_form(explode(':', $compact_translation[LANG]), 3);
		parent::__construct($identifier->copy($perfect_key), $perfect_translation);
	}
}

class verb_perfect_participle extends adjective
{
	function __construct($identifier, $compact_translation_pair) 
	{
		$base_parts = explode(':', $compact_translation_pair[BASE_LANG]);
		$adjective_key = parent::create_word_form($base_parts[0], self::strip_parenthesis($base_parts[4]));
		$adjective_compact_translation = self::make_adjective_compact_translation($compact_translation_pair[LANG]);
		parent::__construct(new translation_identifier($adjective_key, 'adj'),
			$adjective_compact_translation);
	}

	private static function make_adjective_compact_translation($verb_compact_translation) 
	{
		$verb_base_form_and_endings = explode(':', $verb_compact_translation, 5);
		$verb_base_form = $verb_base_form_and_endings[0];
		$perfect_participle_endings = parent::strip_parenthesis($verb_base_form_and_endings[4]);
		$adjective_compact_translation = parent::create_word_form($verb_base_form, $perfect_participle_endings);
		return $adjective_compact_translation;
	}
}
?>
