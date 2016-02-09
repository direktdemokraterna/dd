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

	public $pre_selector;
	public $post_selector;

	public static function create($identifier_str) 
	{
		$pre_selector = self::extract_word_selector($identifier_str
			, word_selector::$previous_word_pattern);
		$post_selector = self::extract_word_selector($identifier_str
			, word_selector::$next_word_pattern);
		$parts = util::split_word_forms($identifier_str);
		$category = count($parts) == 2 ? $parts[1] : 'phrase';
		$key = $parts[0];
		preg_match('/\d+/', $category, $type_matches);
		$identifier = $type_matches
			? new translation_identifier($key, str_replace($type_matches[0], '', $category), (int)$type_matches[0])
			: new translation_identifier($key, $category, 1);
		$identifier->pre_selector = $pre_selector;
		$identifier->post_selector = $post_selector;
		return $identifier;
	}

	private static function extract_word_selector(&$identifier_str, $word_pattern) 
	{
		preg_match($word_pattern, $identifier_str, $matches);
		if (!$matches)
			return null;
		$identifier_str = str_replace($matches[0], '', $identifier_str);
		return new word_selector(self::strip_parenthesis($matches[0]));
	}

	public function match_selectors($previous_identifier, $next_identifier) 
	{
		return (!$this->pre_selector || $this->pre_selector->match($previous_identifier))
			&& (!$this->post_selector || $this->post_selector->match($next_identifier));
	}

	public function copy($change_props = null) 
	{
		$copy = new translation_identifier($this->key, $this->class, $this->type);
		$copy->tempus = $this->tempus;
		$copy->numerus = $this->numerus;
		$copy->definite = $this->definite;
		$copy->base_form = $this->base_form;
		$copy->pre_selector = $this->pre_selector;
		$copy->post_selector = $this->post_selector;
		if ($change_props)
			foreach ($change_props as $key => $value)
				$copy->$key = $value;
		return $copy;
	}

	private static function strip_parenthesis($text_in_parenthesis) 
	{
		return substr($text_in_parenthesis, 1, strlen($text_in_parenthesis) - 2);
	}

	function __construct($key, $class, $type = 1) 
	{
		$this->key = $key;
		$this->base_form = $key;
		$this->class = $class;
		$this->type = $type;	
		$this->tempus = null;
		$this->numerus = null;
		$this->definite = false;
	}
}
?>
