<?php
namespace I18n;

class adjective extends translator
{
	public $translation_noun2;
	public $translation_plural;
	public $has_definite_form;

	function __construct($identifier, $compact_translation, $form = 'infinite') 
	{
		$identifier->form = $form;
		$parts = explode(':', $compact_translation);
		$singular_parts = explode('|', $parts[0]);
		$singular = $singular_parts[0];
		parent::__construct($identifier, $singular);
		$this->translation_plural = count($parts) > 1
			? parent::create_word_form($singular, $parts[1])
			: $singular;
		$this->has_definite_form = (count($parts) > 2);
		$this->translation_noun2 = count($singular_parts) > 1
			? parent::create_word_form($singular, $singular_parts[1])
			: $singular;
	}

	protected function do_translate($lower_phrase, $translations_before, $translations_after, &$connector) 
	{
		$significant_noun = self::get_significant_noun($translations_before, $translations_after);
		return $significant_noun
			? self::get_translation_for_noun($significant_noun->identifier)
			: $this->translation;
	}

	protected function get_translation_for_noun($noun_identifier) 
	{
		if ($noun_identifier->form == 'plural')
			return $this->translation_plural;
		if ($noun_identifier->form == 'singular') {
			if ($noun_identifier->type == 1)
				return $this->translation;
			if ($noun_identifier->type == 2)
				return $this->translation_noun2;
			throw new \Exception('Invalid noun type: ' . $noun_identifier->type);
		}
		throw new \Exception('Invalid noun form: ' . $noun_identifier->form);
	}

	private static function get_significant_noun($translations_before, $translations_after) 
	{
		$parting_words_left = array();
		$parting_words_right = array();
		$left_noun = self::search_left($translations_before, $parting_words_left);
		$right_noun = self::search_right($translations_after, $parting_words_right);
		if ($left_noun && $right_noun)
			return self::select_significant_noun($left_noun, $parting_words_left, $right_noun, $parting_words_right);
		return $left_noun ? $left_noun : $right_noun;
	}

	private static function search_left($translations_before, &$parting_words) 
	{
		foreach (array_reverse($translations_before) as $previous_translation) {
			if ($previous_translation->is_noun())
				return $previous_translation;
			else $parting_words[] = $previous_translation;
		}
		return null;
	}

	private static function search_right($translations_after, &$parting_words) 
	{
		$found_noun = null;
		foreach ($translations_after as $next_translation) {
			if ($next_translation->is_noun())
				$found_noun = $next_translation;				
			else if ($found_noun)
				return $found_noun; 
			else $parting_words[] = $next_translation;
		}
		return $found_noun;
	}

	private static function select_significant_noun($left_noun, $parting_words_left, $right_noun, $parting_words_right) 
	{
		$left_count = count($parting_words_left);
		$right_count = count($parting_words_right);
		if (!$right_count || $right_count < $left_count) 
			return $right_noun;
		if ($left_count < $right_count)
			return $left_noun;
		$left_word_distance = self::compute_word_distance($parting_words_left);
		$right_word_distance = self::compute_word_distance($parting_words_right);
		return $right_word_distance <= $left_word_distance 
			? $right_noun 
			: $left_noun;
	}

	private static function compute_word_distance($words) {
		$sum = 0;
		foreach ($words as $word)
			$sum += self::get_word_distance($word);
		return $sum;
	}
	
	private static function get_word_distance($word) {
		switch ($word->class) {
			case 'verb':
				return 1;
			case 'adj':
				return 2;
			case 'conj':
				return 3;
			default:
				return 4;
		}
	}
}

class adjective_definite extends translator
{
	function __construct($identifier, $compact_translation, $indefinite_translator) 
	{
		$definite_key = self::assemble_word_form(explode(':', $compact_translation[BASE_LANG]), 1, 
			$identifier->key);
		$definite_translation = self::assemble_word_form(explode(':', $compact_translation[LANG]), 2,
			$indefinite_translator->translation);
		parent::__construct($identifier->copy($definite_key), $definite_translation, 'definite');
	}
}
?>
