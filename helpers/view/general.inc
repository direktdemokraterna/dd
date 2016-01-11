<?php
namespace View;
class general 
{
	public static function get_value($parameter_name, $values = null) {
		$values = $values ? $values : $_POST;
		return isset($values[$parameter_name]) ? $values[$parameter_name] : '';
	}

	public static function open_div($classes, $id = null) {
		$div_tag = '<div class="' . $classes . '"';
		if (!empty($id))
			$div_tag .= ' id="' . $id . '"';
		$div_tag .= '>';
		echo $div_tag;
	}

	public static function open_span($classes = null) {
		echo("<span" . ($classes ? " class=\"$classes\">" : ">") . PHP_EOL);
	}

	public static function close_div() {
		echo('</div>' . PHP_EOL);
	}

	public static function close_span() {
		echo('</span>' . PHP_EOL);
	}

	public static function make_control_label($control_name, $control_label) {
		echo('<br><label for "' . $control_name . '">' . $control_label . '</label>');
	}	

	public static function get_from_action_for_url($actions) {
		return (in_array($_GET['action'], $actions) ? "&from_action=" . $_GET['action'] : '');
	}

	public static function make_html_from_wiki_text($wiki_text) {
		try {
			$html_text = \forum_helpers::replace_brackets_with_html_tags($wiki_text);
		}
		catch (\Exception $ex) {
			return "ERROR WHEN PARSING TEXT: " . $ex;
		}
		return nl2br($html_text);
	}

	public static function make_plaintext_from_wiki_text($wiki_text) {
		try {
			return \forum_helpers::remove_bbcode_tags($wiki_text);
		}
		catch (\Exception $ex) {
			return "ERROR WHEN PARSING TEXT: " . $ex;
		}
	}

	public static function db_result_to_json($db_result) {
		$list = array();
		foreach($db_result as $row){
			$map = array();
			foreach ($row as $key => $value)
				$map[$key] = $value;
			$list[] = $map;
		}
		$json = json_encode($list);
		return $json;
	}
}
?>
