<?php
namespace I18n;

class translation_identifier 
{
	public $key;
	public $base_form;
	public $class;
	public $type;

	public $tempus;
	public $numerus;
	public $definite;

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
		preg_match(next_word_selector::$pattern, $identifier_str, $post_matches);
		if ($post_matches) {
			$identifier_str = str_replace($post_matches[0], '', $identifier_str);
			return new next_word_selector(translator::strip_parenthesis($post_matches[0]));
		}
		return null;
	}

	public function match($previous_matches, $following_matches, $restrictive = true) 
	{
		return !$this->selector || $this->selector->match($previous_matches, $following_matches, $restrictive);
	}

	public function copy($change_props = null) 
	{
		$copy = new translation_identifier($this->key
			, $this->class
			, $this->type
			, $this->tempus
			, $this->numerus
			, $this->definite
			, $this->selector
			, $this->base_form);
		if ($change_props)
			foreach ($change_props as $key => $value)
				$copy->$key = $value;
		return $copy;
	}

	function __construct($key, $class, $type = 1, $tempus = null, $numerus = null, $definite = false
		, $selector = null, $base_form = null) 
	{
		$this->key = $key;
		$this->base_form = $base_form ? $base_form : $key;
		$this->class = $class;
		$this->type = $type;	
		$this->tempus = $tempus;
		$this->numerus = $numerus;
		$this->definite = $definite;
		$this->selector = $selector;
	}
}
?>
