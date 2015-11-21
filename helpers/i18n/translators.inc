<?php
namespace I18n;

class translation_identifier 
{
	public $key;
	public $class;
	public $type;
	public $form;
	public $selector;

	public static function create($identifier_str) 
	{
		preg_match('/\[\w+\]/', $identifier_str, $matches);
		if ($matches) {
			$identifier_str = str_replace($matches[0], '', $identifier_str);
			$selector = $matches[0];
		}
		$parts = explode(':', $identifier_str);
		$category = count($parts) == 2 ? $parts[1] : 'phrase';
		$key = $parts[0];
		preg_match('/\d+/', $category, $matches);
		return $matches
			? new translation_identifier($key, str_replace($matches[0], '', $category), (int)$matches[0])
			: new translation_identifier($key, $category, 1);
	}

	public function match($previous) 
	{
		return !$this->selector || $selector == $previous->identifier->key;
	}

	public function copy($new_key) 
	{
		return new translation_identifier($new_key, $this->class, $this->type);
	}

	function __construct($key, $class, $type = 1, $form = null) 
	{
		$this->key = $key;
		$this->class = $class;
		$this->type = $type;	
		$this->form = $form;	
	}
}

class translator {
	public $identifier;		
	public $translation;

	function __construct($identifier, $translation) {
		$this->identifier = $identifier;
		$this->translation = $translation;
	}

	public function translate($lower_phrase, $translations_before, $translations_after) 
	{
		if ($lower_phrase != $this->identifier->key)
			throw new Exception("mismatched translation: " . $lower_phrase . " != " . $this->identifier->key);
		$connector = $translations_after ? ' ' : '';
		return $this->do_translate($lower_phrase, $translations_before, $translations_after, $connector) 
		. $connector;
	}

	public function is_noun() 
	{
		return $this->identifier->class == 'noun';
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
		$suffix = str_replace('_', '', $ending);
		$del_char_count = strlen($ending) - strlen($suffix);
		$word_stem = substr($base_form, 0, strlen($base_form) - $del_char_count);
		return $word_stem . $suffix;
	}

	protected static function strip_parenthesis($text_in_parenthesis) 
	{
		return substr($text_in_parenthesis, 1, strlen($text_in_parenthesis) - 2);
	}
}

class adjective extends translator
{
	public $translation_noun2;
	public $translation_plural;
	public $has_definite_form;

	function __construct($identifier, $compact_translation) 
	{
		$parts = explode(':', $compact_translation);
		$singular_parts = explode('|', $parts[0]);
		$singular = $singular_parts[0];
		$alt_singular_ending = $singular_parts[1];
		$plural_ending = $parts[1];
		parent::__construct($identifier, $singular);
		$this->has_definite_form = (count($parts) > 2);
		$this->translation_noun2 = parent::create_word_form($singular
			, $alt_singular_ending);
		$this->translation_plural = parent::create_word_form($singular, $plural_ending);
	}

	protected function do_translate($lower_phrase, $translations_before, $translations_after, &$connector) 
	{
		$significant_noun = self::get_significant_noun($translations_after);
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

	private static function get_significant_noun($translations_after) 
	{
		$found_noun = null;
		foreach ($translations_after as $next_translation) {
			if ($next_translation->is_noun())
				$found_noun = $next_translation;				
			else if ($found_noun)
				return $found_noun; 
		}
		return $found_noun;
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
		parent::__construct($identifier->copy($definite_key), $definite_translation);
	}
}

class noun extends translator 
{
	private $definite_translation;

	function __construct($identifier, $indefinite_translation, $definite_translation, $form) 
	{
		$identifier->form = $form;
		parent::__construct($identifier, $indefinite_translation);
		$this->definite_translation = $definite_translation;
	}

	protected function do_translate($lower_phrase, $translations_before, $translations_after, &$connector) 
	{
		return self::is_definite($translations_before)
			? $this->definite_translation
			: $this->translation; 
	}

