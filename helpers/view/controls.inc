<?php
namespace View;
class controls 
{
	public static function generate_password($control_name, $control_label, $tab_index = 1) {
		return self::generate_control_label($control_name, $control_label)
			. '<input type="password" name="' . $control_name . '" id="' . $control_name . 
			'" tabindex="' . $tab_index . '"></input>';
	}
	
	public static function generate_textfield($control_name, $control_label, $tab_index = 1, $values = null, $attributes = null) {
		$value = is_array($values) 
			? self::get_value($control_name, $values) 
			: $values;
		$element = '<input type="text" name="' . $control_name . '" id="' . $control_name . 
			'" tabindex="' . $tab_index . '" value="' . $value . '"';
		self::add_attributes($element, $attributes);
		$element .= '></input>';
		return self::generate_control_label($control_name, $control_label) . $element;
	}

	public static function generate_textarea($control_name, $control_label, $tab_index = 1, $values = null, $attributes = null) {
		$value = is_array($values) 
			? self::get_value($control_name, $values) 
			: $values;
		$element = '<textarea name="' . $control_name . '" id="' . $control_name . 
			'" tabindex="' . $tab_index . '"';
		self::add_attributes($element, $attributes);
		$element .= '>' . $value . '</textarea>';
		return self::generate_control_label($control_name, $control_label) . $element;
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

	public static function generate_checkbox($control_name, $control_label, $value, $tab_index = 1, $checked_values = null) {
		$checked_value = is_array($checked_values) 
			? self::get_value($control_name, $checked_values) 
			: $checked_values;
		return self::generate_control_label($control_name, $control_label)
			. '<input type="checkbox" name="' . $control_name . '" value="' . $value 
			. '" id="' . $control_name . '"' . ($checked_value ? " checked>" : ">");
	}

	public static function output_labeled_selector($control_name, $control_label, $options, $values = null, $attributes = null) {
		echo self::generate_control_label($control_name, $control_label);
		self::output_selector($control_name, $options, $values, $attributes);
	}

	public static function output_selector($control_name, $options, $values = null, $attributes = null) {
		$selected_option = is_array($values) 
			? self::get_value($control_name, $values) 
			: $values;
		self::open_select($control_name, $attributes);
		foreach($options as $key => $value){
			self::output_option($key, $selected_option, $value);
		}
		self::close_select();
	}

	public static function generate_internal_link($label, $type, $action = null, $params = null, $class = null, $confirm = null) {
		$url = 'index.php?type=' . $type . ($action ? '&action=' . $action : '') 
		. (empty($params) ? '' : '&' . $params);
		$href = 'href="' . $url . '"';
		$classAttr = ($class ? ' class="' . $class . '"'  : '');
		$onclick = ($confirm ? " onclick=\"return confirm('" . _t($confirm) . "')\"" : "");
		return '<a ' . $classAttr . $href . $onclick . '>' . $label . '</a>'; 
	}	

	public static function output_link_list($type, $links) {
		echo '<ul>';
		foreach (array_keys($links) as $action)
			__li(_link($links[$action], $type, $action));
		echo '</ul>';
	}

	public static function output_search_box($label, $type, $action, $tab_index = 1) {
		__h2(_t("Search " . $label));
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
		__link(_t("Back to the search result"), $_GET['type'], $_GET['from_action']);
		__br();
	}

	public static function output_text_editor($options)
	{
		$name = $options['name'];
		$legend = $options['legend'];
		$target_id = $options['target_id'];
		$submit_text = $options['submit_text'];
		$title_label = isset($options['title_label']) ? $options['title_label'] : null;
		$tab_index = isset($options['tab_index']) ? $options['tab_index'] : 1;

		$form_name = $name . '_form';
		$content_name = $name . '_content';
		$submit_name = $name . '__submit';

		$content = isset($_POST[$content_name]) 
			? $_POST[$content_name] 
			: (isset($options['content']) ? $options['content'] : '');

		echo '<form method="post" action="" id="' . $form_name . '" class="text-editor">';
		echo '<fieldset>';
		echo '<legend>' . $legend . '</legend>';
		__hidden("target_id", $target_id);
		if ($title_label) 
			__textfield($name . '_title', $title_label, $tab_index++);
		echo '<div id="format_buttons_div">';
		echo '<input type="button" id="format_buttons_b" accesskey="b" title="'. _t("Bold") .'" value="b" onClick="make_bold(\'' . $content_name . '\')">';
		echo '<input type="button" id="format_buttons_i" accesskey="i" title="'. _t("Italic") .'" value="i" onClick="make_italic(\'' . $content_name . '\')">';
		echo '<input type="button" id="format_buttons_u" accesskey="u" title="'. _t("Underline") .'" value="u" onClick="make_underline(\'' . $content_name . '\')">';
		echo '</div>';
		echo '<textarea name="' . $content_name . '" id="' . $content_name . '" tabindex="' 
			. $tab_index . '">' . $content . '</textarea><br>';
		echo '<input type="submit" id="' . $submit_name . '" value="' . $submit_text 
			. '" tabindex="' . ($tab_index + 1) . '">';
		echo '</fieldset>';
		echo '</form>';
	}

	public static function output_paging_row($page, $list_count, $url_without_page, $label = null) 
	{
		$paging_info = Paging_info::create($page, $list_count);
		general::open_div("paging_info");
		echo _span(_t("Showing ") . ($label ? "$label " : "") 
			. $paging_info->first_showed_post_number . " - " 
			. $paging_info->last_showed_post_number . _t(" of ") . $paging_info->post_count);
		if ($paging_info->post_count > POSTS_PER_PAGE) {
			general::open_span();
			self::output_page_links($paging_info->number_of_pages, $paging_info->page, 
				$url_without_page . "&page=");
			general::close_span();
		}
		general::close_div();
	}

	public static function generate_control_label($control_name, $control_label) {
		return '<br><label for "' . $control_name . '">' . $control_label . '</label>';
	}	

	private static function output_page_links ($number_of_pages, $current_page, $link_without_page_number)
	{
		echo "<span class=\"float-right\">";
		if($current_page > 1){
			$previous_page = $current_page - 1;
			echo "<a href=\"" . $link_without_page_number . $previous_page . "\"><</a> ";
		}
		for($i=1; $i<($number_of_pages+1); $i++){
			echo "&nbsp;&nbsp;&nbsp;";
			if($i != $current_page)
				echo "<a href=\"" . $link_without_page_number . $i . "\">" . $i . "</a> ";
			else
				echo "<strong>" . $i . "</strong> ";
		}
		if($current_page < $number_of_pages){
			echo "&nbsp;&nbsp;&nbsp;";
			$next_page = $current_page + 1;
			echo "<a href=\"" . $link_without_page_number . $next_page . "\">></a> ";
		}
		echo "</span>";
	}

	private static function get_value($parameter_name, $values = null) {
		$values = $values ? $values : $_POST;
		return isset($values[$parameter_name]) ? $values[$parameter_name] : '';
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

	private static function output_option($value, $selected_value, $label = null) {
		echo "<option value=\"" . $value . "\"" . ($value == $selected_value ? " selected" : "") . ">" 
		. ($label != null ? $label : $value) . "</option>" . PHP_EOL;
	}
}

class Paging_info 
{
	public $page;
	public $post_count;
	public $number_of_pages;
	public $first_showed_post_number;
	public $last_showed_post_number;

	public static function create($page, $post_count) {
		$instance = new Paging_info();
		$instance->page = $page;
		$instance->post_count = $post_count;
		$instance->number_of_pages = ceil($post_count / POSTS_PER_PAGE);
		$instance->first_showed_post_number = 1 + ($page - 1) * POSTS_PER_PAGE;
		$instance->last_showed_post_number = min($page * POSTS_PER_PAGE, $post_count);
		return $instance;
	}
}
?>
