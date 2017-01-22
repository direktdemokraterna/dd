<?php

class Testcase {
	public $from_text;
	public $from_language;
	public $to_text;
	public $to_language;
	public $hints;
	public $actual;
	public $success;

	public function test() {
		$translation_hints = $this->hints 
			? self::get_translation_hints($this->hints) 
			: null;
		$this->actual = \i18n\rule_engine::translate($this->from_text, $translation_hints);		
		$this->success = $this->to_text
			? $this->to_text == $this->actual
			: null;
	}

	public function output($n) 
	{
		echo $n . ") " . $this->from_text;
		__space(3);
		echo $this->hints ? $this->hints : 'No hints';
		__space(3);
		echo '<input type="submit" name="remove" value="Ta bort ' . $n . '">';				
		echo _space(2) . '<input type="submit" name="test" value="Kör ' . $n . '">';				
		__br();
		echo '<input type="text" class="' . $this->get_output_class() . '" readonly value="' . $this->actual . '">';
		if ($this->success === false) 
			echo _space(3) . "Expected: " . $this->to_text . _br();
		__br();
	}

	public function get_output_class() {
		return $this->success === null 
			? '' 
			: ($this->success ? "correct" : "incorrect");
	}

	public static function generate($xml) 
	{
		$case = new Testcase();
		$hints_attr = $xml->attributes['hints'];
		$success_attr = $xml->attributes['success'];
		$from_xml = $xml->children[0];
		if ($from_xml->name != 'when')
			throw new \Exception('First element must be when');
		$to_xml = $xml->children[1];
		if ($to_xml->name != 'then')
			throw new \Exception('Second element must be then');
		$from_lang_attr = $from_xml->attributes['lang'];
		$to_lang_attr = $to_xml->attributes['lang'];
		$last_run = isset($xml->children[2]) ? $xml->children[2] : null;
		if ($last_run && $last_run->name != 'last_run')
			throw new \Exception('Third element must be last_run');

		$hints = $hints_attr->value;
		$success = self::parse_success($success_attr->value);
		$from_lang = $from_lang_attr->value;
		if ($from_lang != 'en')
			throw new \Exception('First language must be en');
		$to_lang = $to_lang_attr->value;
		if ($to_lang != 'sv')
			throw new \Exception('Second language must be sv');
		$case->from_language = $from_lang;
		$case->from_text = $from_xml->text;
		$case->to_language = $to_lang;
		$case->to_text = $to_xml->text;
		$case->hints = $hints;
		$case->actual = $last_run ? $last_run->text : null;
		$case->success = $success;
		return $case;
	}

	public function to_xml() {
		$case_node = xml_parser::create_element('case');

		$hints_attr = xml_parser::create_attribute('hints', $this->hints);
		$case_node->attributes['hints'] = $hints_attr;

		$success_attr = xml_parser::create_attribute('success', self::success_to_string($this->success));
		$case_node->attributes['success'] = $success_attr;

		$from_node = xml_parser::create_element('when');
		$from_node->text = $this->from_text;
		$from_lang_attr = xml_parser::create_attribute('lang', $this->from_language);
		$from_node->attributes['lang'] = $from_lang_attr;

		$to_node = xml_parser::create_element('then');
		$to_node->text = $this->to_text;
		$to_lang_attr = xml_parser::create_attribute('lang', $this->to_language);
		$to_node->attributes['lang'] = $to_lang_attr;

		$last_run_node = xml_parser::create_element('last_run');
		$last_run_node->text = $this->actual;

		$case_node->children[] = $from_node;
		$case_node->children[] = $to_node;
		$case_node->children[] = $last_run_node;

		return $case_node;
	}

	private static function parse_success($success) 
	{
		switch ($success) {
			case 'true':
				return true;
			case 'false':
				return false;
			default:
				return null;
		}
	}

	private static function success_to_string($success) 
	{
		return $success ? 'true' : ($success === null ? '' : 'false');
	}

	private static function get_translation_hints($hints_txt) 
	{
		$segments = explode(',', $hints_txt);
		$hints = array();
		foreach ($segments as $segment) {
			$parts = explode('=>', $segment);
			$hints[$parts[0]] = $parts[1];
		}
		return $hints;
	}
}
?>