	private static function is_definite($translations_before) 
	{
		return $translations_before && get_class(end($translations_before)) == 'adjective_definite';
	}
}

class noun_singular extends noun 
{
	private $connector;

	function __construct($identifier, $compact_translation) 
	{
		$parts = explode(':-', $compact_translation);
		$inflections = $parts[0];
		$connector = count($parts) == 2 ? $parts[1] : null;
		$parts = explode(':', $inflections);
		$indefinite_translation = $parts[0];
		$definite_translation = count($parts) > 2 
			? parent::create_word_form($indefinite_translation, $parts[2])
			: $indefinite_translation;
		parent::__construct($identifier, $indefinite_translation, $definite_translation, 'singular');
		$this->connector = $connector;
	}

	protected function do_translate($lower_phrase, $translations_before, $translations_after, &$connector) 
	{
		if ($this->is_compound($translations_after)) {
			$connector = '';
			return parent::create_word_form($this->translation, $this->connector);
		}
		return parent::do_translate($lower_phrase, $translations_before, $translations_after, $connector);
	}

	protected function is_compound($translations_after) 
	{
		return $this->connector !== null && $translations_after && $translations_after[0]->is_noun();
	}
}

class noun_plural extends noun 
{
	function __construct($identifier, $compact_translation) 
	{
		$key_parts = explode(':', $compact_translation[BASE_LANG]);
		$plural_key = self::assemble_word_form($key_parts, 1);
		$translation_parts = explode(':', $compact_translation[LANG]);
		$indefinite_translation = self::assemble_word_form($translation_parts, 1);
		$definite_translation = self::assemble_word_form($translation_parts, 3, $indefinite_translation);
		parent::__construct($identifier->copy($plural_key), $indefinite_translation, 
			$definite_translation, 'plural');
	}
}

class verb_infinitive extends translator 
{
	public $has_perfect;
	public $has_perfect_participle;

	function __construct($identifier, $compact_translation) 
	{
		$parts = explode(':', $compact_translation);
		parent::__construct($identifier, $parts[0]);
		$this->has_perfect = (count($parts) > 1);
		$this->has_perfect_participle = (count($parts) > 2);
	}
}

class verb_perfect extends translator 
{
	function __construct($identifier, $compact_translation) 
	{
		$perfect_key = self::assemble_word_form(explode(':', $compact_translation[BASE_LANG]), 1);
		$perfect_translation = self::assemble_word_form(explode(':', $compact_translation[LANG]), 1);
		parent::__construct($identifier->copy($perfect_key), $perfect_translation);
	}
}

class verb_perfect_participle extends adjective
{
	function __construct($identifier, $compact_translation) 
	{
		$base_parts = explode(':', $compact_translation[BASE_LANG]);
		$adjective_key = parent::assemble_word_form($base_parts, 2);
		$adjective_compact_translation = self::make_adjective_compact_translation($compact_translation);
		parent::__construct(new translation_identifier($adjective_key, 'adj'),
			$adjective_compact_translation);
	}

	private static function make_adjective_compact_translation($verb_compact_translation) {
		$verb_base_form_and_endings = explode(':', $verb_compact_translation[LANG], 3);
		$verb_base_form = $verb_base_form_and_endings[0];
		$perfect_participle_endings = parent::strip_parenthesis($verb_base_form_and_endings[2]);
		$adjective_compact_translation = self::replace_adjective_suffix_with_base_form($verb_base_form, $perfect_participle_endings);
		return $adjective_compact_translation;
	}

	private static function replace_adjective_suffix_with_base_form($verb_base_form, 
		$perfect_participle_endings) {
		$adjective_suffix_and_endings = explode('|', $perfect_participle_endings);
		$adjective_suffix = $adjective_suffix_and_endings[0];
		$adjective_endings = $adjective_suffix_and_endings[1];
		$adjective_base_form = parent::create_word_form($verb_base_form, $adjective_suffix);
		$adjective_compact_translation = implode('|', array($adjective_base_form, $adjective_endings));
		return $adjective_compact_translation;
	}
}
?>
