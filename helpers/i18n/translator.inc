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

	public function translate($translators_before, $translators_after) 
	{
		return $this->translator->translate(strtolower($this->phrase), $translators_before, $translators_after);
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
		preg_match('/^\[\w*\]/', $identifier_str, $pre_matches);
		if ($pre_matches) {
			$identifier_str = str_replace($pre_matches[0], '', $identifier_str);
			return new previous_word_selector(translator::strip_parenthesis($pre_matches[0]));
		}
		preg_match('/\[\w+[\w\|]+\w+\]|\[\w+\]$/', $identifier_str, $post_matches);
		if ($post_matches) {
			$identifier_str = str_replace($post_matches[0], '', $identifier_str);
			return new next_class_selector(translator::strip_parenthesis($post_matches[0]));
		}
		return null;
	}

	public function match($previous_matches, $following_matches) 
	{
		return !$this->selector || $this->selector->match($previous_matches, $following_matches);
	}

	public function copy($new_key, $new_selector = null) 
	{
		return new translation_identifier($new_key, $this->class, $this->type, $this->form, 
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

class previous_word_selector 
{
	public $word;

	function __construct($word) 
	{
		$this->word = $word;
	}

	public function match($previous_matches, $following_matches) 
	{
		return $this->word 
			? $previous_matches && end($previous_matches)->translator->identifier->base_form == $this->word
			: !$previous_matches;
	}
}

class next_class_selector 
{
	public $classes;

	function __construct($classes_str) 
	{
		$this->classes = explode('|', $classes_str);
	}

	public function match($previous_matches, $following_matches) 
	{
		return $following_matches && $this->match_classes($following_matches[0]->translator);
	}

	public function match_classes($translator) 
	{
		return is_array($translator)
			? $this->match_classes($translator[0])
			: in_array($translator->identifier->class, $this->classes);
	}
}

class noun_numerus_selector 
{
	protected function get_quantifier($previous_matches) 
	{
		$current_is_noun = true;
		foreach (array_reverse($previous_matches) as $previous_match) {
			$previous_translator = $previous_match->translator;
			if ($previous_translator->is_quantifier())
				return (int)$previous_match->phrase;
			if ($previous_translator->is_adjective())
				$current_is_noun = false; 
			else if (!($previous_translator->is_noun() && $current_is_noun))
				break; 
		}
		return null; 
	}
}

class singular_noun_selector extends noun_numerus_selector
{
	public function match($previous_matches, $following_matches) 
	{
		$quantifier = parent::get_quantifier($previous_matches);
		return $quantifier == 1;
	}
}

class plural_noun_selector extends noun_numerus_selector
{
	public function match($previous_matches, $following_matches) 
	{
		$quantifier = parent::get_quantifier($previous_matches);
		return $quantifier === 0 || $quantifier > 1;
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

	public function translate($lower_phrase, $translations_before, $translations_after) 
	{
		$connector = $translations_after ? ' ' : '';
		$translation = $this->do_translate($lower_phrase, $translations_before, $translations_after, $connector);
		return $translation ? $translation . $connector : '';
	}

	public function match($previous_matches, $following_matches)
	{
		return $this->match_static($previous_matches, $following_matches) 
		&& $this->identifier->match($previous_matches, $following_matches);
	}	

	protected function match_static($previous_matches, $following_matches) 
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
		return $this->identifier->class == 'pron';
	}

	public function is_quantifier() 
	{
		return $this->identifier->class == 'quant';
	}

	public function is_noun_modifier() {
		return $this->is_adjective() || $this->is_quantifier();
	}

	protected function do_translate($lower_phrase, $translations_before, $translations_after, &$connector) 
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
?>