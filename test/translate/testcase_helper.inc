<?php

define('TEST_FILENAME', 'testcases.xml');

class testcase_helper 
{
	public static function load() 
	{
		$xml_nodes = xml_parser::parse(TEST_FILENAME);
		$testcases = testcase_helper::generate($xml_nodes);
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

	public static function run_tests($testcases) 
	{
		foreach ($testcases as $case)
			$case->test();
	}

	public static function output($testcases, $hide_passed_tests = false, $page = 1) 
	{
		$hide_passed = isset($_POST['hide_passed']) ? $_POST['hide_passed'] : false;
		$hide_without_hint = isset($_POST['hide_without_hint']) ? $_POST['hide_without_hint'] : false;
		\I18n\controller::update_language("sv");
		__h1("Testfall");
		__hidden("showing_testcases", true);
		echo self::generate_hide_passed_control($hide_passed);
		echo self::generate_hide_without_hint_control($hide_without_hint);
		__br();
		$error_count = count(array_filter($testcases, function($case) 
			{
				return $case->success === false;
			}));
		if ($error_count)
			__span($error_count . " fel", "incorrect");
		else 
			__span("Inga fel", "correct");
		__br();
		self::output_testcases_list($testcases, $hide_passed, $hide_without_hint, $page);
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

	private static function output_testcases_list($all_cases, $hide_passed, $hide_without_hint, $page) 
	{
		$cases = $hide_passed
			? array_filter($all_cases, function($case) { return $case->success === false; })
			: $all_cases;
		if ($hide_without_hint)
			$cases = array_filter($cases, function($case) { return $case->hints; });
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
			$case->output($n);
		}
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

	private static function generate_hide_without_hint_control ($hide_without_hint)
	{
		$html = '<input type="checkbox" name="hide_without_hint"' .
			($hide_without_hint ? ' checked' : '') 
			. ' id="hide_without_hint" onchange="this.form.submit()"><label for "hide_without_hint">' 
			. "Dölj utan hint" . '</label>';
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
?>