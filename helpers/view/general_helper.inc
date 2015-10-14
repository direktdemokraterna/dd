<?php
namespace View;
class general_helper 
{
	public static function make_selector($control_name, $control_label, $tab_index, $options) {
		self::make_control_label($control_name, $control_label);
		self::open_select($control_name, $tab_index);
		foreach(array_keys($options) as $option_name){
			self::make_select_option($option_name, $options[$option_name], $control_name);
		}
		self::close_select();
	}

	public static function make_textfield($control_name, $control_label, $tab_index) {
		$value = self::get_posted_value($control_name);
		self::make_control_label($control_name, $control_label);
		echo('<input type="text" name="' . $control_name . '" id="' . $control_name . 
			'" tabindex="' . $tab_index . '" value="' . $value . '"></input>');
	}

	public static function make_textarea($control_name, $control_label, $tab_index) {
		$value = self::get_posted_value($control_name);
		self::make_control_label($control_name, $control_label);
		echo('<textarea name="' . $control_name . '" id="' . $control_name . 
			'" tabindex="' . $tab_index . '"">' . $value . '</textarea>');
	}

	public static function get_posted_value($parameter_name) {
		return isset($_POST[$parameter_name]) ? $_POST[$parameter_name] : '';
	}

	public static function open_div($class_name) {
		echo('<div class="' . $class_name . '">' . PHP_EOL);
	}

	public static function open_span($class_name) {
		echo('<span class="' . $class_name . '">' . PHP_EOL);
	}

	public static function close_div() {
		echo('</div>' . PHP_EOL);
	}

	public static function close_span() {
		echo('</span>' . PHP_EOL);
	}

	public static function make_internal_link($label, $type, $action, $params = null, $line_break = false, $class = null, $confirm = null) {
		$url = 'index.php?type=' . $type . '&action=' . $action . (empty($params) ? '' : '&' . $params);
		$href = 'href="' . $url . '"';
		$classAttr = ($class ? ' class="' . $class . '"'  : '');
		$onclick = ($confirm ? " return confirm('" . $confirm . "')" : '');
		echo '<a ' . $classAttr . $href . $onclick . '>' . $label . '</a>' . ($line_break ? '<br>' : '&nbsp;'); 
	}	

	private static function make_control_label($control_name, $control_label) {
		echo('<br><label for "' . $control_name . '">' . $control_label . '</label>');
	}	

	private static function open_select($control_name, $tab_index) {
		echo('<select name="' . $control_name . '" id="' . $control_name . '" tabindex="' . $tab_index . '">' . PHP_EOL);
	}	

	private static function close_select($control_name, $tab_index) {
		echo('</select>' . PHP_EOL);		
	}	

	private static function make_select_option($option_name, $option_label, $selected_parameter) {
		$selected_option = isset($_POST[$selected_parameter]) ? $_POST[$selected_parameter] : null;
		echo('<option value="' . $option_name . '"' . ($selected_option == $option_name ? ' selected' : '') . '>' . 
			$option_label . '</option>' . PHP_EOL);
	}
}
?>
