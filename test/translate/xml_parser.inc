<?php
define('READY', 0);
define('BEGIN_TAG', 2);
define('BEGIN_CLOSE_TAG', 3);
define('OPEN_TAG', 4);
define('CLOSE_TAG', 5);
define('ATTRIBUTE_NAME', 6);
define('ATTRIBUTE_VALUE_START', 7);
define('ATTRIBUTE_VALUE', 8);
define('ATTRIBUTE_VALUE_END', 9);
define('TEXT', 10);
define('AFTER_ELEMENT', 11);

define('ROOT_NAME', 'root');

class xml_parser {

	private $element_stack = array();
	private $current_attribute = null;
	private $parse_log = "";
	private $current_text = "";
	private $state = READY;

	public static function parse($filename) 
	{
		$xml = file_get_contents('testcases.xml');
		$parser = new xml_parser();
		return $parser->_parse($xml);
	}

	public static function save($filename, $root) 
	{
		$text = $root->write_children();
		$data = mb_convert_encoding($text, 'ISO-8859-1');
		file_put_contents($filename, $data);
	}

	public static function create_root() 
	{
		return self::create_element(ROOT_NAME);
	}

	public static function create_element($name) 
	{
		return new Element($name);
	}

	public static function create_attribute($name, $value) 
	{
		$attribute = new Attribute($name);
		$attribute->value = $value;
		return $attribute;
	}

	private function _parse($xml) 
	{
		$this->add_element(ROOT_NAME);
		try {
			foreach (str_split($xml) as $char) {
				$this->parse_log .= $char;
				$new_state = $this->update_state($char);
				if ($this->state == $new_state 
					|| $new_state == TEXT 
					|| ($this->state == BEGIN_TAG && $new_state == OPEN_TAG))
					$this->current_text .= $char;
				else
					$this->current_text = "";	
				$this->state = $new_state;
			}
		}
		catch (Exception $ex) {
			throw new \Exception("INVALID FORMAT: " . $ex->getMessage() . " at " . $this->parse_log);
		}
		if (count($this->element_stack) != 1)
			throw new \Exception("Missing close tags");
		return $this->element_stack[0];
	}

	private function update_state($char) 
	{
		switch ($this->state) {
			case READY:
				if (!trim($char))
					return $this->state;
				if ($char == '<')
					return BEGIN_TAG;
				if (!$this->element_stack)
					throw new \Exception("Element expected");
				return TEXT;					
			case BEGIN_TAG:
				if ($char == '/')
					return CLOSE_TAG;
				return OPEN_TAG;					
			case BEGIN_CLOSE_TAG:
				if ($char == '/')
					return CLOSE_TAG;
				throw new \Exception("Malformed close tag");
			case OPEN_TAG:
				if ($char == '>' || $char == ' ') {				
					if (!$this->current_text)
						throw new \Exception("Empty opening tag");
					$this->add_element($this->current_text);
					return $char == '>' ? READY : ATTRIBUTE_NAME;
				}
				return $this->state;
			case CLOSE_TAG:
				if ($char == '>') {
					if (!$this->current_text)
						throw new \Exception("Empty close tag");
					else if ($this->current_text != $this->current_element()->name)
						throw new \Exception("Mismatching end tag, expected: " . $this->current_element()->name . " but was " . $this->current_text);
					array_pop($this->element_stack);
					return AFTER_ELEMENT;
				}
				return $this->state;
			case ATTRIBUTE_NAME:
				if ($char == '=') {
					if (!$this->current_text) 
						throw \Exception("Empty attribute name");
					$this->add_attribute($this->current_text);
					return ATTRIBUTE_VALUE_START;
				}
				return $this->state;
			case ATTRIBUTE_VALUE_START:
				if ($char == '"')
					return ATTRIBUTE_VALUE;
				throw \Exception("Malformed attribute");
			case ATTRIBUTE_VALUE:
				if ($char == '"') {
					if (!$this->current_text) 
						throw \Exception("Empty attribute value");
					$this->current_attribute->value = $this->current_text;
					return ATTRIBUTE_VALUE_END;
				}
				return $this->state;
			case ATTRIBUTE_VALUE_END:
				if ($char == ' ')
					return ATTRIBUTE_NAME;
				if ($char == '>')				
					return READY;
				throw \Exception("Unexpected character after attribute");
			case TEXT:
				if ($char == '<') {
					if (!$this->current_text)
						throw \Exception("Empty text");
					$this->current_element()->text = trim($this->current_text);
					return BEGIN_CLOSE_TAG;
				}
				return $this->state;
			case AFTER_ELEMENT:
				if (!trim($char))
					return $this->state;
				if ($char == '<')
					return BEGIN_TAG;
				throw \Exception("Unexpected character after element");
			default:
				throw new \Exception("Unknown state: " . $state);
		}
	}

	private function current_element() 
	{
		return end($this->element_stack);
	}

	private function add_element($name) 
	{
		$new_element = new Element($name);
		if ($this->element_stack)
			end($this->element_stack)->children[] = $new_element;
		$this->element_stack[] = $new_element;		
	}

	private function add_attribute($name) 
	{
		$this->current_attribute = new Attribute($name);
		$this->current_element()->attributes[] = $this->current_attribute;
	}
}

class Element 
{
	public $name;
	public $attributes;
	public $children;
	public $text;

	public function __construct($name) {
		$this->name = $name;
		$this->children = array();
		$this->attributes = array();
	}

	public function write($indent = 0) {
		$str = str_repeat("\t", $indent) . '<' . $this->name;
		foreach ($this->attributes as $attribute)
			$str .= ' ' . $attribute->write();
		$str .= '>' . PHP_EOL;
		if ($this->text)
			$str .= str_repeat("\t", $indent + 1) . $this->text . PHP_EOL;
		else 
			$str .= self::write_children($indent + 1);
		$str .= str_repeat("\t", $indent) . '</' . $this->name . '>' . PHP_EOL;
		return $str;
	}

	public function write_children($indent = 0) {
		$str = "";
		foreach ($this->children as $child)
			$str .= $child->write($indent);			
		return $str;
	}
}

class Attribute 
{
	public $name;
	public $value;

	public function __construct($name) 
	{
		$this->name = $name;
	}

	public function write() {
		return $this->name . '="' . $this->value . '"';
	}
}
?>