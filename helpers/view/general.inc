<?php
namespace View;
class general 
{
	public static function make_password($control_name, $control_label, $tab_index = 1) {
		self::make_control_label($control_name, $control_label);
		echo('<input type="password" name="' . $control_name . '" id="' . $control_name . 
			'" tabindex="' . $tab_index . '"></input>');
	}

	public static function make_textfield($control_name, $control_label, $tab_index = 1, $values = null, $attributes = null) {
		$value = is_array($values) 
			? self::get_value($control_name, $values) 
			: $values;
		self::make_control_label($control_name, $control_label);
		$element = '<input type="text" name="' . $control_name . '" id="' . $control_name . 
			'" tabindex="' . $tab_index . '" value="' . $value . '"';
		self::add_attributes($element, $attributes);
		$element .= '></input>';
		echo $element;
	}

	public static function make_textarea($control_name, $control_label, $tab_index = 1, $values = null, $attributes = null) {
		$value = is_array($values) 
			? self::get_value($control_name, $values) 
			: $values;
		self::make_control_label($control_name, $control_label);
		$element = '<textarea name="' . $control_name . '" id="' . $control_name . 
			'" tabindex="' . $tab_index . '"';
		self::add_attributes($element, $attributes);
		$element .= '>' . $value . '</textarea>';
		echo $element;
	}

	public static function output_grid_view($columns, $rows, $row_styles = null) 
	{
		$col_count = count($columns);
		echo '<table class="grid_view"><tr>';
		foreach ($columns as $column)
			echo '<td>' . $column . '</td>';
		$i = 0;
		foreach($rows as $row) {
			$classes = $i % 2 ? "even_row" : "odd_row";
			if ($row_styles && $row_styles[$i]) 
				$classes .= ' ' . $row_styles[$i];
			echo "<tr class='$classes'>";
			for ($col = 0; $col < $col_count; $col++)
				echo '<td>' . $row[$col] . '</td>';
			echo '</tr>';
			$i++;			
		}
		echo '</table>';
	}	

	public static function make_checkbox($control_name, $control_label, $value, $tab_index = 1, $checked_values = null) {
		$checked_value = is_array($checked_values) 
			? self::get_value($control_name, $checked_values) 
			: $checked_values;
		self::make_control_label($control_name, $control_label);
		echo '<input type="checkbox" name="' . $control_name . '" value="' . $value 
			. '" id="' . $control_name . '"' . ($checked_value ? " checked>" : ">");
	}

	public static function make_labeled_selector($control_name, $control_label, $options, $values = null, $attributes = null) {
		self::make_control_label($control_name, $control_label);
		self::make_selector($control_name, $options, $values, $attributes);
	}

	public static function make_selector($control_name, $options, $values = null, $attributes = null) {
		$selected_option = is_array($values) 
			? self::get_value($control_name, $values) 
			: $values;
		self::open_select($control_name, $attributes);
		foreach($options as $key => $value){
			self::make_option($key, $selected_option, $value);
		}
		self::close_select();
	}

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

	public static function open_span($classes) {
		echo('<span class="' . $classes . '">' . PHP_EOL);
	}

	public static function close_div() {
		echo('</div>' . PHP_EOL);
	}

	public static function close_span() {
		echo('</span>' . PHP_EOL);
	}

	public static function output_internal_link($label, $type, $action = null, $params = null, $class = null, $confirm = null) {
		echo self::generate_internal_link($label, $type, $action, $params, $class, $confirm);
	}	

	public static function generate_internal_link($label, $type, $action = null, $params = null, $class = null, $confirm = null) {
		$url = 'index.php?type=' . $type . ($action ? '&action=' . $action : '') 
		. (empty($params) ? '' : '&' . $params);
		$href = 'href="' . $url . '"';
		$classAttr = ($class ? ' class="' . $class . '"'  : '');
		$onclick = ($confirm ? " onclick=\"return confirm('" . _t($confirm) . "')\"" : "");
		return '<a ' . $classAttr . $href . $onclick . '>' . $label . '</a>'; 
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

	public static function output_link_list($type, $links) {
		echo '<ul>';
		foreach (array_keys($links) as $action)
			echo '<li>' . self::generate_internal_link($links[$action], $type, $action) . '</li>';
		echo '</ul>';
	}

	public static function output_search_box($label, $type, $action, $tab_index = 1) {
		_h2(_t("Search " . $label));
		$search_input_name = \Logic\util::get_search_input_name($type, $action);
		$value = isset($_SESSION[$search_input_name]) ? $_SESSION[$search_input_name] : '';
		echo '<form method="post" class="sidebar_search_form" action="index.php?type=' 
		. $type . '&action=' . $action . '">';
		echo '<input tabindex="' . $tab_index++ . '" type="text" value="' . 
		$value . '" name="' . $search_input_name . '" class="sidebar_search_input">';
		echo '<input tabindex="' . $tab_index . '" type="submit" class="sidebar_search_submit" value="' 
		. _t('Search') . '">';
		echo '</form>';
	}

	public static function output_search_back_link() {
		_link(_t("Back to the search result"), $_GET['type'], $_GET['from_action']);
		_br();
	}

	private static function add_attributes(&$element, $attributes) {
		if ($attributes)
			foreach ($attributes as $key => $value)
				$element .= ' ' . $key . '="' . $value . '"';
	}

	private static function open_select($control_name, $attributes) {
		echo('<select name="' . $control_name . '" id="' . $control_name . '"'
			. ($attributes != null ? ' ' . $attributes : '') . '>' . PHP_EOL);
	}	

	private static function close_select() {
		echo('</select>' . PHP_EOL);		
	}	

	private static function make_option($value, $selected_value, $label = null) {
		echo "<option value=\"" . $value . "\"" . ($value == $selected_value ? " selected" : "") . ">" 
		. ($label != null ? $label : $value) . "</option>" . PHP_EOL;
	}
}
?>
