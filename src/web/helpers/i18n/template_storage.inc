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
		foreach ($compact_templates as $from_pattern => $to_order)
			$templates[] = new template($priority++, $from_pattern, $to_order);			
		return self::make_children($templates);
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
			if ($node->word_form == $word_form) {
				$node->update_lengths($template, $level);
				return $node;				
			}
		$node = self::make_branch_node($template, $word_form, $level);
		$nodes[] = $node;
		return $node;
	}

	private static function make_leaf_node($template) 
	{
		$node = new template_node();
		$node->template = $template;
		$node->best_priority = $template->priority;
		$node->max_length = $node->min_length = count($template->from_sequence);
		$node->best_priority = $template->priority;
		return $node;
	}

	private static function make_branch_node($template, $word_form, $level) 
	{
		$node = new template_node();
		$node->word_form = $word_form;
		$node->best_priority = $template->priority;
		$node->update_lengths($template, $level);
		return $node;
	}
}

class template_node 
{
	public $word_form;
	public $children = array();
	public $template;
	public $best_priority;
	public $max_length = 0;
	public $min_length = PHP_INT_MAX;

	public function update_lengths($template, $level) 
	{
		$template_length = count($template->from_sequence);
		$this->min_length = min($this->min_length, $template_length);
		$this->max_length = max($this->max_length, $template_length
			+ self::count_nouns(array_slice($template->from_sequence, $level)));		
	}

	private static function count_nouns($word_forms) 
	{
		$sum = 0;
		foreach ($word_forms as $word_form)
			if ($word_form->class == 'noun')
				$sum++;
		return $sum;
	}
}
?>
