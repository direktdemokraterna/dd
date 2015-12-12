<?php
namespace I18n;

class translation_match
{
	public $phrase;
	public $translator;

	function __construct($phrase, $translator) 
	{
		$this->phrase = $phrase;
		$this->translator = $translator;
	}

	public function translate($translators_before, $translators_after, $translation_hints) 
	{
		return $this->translator->translate(strtolower($this->phrase), $translators_before, $translators_after, $translation_hints);
	}
}

class translation_identifier 
{
	public $key;
	public $base_form;
	public $class;
	public $type;
	public $form;
	public $selector;

	public static function create($identifier_str) 
	{
		$selector = self::extract_selector($identifier_str);
		$parts = explode(':', $identifier_str);
		$category = count($parts) == 2 ? $parts[1] : 'phrase';
		$key = $parts[0];
		preg_match('/\d+/', $category, $type_matches);
		$identifier = $type_matches
			? new translation_identifier($key, str_replace($type_matches[0], '', $category), (int)$type_matches[0])
			: new translation_identifier($key, $category, 1);
		$identifier->selector = $selector;
		return $identifier;
	}

	private static function extract_selector(&$identifier_str) 
	{
		preg_match(previous_word_selector::$pattern, $identifier_str, $pre_matches);
		if ($pre_matches) {
			$identifier_str = str_replace($pre_matches[0], '', $identifier_str);
			return new previous_word_selector(translator::strip_parenthesis($pre_matches[0]));
		}
		preg_match(next_class_selector::$pattern, $identifier_str, $post_matches);
		if ($post_matches) {
			$identifier_str = str_replace($post_matches[0], '', $identifier_str);
			return new next_class_selector(translator::strip_parenthesis($post_matches[0]));
		}
		return null;
	}

	public function match($previous_matches, $following_matches, $restrictive = true) 
	{
		return !$this->selector || $this->selector->match($previous_matches, $following_matches, $restrictive);
	}

	public function copy($new_key, $new_selector = null, $new_form = null) 
	{
		return new translation_identifier($new_key, $this->class, $this->type
			, $new_form ? $new_form : $this->form, 
			$new_selector ? $new_selector : $this->selector, $this->base_form);
	}

	function __construct($key, $class, $type = 1, $form = null, $selector = null, $base_form = null) 
	{
		$this->key = $key;
		$this->base_form = $base_form ? $base_form : $key;
		$this->class = $class;
		$this->type = $type;	
		$this->form = $form;
		$this->selector = $selector;
	}
}

class translator 
{
	public $identifier;		
	public $translation;

	function __construct($identifier, $translation = null) 
	{
		$this->identifier = $identifier;
		$this->translation = $translation;
	}

	public function translate($lower_phrase, $translations_before, $translations_after, $translation_hints = null) 
	{
		$connector = $translations_after ? ' ' : '';
		$translation = $this->do_translate($lower_phrase, $translations_before, $translations_after, $connector, $translation_hints);
		return $translation ? $translation . $connector : '';
	}

	public function match($previous_matches, $following_matches, $restrictive = true)
	{
		return $this->match_static($previous_matches, $following_matches, $restrictive) 
		&& $this->identifier->match($previous_matches, $following_matches, $restrictive);
	}	

	protected function match_static($previous_matches, $following_matches, $restrictive = true) 
	{
		return true;
	}	

	public function is_adjective() 
	{
		return $this->identifier->class == 'adj';
	}

	public function is_noun() 
	{
		return $this->identifier->class == 'noun';
	}

	public function is_verb() 
	{
		return $this->identifier->class == 'verb';
	}

	public function is_pronoun() 
	{
		return in_array($this->identifier->class, array('pron', 'pron-it'));
	}

	public function is_preposition() 
	{
		return $this->identifier->class == 'prep';
	}

	public function is_quantifier() 
	{
		return $this->identifier->class == 'quant';
	}

	public function is_noun_modifier() {
		return $this->is_adjective() 
		|| $this->is_quantifier() 
		|| $this->identifier->class == 'pron-poss'
		|| $this->identifier->class == 'definite'
		|| in_array($this->identifier->key, array('as', 'this'));
	}

	protected function do_translate($lower_phrase, $translations_before, $translations_after, &$connector, $translation_hints = null) 
	{
		return $this->translation;
	}

	protected static function assemble_word_form($parts, $n, $base_form = null) 
	{
		if (!$base_form)
			$base_form = $parts[0];
		return count($parts) > $n 
			? self::create_word_form($base_form, $parts[$n])
			: $base_form;
	}

	protected static function create_word_form($base_form, $ending) 
	{
		$suffix = ltrim($ending, '_');
		$del_char_count = strlen($ending) - strlen($suffix);
		$word_stem = substr($base_form, 0, strlen($base_form) - $del_char_count);
		return $word_stem . $suffix;
	}

	public static function strip_parenthesis($text_in_parenthesis) 
	{
		return substr($text_in_parenthesis, 1, strlen($text_in_parenthesis) - 2);
	}
}

class untranslated extends translator
{
	function __construct($phrase) 
	{
		parent::__construct(new translation_identifier('', 'untranslated'), $phrase);
	}
}

class noun_modifier extends translator 
{
	private $translation_noun2;
	private $translation_plural;

	function __construct($identifier, $compact_translation) 
	{
		$word_parts = explode(' ', $compact_translation, 2);
		$form_parts = explode(':', $word_parts[0]);
		$type_parts = explode('|', $form_parts[0]);
		$singular = $type_parts[0];
		$translation_plural = count($form_parts) > 1
			? parent::create_word_form($singular, $form_parts[1])
			: $singular;
		$translation_noun2 = count($type_parts) > 1
			? parent::create_word_form($singular, $type_parts[1])
			: $singular;
		if (count($word_parts) == 2) {
			$singular .= ' ' . $word_parts[1];
			$translation_plural .= ' ' . $word_parts[1];
			$translation_noun2 .= ' ' . $word_parts[1];
		}
		parent::__construct($identifier, $singular);
		$this->translation_plural = $translation_plural;
		$this->translation_noun2 = $translation_noun2;
	}

	protected function do_translate($lower_phrase, $translations_before, $translations_after, &$connector
		, $translation_hints = null) 
	{
		if ($translation_hints && isset($translation_hints['form']) && $translation_hints['form'] == 'plural')
			return $this->translation_plural;
		$has_plurifying_pronoun = $this->has_plurifying_pronoun($translations_before);
		if ($has_plurifying_pronoun)
			return $this->translation_plural;
		$significant_noun = $this->get_significant_noun($translations_before, $translations_after);
		return $significant_noun
			? self::get_translation_for_noun($significant_noun->identifier)
			: $this->translation;
	}

	private function has_plurifying_pronoun($translations_before) 
	{
		foreach (array_reverse($translations_before) as $translation) {
			if ($translation->identifier->key == 'this' 
				|| $translation->identifier->class == 'definite'
				|| $translation->identifier->class == 'pron-poss')
				return true;
			if (!$translation->is_noun_modifier()) break;
		}
		return false;
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
	
	protected function get_significant_noun($translations_before, $translations_after) 
	{
		$found_noun = null;
		foreach ($translations_after as $translation) {
			if ($translation->is_noun())
				$found_noun = $translation;				
			else if ($found_noun || !$translation->is_noun_modifier()) break;
		}
		return $found_noun;
	}
}
?>
