<?php
namespace I18n;

class translation_match
{
	public $phrase;
	public $translation;

	function __construct($phrase, $translation) 
	{
		$this->phrase = $phrase;
		$this->translation = $translation;
	}

	public function translate($translations_before, $translations_after) 
	{
		$lower_translation = $this->translation->translate(strtolower($this->phrase), 
			$translations_before, $translations_after);
		return self::match_case($lower_translation, $this->phrase);
	}

	private static function match_case($target, $template) 
	{
		return (ctype_upper($template[0]) 
				? strtoupper($target[0]) 
				: strtolower($target[0]))
		. substr($target, 1);
	}		
}

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
			$selector = new previous_word_selector($matches[0]);
		}
		else $selector = null;
		$parts = explode(':', $identifier_str);
		$category = count($parts) == 2 ? $parts[1] : 'phrase';
		$key = $parts[0];
		preg_match('/\d+/', $category, $matches);
		$identifier = $matches
			? new translation_identifier($key, str_replace($matches[0], '', $category), (int)$matches[0])
			: new translation_identifier($key, $category, 1);
		$identifier->selector = $selector;
		return $identifier;
	}

	public function match($previous_matches) 
	{
		return !$this->selector || $this->selector->match($previous_matches);
	}

	public function copy($new_key, $new_selector = null) 
	{
		return new translation_identifier($new_key, $this->class, $this->type, $this->form, $new_selector);
	}

	function __construct($key, $class, $type = 1, $form = null, $selector = null) 
	{
		$this->key = $key;
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

	public function match($previous_matches) 
	{
		return $previous_matches && end($previous_matches)->translation->identifier->key == $this->word;
	}
}

class noun_numerus_selector 
{
	protected function get_quantifier($previous_matches) 
	{
		$current_is_noun = true;
		foreach (array_reverse($previous_matches) as $previous_match) {
			$previous_translation = $previous_match->translation;
			if ($previous_translation->is_quantifier())
				return (int)$previous_match->phrase;
			if ($previous_translation->is_adjective())
				$current_is_noun = false; 
			else if (!($previous_translation->is_noun() && $current_is_noun))
				break; 
		}
		return null; 
	}
}

class singular_noun_selector extends noun_numerus_selector
{
	public function match($translations_before) 
	{
		$quantifier = parent::get_quantifier($translations_before);
		return $quantifier == 1;
	}
}

class plural_noun_selector extends noun_numerus_selector
{
	public function match($translations_before) 
	{
		$quantifier = parent::get_quantifier($translations_before);
		return $quantifier === 0 || $quantifier > 1;
	}
}

class translator {
	public $identifier;		
	public $translation;

	function __construct($identifier, $translation = null) {
		$this->identifier = $identifier;
		$this->translation = $translation;
	}

	public function translate($lower_phrase, $translations_before, $translations_after) 
	{
		$connector = $translations_after ? ' ' : '';
		return $this->do_translate($lower_phrase, $translations_before, $translations_after, $connector) 
		. $connector;
	}

	public function is_noun() 
	{
		return $this->identifier->class == 'noun';
	}

	public function is_adjective() 
	{
		return $this->identifier->class == 'adj';
	}

	public function is_quantifier() 
	{
		return $this->identifier->key == '%d';
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
	private $base_translation;
	private $definite_translation;
	private $connector;

	function __construct($identifier, $form, $compact_translation, $indef_index, $def_index) 
	{
		$identifier->form = $form;
		parent::__construct($identifier);
		$parts = explode(':-', $compact_translation);
		$inflections = $parts[0];
		$this->connector = count($parts) == 2 ? $parts[1] : null;
		self::set_inflections($inflections, $indef_index, $def_index);
	}

	private function set_inflections($inflections, $indef_index, $def_index) {
		$parts = explode(':', $inflections);
		$this->base_translation = $parts[0];
		$this->translation = $indef_index 
			? self::assemble_word_form($parts, $indef_index)
			: $this->base_translation;
		$this->definite_translation = count($parts) > $def_index
			? self::create_word_form($this->translation, $parts[$def_index])
			: $this->translation;
	}

	protected function do_translate($lower_phrase, $translations_before, $translations_after, &$connector) 
	{
		if ($this->is_compound($translations_after)) {
			$connector = '';
			return parent::create_word_form($this->base_translation, $this->connector);
		}
		return self::is_definite($translations_before)
			? $this->definite_translation
			: $this->translation; 
	}

	private static function is_definite($translations_before) 
	{
		return $translations_before && get_class(end($translations_before)) == 'adjective_definite';
	}

	protected function is_compound($translations_after) 
	{
		return $this->connector !== null && $translations_after && $translations_after[0]->is_noun();
	}
}

class noun_singular extends noun 
{
	function __construct($identifier, $compact_translation) 
	{
		parent::__construct($identifier, 'singular', $compact_translation, 0, 2);
	}
}

class noun_plural extends noun 
{
	function __construct($identifier, $compact_translation) 
	{
		if (!$identifier->key) {
			$key_parts = explode(':', $compact_translation[BASE_LANG]);
			$identifier->key = self::assemble_word_form($key_parts, 1);			
		}
		parent::__construct($identifier, 'plural', $compact_translation[LANG], 1, 3);
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

	private static function make_adjective_compact_translation($verb_compact_translation) 
	{
		$verb_base_form_and_endings = explode(':', $verb_compact_translation[LANG], 3);
		$verb_base_form = $verb_base_form_and_endings[0];
		$perfect_participle_endings = parent::strip_parenthesis($verb_base_form_and_endings[2]);
		$adjective_compact_translation = parent::create_word_form($verb_base_form, $perfect_participle_endings);
		return $adjective_compact_translation;
	}
}
?>
