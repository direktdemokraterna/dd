<?php
namespace I18n;

class template_storage 
{
	private static $templates = null;

	public static function get_templates() 
	{
		if (self::$templates == null)
			self::$templates = self::expand_templates();
		return self::$templates;
	}

	private static function expand_templates() 
	{
		$templates = array();
		$compact_templates = templates::create_templates();
		$priority = 0;
		foreach ($compact_templates as $from => $to)
			$templates[] = self::expand_template($priority++, $from, $to);
		return $templates;
	}

	private static function expand_template($priority, $from, $to) 
	{
		$from_pattern = self::expand_pattern($from);
		$to_pattern = self::expand_pattern($to);
		return new template($priority, $from_pattern, $to_pattern, $from);
	}

	private static function expand_pattern($pattern) 
	{
		$word_parts = self::split_word_patterns($pattern);
		$word_forms = array_map('self::expand_word_form', $word_parts);
		return $word_forms;
	}

	private static function split_word_patterns($pattern) 
	{
		$word_parts = array();
		$word_part = '';
		foreach (str_split($pattern) as $char) {
			if (ctype_upper($char) && $word_part) {
				$word_parts[] = $word_part;
				$word_part = '';
			}
			$word_part .= $char;
		}
		$word_parts[] = $word_part;
		return $word_parts;
	}

	private static function expand_word_form($word_part) 
	{
		$class = templates::expand_class($word_part[0]);
		$modifiers = templates::expand_modifiers(substr($word_part, 1));
		return new word_form($class, $modifiers);
	}
}
?>
