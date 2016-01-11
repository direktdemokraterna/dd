<?php
namespace View;
class general 
{
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

	public static function get_from_action_for_url($actions) {
		return (in_array($_GET['action'], $actions) ? "&from_action=" . $_GET['action'] : '');
	}
}
?>
