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

	protected function match_static($previous_matches, $following_matches, $restrictive = true) 
	{
		if (!$restrictive) return true;
		if ($previous_matches && end($previous_matches)->translator->identifier->key == 'as')
			return false;
		return !($previous_matches && self::is_invalid_imperative_modifier(end($previous_matches)->translator));
	}

	protected function is_invalid_imperative_modifier($translator) 
	{
		return $translator->is_noun_modifier() || $translator->is_verb();
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

	protected function match_static($previous_matches, $following_matches, $restrictive = true) 
	{
		return $previous_matches && 
		self::has_indefinite_marker($previous_matches);
	}

	private static function has_indefinite_marker($previous_matches) 
	{
		if (end($previous_matches)->translator->identifier->class == 'indefinite') return true;
		foreach (array_reverse($previous_matches) as $match) {
			if ($match->translator->identifier->class == 'verb-aux')
				return true;
			else if ($match->translator->is_verb())
				break;
		}
		return false;
	}
}

class verb_present extends translator 
{
	public $singular_key;
	public $singular_translation;

	function __construct($identifier, $compact_translation) 
	{
		$keys = iterator_to_array(self::get_word_forms($compact_translation[BASE_LANG]));
		$translations = iterator_to_array(self::get_word_forms($compact_translation[LANG]));
		$identifier->form = 'present';
		parent::__construct($identifier, $translations[0]);
		$this->singular_translation = $translations[1];
		$this->singular_key = $keys[1];
	}

	private function get_word_forms($compact_translation) 
	{
		$words = explode(' ', $compact_translation, 2);
		$parts = explode(':', $words[0]);
		$word = parent::assemble_word_form($parts, 2);
		$singular = self::extract_singular($word);
		if (count($words) == 2) {
			$word .= ' ' . $words[1];
			if ($singular)
				$singular .= ' ' . $words[1];
		}
		yield $word;
		yield $singular;
	}

	private function extract_singular(&$compact_forms) 
	{
		$parts = explode('|', $compact_forms, 2);
		if (count($parts) == 1) 
			return $compact_forms;
		$compact_forms = $parts[0];
		return self::assemble_word_form($parts, 1);
	}

	protected function match_static($previous_matches, $following_matches, $restrictive = true) 
	{
		return $previous_matches 
			? self::get_subject(array_map(function($match) {return $match->translator;}, $previous_matches))
			: !$restrictive && !$following_matches;
	}

	protected function do_translate($lower_phrase, $translations_before, $translations_after, &$connector, $translation_hints = null) 
	{
		if ($this->singular_translation) {
			$subject = self::get_subject($translations_before);
			if ($subject && $subject->identifier->form == 'singular')
				return $this->singular_translation;
		}
		return parent::do_translate($lower_phrase, $translations_before, $translations_after, $connector, $translation_hints);
	}

	private static function get_subject($translators_before) 
	{
		foreach (array_reverse($translators_before) as $translator) {
			if (self::is_subject($translator)) 
				return $translator;
			if ($translator->identifier->key != 'who')
				break;			
		}
		return null;
	}

	private static function is_subject($translator) 
	{
		return $translator->is_noun() || $translator->is_pronoun();
	}
}

class verb_present_singular extends translator 
{
	function __construct($identifier, $translation) 
	{
		$identifier->form = 'present';
		parent::__construct($identifier, $translation);
	}

	protected function match_static($previous_matches, $following_matches, $restrictive = true) 
	{
		return $previous_matches 
			? self::has_subject($previous_matches)
			: !$restrictive;
	}

	private static function has_subject($previous_matches) {
		foreach (array_reverse($previous_matches) as $match) {
			if ($match->translator->is_noun() || $match->translator->is_pronoun())
				return true;
			if ($match->translator->identifier->class != 'prep')
				break;
		}
		return false;
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

	protected function match_static($previous_matches, $following_matches, $restrictive = true) 
	{
		if ($previous_matches && self::is_present_marker(end($previous_matches)->translator))
			return false;
		return !$restrictive || !self::has_indefinite_object($following_matches);  
	}

	private static function is_present_marker($translator) {
		return $translator->is_verb() && $translator->identifier->form == 'present';
	}

	private static function has_indefinite_object($following_matches) {
		return $following_matches && self::is_indefinite_noun($following_matches[0]->translator);
	}

	private static function is_indefinite_noun($translator) {
		if (is_array($translator))
			return self::is_indefinite_noun($translator[0]);
		return $translator->is_noun() && !$translator->is_definite;
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
