<?php
namespace I18n;

class template_storage 
{
	private static $templates = null; // tree

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
		return self::make_children($templates);
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
		return new word_form($class, $modifiers, $word_part);
	}

	private static function make_children($templates, $level = 0) 
	{
		$child_nodes = array();
		foreach ($templates as $template) 
			self::add_template_as_child($child_nodes, $template, $level);
		return $child_nodes;
	}

	private static function add_template_as_child(&$child_nodes, $template, $level) 
	{
		$node = self::produce_node($child_nodes, $template, $level);
		if ($level == count($template->from_sequence) - 1)
			$node->children[] = self::make_leaf_node($template);
		else self::add_template_as_child($node->children, $template, $level + 1);
	}

	private static function produce_node(&$nodes, $template, $level) 
	{
		$word_form = $template->from_sequence[$level];
		foreach ($nodes as $node)
			if ($node->word_form == $word_form)
				return $node;
		$node = self::make_branch_node($template, $word_form);
		$nodes[] = $node;
		return $node;
	}

	private static function make_leaf_node($template) 
	{
		$node = new template_node();
		$node->template = $template;
		$node->best_priority = $template->priority;
		return $node;
	}

	private static function make_branch_node($template, $word_form) 
	{
		$node = new template_node();
		$node->word_form = $word_form;
		$node->best_priority = $template->priority;
		return $node;
	}
}

class template_node 
{
	public $word_form;
	public $children = array();
	public $template;
	public $best_priority;
}
?>
