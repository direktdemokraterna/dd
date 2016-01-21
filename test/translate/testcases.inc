<?php

define('TEST_FILENAME', 'testcases.xml');

class testcases 
{
	public static function load() 
	{
		$xml_nodes = xml_parser::parse(TEST_FILENAME);
		$testcases = testcases::generate($xml_nodes);
		return $testcases;
	}

	public static function save($testcases) 
	{
		$testcases_xml = self::to_xml($testcases);
		xml_parser::save(TEST_FILENAME, $testcases_xml);
	}

	public static function empty_testcase() {
		$testcase = new Testcase();
		$testcase->from_language = 'en';
		$testcase->to_language = 'sv';
		return $testcase;
	}

	public static function output($testcases, $hide_passed_tests = false, $page = 1) 
	{
		$hide_passed = isset($_POST['hide_passed']) ? $_POST['hide_passed'] : 0;
		\I18n\controller::update_language("sv");
		__h1("Testfall");
		__hidden("showing_testcases", true);
		echo self::generate_hide_passed_control($hide_passed);
		__br();
		$n = 0;
		$result = array();
		$errors = 0;
		foreach ($testcases as $case) {
			$n++;
			$expected = $case->to_text;
			$actual = _t($case->from_text);
			$ok = ($expected == $actual);
			$result[] = $ok;
			if (!$ok) $errors++;
		}
		if ($errors)
			__span($errors . " fel", "incorrect");
		else 
			__span("Inga fel", "correct");
		__br();
		self::output_testcases_list($testcases, $result, $hide_passed, $page);
	}

	public static function output_testcases_list($all_cases, $result, $hide_passed, $page) 
	{
		if ($hide_passed) {
			$failed_cases = array();
			$n = 0;
			foreach ($all_cases as $case) {
				if (!$result[$n])
					$failed_cases[] = $case;
				$n++;
			}
			$cases = $failed_cases;
		}
		else $cases = $all_cases;

		$page_size = 50;
		$list_count = count($cases);
		if ($page_size * ($page - 1) >= $list_count)
			$page = 1;
		echo '<div style="width: 500px">';
		\View\controls::output_paging_row($page, $list_count, "testfall", $page_size);
		echo '</div>';
		$n = ($page - 1) * $page_size;
		$cases = array_slice($cases, $n, $page_size);
		foreach ($cases as $case) {
			if ($hide_passed) 
				$n = array_search($case, $all_cases);
			$n++;
			echo $n . ") " . $case->from_text;
			__space(4);
			echo '<input type="submit" name="remove" value="Ta bort ' . $n . '">';				
			echo _space(2) . '<input type="submit" name="test" value="Kör ' . $n . '">';				
			$ok = $result[$n - 1];
			$actual = _t($case->from_text);
			$output_class = $ok ? "correct" : "incorrect";
			__br();
			echo '<input type="text" class="' . $output_class . '" readonly value="' . $actual . '">';
			if (!$ok) 
				echo _space(3) . "Expected: " . $case->to_text . _br();
			__br();
		}
	}

	public static function get_testcase($index) 
	{
		$current_cases = self::load();
		return count($current_cases) > $index ? $current_cases[$index] : null;
	}

	public static function remove_at_index($index) 
	{
		$cases = self::load();
		array_splice($cases, $index, 1);
		self::save($cases);
	}

	public static function extract() {
		include("testcase_extractor.inc");
		$base_dir = dirname(dirname(__DIR__));
		$new_cases = testcase_extractor::extract($base_dir);
		$all_cases = $new_cases;
		self::sort_testcases($all_cases);
		self::remove_duplicates($all_cases);
		self::save($all_cases);
		return $all_cases;
	}

	public static function extract_test_index($value) {
		$parts = explode(' ', $value);
		$n = (int)end($parts);
		return $n - 1;
	}

	private static function generate($xml) 
	{
		if (!$xml->children) 
			return array();
		$cases_xml = $xml->children[0]->children;
		$cases = array();
		foreach ($cases_xml as $case_xml) {
			$case = Testcase::generate($case_xml);
			$cases[] = $case;
		}
		return $cases;
	}

	private static function generate_hide_passed_control ($hide_passed)
	{
		$html = '<input type="checkbox" name="hide_passed"' .
			($hide_passed ? ' checked' : '') 
			. ' id="hide_passed" onchange="this.form.submit()"><label for "hide_passed">' 
			. "Dölj klarade" . '</label>';
		return _span($html, "standard-form");
	}

	private static function sort_testcases(&$cases) {
		usort($cases, function($a, $b) {
			return strcmp($a->from_text, $b->from_text);
		});
	}

	private static function remove_duplicates(&$cases) {
		$len = count($cases);
		$prev = null;
		for ($i = 0; $i < $len; $i++) {
			$next = $cases[$i]->from_text;
			if ($next == $prev) {
				array_splice($cases, $i--, 1);
				$len--;	
			}
			$prev = $next;
		}
	}

	private static function to_xml($testcases) {
		$root = xml_parser::create_root();
		$cases_node = xml_parser::create_element('cases');
		$root->children[] = $cases_node;
		foreach ($testcases as $case)
			$cases_node->children[] = $case->to_xml();
		return $root;
	}
}

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
		$this->actual = _t($this->from_text, $translation_hints);		
		$this->success = $this->to_text == $this->actual;
		return $this->success;
	}

	public function output_class() {
		return $this->to_text ? ($this->success ? "correct" : "incorrect") : '';
	}

	public static function generate($xml) 
	{
		$case = new Testcase();
		$from_xml = $xml->children[0];
		if ($from_xml->name != 'when')
			throw new \Exception('First element must be when');
		$to_xml = $xml->children[1];
		if ($to_xml->name != 'then')
			throw new \Exception('Second element must be then');
		$from_lang_attr = $from_xml->attributes[0];
		if ($from_lang_attr->name != 'lang')
			throw new \Exception('First element must have lang attribute');
		$to_lang_attr = $to_xml->attributes[0];
		if ($from_lang_attr->name != 'lang')
			throw new \Exception('Second element must have lang attribute');
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
		return $case;
	}

	public function to_xml() {
		$case_node = xml_parser::create_element('case');
		$from_node = xml_parser::create_element('when');
		$case_node->children[] = $from_node;
		$to_node = xml_parser::create_element('then');
		$case_node->children[] = $to_node;
		$from_lang_attr = xml_parser::create_attribute('lang', $this->from_language);
		$from_node->attributes[] = $from_lang_attr;
		$from_node->text = $this->from_text;
		$to_lang_attr = xml_parser::create_attribute('lang', $this->to_language);
		$to_node->attributes[] = $to_lang_attr;
		$to_node->text = $this->to_text;
		return $case_node;
	}

	private static function get_translation_hints($hints_txt) {
		$parts = explode('=>', $hints_txt);
		return array($parts[0] => $parts[1]);
	}	
}
?>