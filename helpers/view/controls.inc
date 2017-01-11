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

	public static function output_paging_row($page, $list_count, $label = null
		, $page_size = POSTS_PER_PAGE) 
	{
		$paging_info = Paging_info::create($page, $list_count, $page_size);
		general::open_div("paging_info");
		echo _span(_t("Showing ") . ($label ? "$label " : "") 
			. $paging_info->first_showed_post_number . " - " 
			. $paging_info->last_showed_post_number . _t(" of ") . $paging_info->post_count);		
		if ($paging_info->post_count > $page_size) {
			general::open_span();
			self::output_page_links($paging_info->number_of_pages, $paging_info->page);
			general::close_span();
		}
		general::close_div();
	}

	public static function output_grid_view($columns, $rows, $row_styles = null, $column_classes = null) 
	{
		$col_count = count($columns);
		echo '<table class="grid_view">';
		self::output_grid_view_header($columns, $column_classes);
		self::output_grid_view_rows(count($columns), $rows, $row_styles, $column_classes);
		echo '</table>';
	}	

	private static function output_grid_view_header($columns, $column_classes) 
	{
		echo '<tr>';
		$query_params = \Logic\util::get_request_params();
		$old_sort = isset($query_params['sort']) ? $query_params['sort'] : 0;
		$params_except_sort_value = self::generate_params_except_sort_value($query_params);
		$col = 0;
		foreach ($columns as $column) 
			if ($column){
				$col++;
				__th(_link($column . ($col == $old_sort 
					? ' &#x25B2' 
					: ($col == -$old_sort ? ' &#x25BC' : ''))
					, $query_params['type']
					, isset($query_params['action']) ? $query_params['action'] : null
					, $params_except_sort_value . ($col == $old_sort ? -$col : $col)), isset($column_classes[$col-1]) ? $column_classes[$col-1] : null);
			}
			else 
				__th("");
		echo '</tr>';
	}	

	private static function generate_params_except_sort_value($query_params) 
	{
		unset($query_params['sort']);
		$param_str = \Logic\util::make_param_string($query_params);
		return $param_str ? $param_str . "&sort=" : "sort=";
	}	

	private static function output_grid_view_rows($col_count, $rows, $row_styles = null, $column_classes) 
	{
		$i = 0;
		foreach($rows as $row) {
			$classes = $i % 2 ? "even_row" : "odd_row";
			if ($row_styles && $row_styles[$i]) 
				$classes .= ' ' . $row_styles[$i];
			echo "<tr class='$classes'>";
			for ($col = 0; $col < $col_count; $col++)
				__td($row[$col], isset($column_classes[$col]) ? $column_classes[$col] : null);
			echo '</tr>';
			$i++;			
		}
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
		echo '<input onClick="this.select();" tabindex="' . $tab_index++ . '" type="text" value="' . 
		$value . '" name="' . $search_input_name . '" class="sidebar_search_input">';
		echo '<div class="align-right">';
		echo '<input tabindex="' . $tab_index . '" type="submit" class="sidebar_search_submit" value="' 
		. _t('Search') . '">';
		echo '</div>';
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

		echo '<form method="post" action="" id="' . $form_name . '" class="text-editor anchor-form scroll">';
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
		echo '<div class="align-center">';
		echo '<input type="submit" id="' . $submit_name . '" value="' . $submit_text 
			. '" tabindex="' . ($tab_index + 1) . '">';
		echo '</div>';
		echo '</fieldset>';
		echo '</form>';
	}

	public static function generate_control_label($control_name, $control_label) {
		return '<br><label for "' . $control_name . '">' . $control_label . '</label>';
	}	

	private static function output_page_links ($number_of_pages, $page)
	{
		$query = \Logic\util::get_request_params();
		unset($query['page']);
		$params_except_page_number = \Logic\util::make_param_string($query) . "&page=";
		echo "<span class=\"float-right\">";
		if($page > 1)
			self::output_page_link('<', $query, $params_except_page_number . ($page - 1));
		for($i=1; $i<($number_of_pages+1); $i++){
			__space(3);
			if($i == $page)
				__strong($i);
			else
				self::output_page_link($i, $query, $params_except_page_number . $i);
		}
		if($page < $number_of_pages){
			__space(3);
			self::output_page_link('>', $query, $params_except_page_number . ($page + 1));
		}
		echo "</span>";
	}

	private static function output_page_link ($label, $query, $params_string)
	{
		if (isset($query['type'])) {
			__link($label, $query['type'], isset($query['action']) ? $query['action'] : null
				, "$params_string");
		}
		else {
			$url = "//" . $_SERVER['HTTP_HOST'] . $_SERVER['PHP_SELF'] . "?$params_string";
			echo "<a href='$url'>$label</a>";
		}
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

	public static function create($page, $post_count, $page_size = POSTS_PER_PAGE) {
		$instance = new Paging_info();
		$instance->page = $page;
		$instance->post_count = $post_count;
		$instance->number_of_pages = ceil($post_count / $page_size);
		$instance->first_showed_post_number = 1 + ($page - 1) * $page_size;
		$instance->last_showed_post_number = min($page * $page_size, $post_count);
		return $instance;
	}
}
?>
