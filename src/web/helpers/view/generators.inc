<?php
	function __h1($text)
	{
		echo _h1($text);
	}

	function __h2($text)
	{
		echo _h2($text);
	}

	function __space($n = 1) 
	{
		echo _space($n);
	}

	function __br($n = 1) 
	{
		echo _br($n);
	}

	function __p($html) 
	{
		echo _p($html);
	}

	function __strong($text) 
	{
		echo _strong($text);
	}

	function __li($html) 
	{
		echo _li($html);
	}
	
	function __th($html, $class = null) 
	{
		echo _th($html, $class);
	}

	function __td($html, $class = null) 
	{
		echo _td($html, $class);
	}

	function __open_form($class = "standard-form") {
		echo '<form method="post" action="" class="' . $class . '">';
		general_helpers::initiate_csrf_protection();
	}

	function __link($label, $type, $action = null, $params = null, $class = null, $confirm = null) 
	{
		echo _link($label, $type, $action, $params, $class, $confirm);
	}

	function __label($text, $for) {
		echo _label($text, $for);
	}

	function __password($control_name, $control_label, $tab_index = 1) {
		echo _password($control_name, $control_label, $tab_index);
	}

	function __textfield($control_name, $control_label, $tab_index = 1, $values = null, $attributes = null) {
		echo _textfield($control_name, $control_label, $tab_index, $values, $attributes);
	}

	function __textarea($control_name, $control_label, $tab_index = 1, $values = null, $attributes = null) {
		echo _textarea($control_name, $control_label, $tab_index, $values, $attributes);
	}

	function __checkbox($control_name, $control_label, $value, $tab_index = 1, $checked_values = null)
	{
		echo _checkbox($control_name, $control_label, $value, $tab_index, $checked_values);
	}

	function __span($html, $class = null) 
	{
		echo _span($html, $class);
	}

	function __hidden($name, $value = "") 
	{
		echo _hidden($name, $value);
	}

	function __submit_and_close($label, $name = null, $confirm = null, $tab_index = 1) {
		__submit($label, $name, $confirm, $tab_index);
		echo '</form>';
	}

	function __submit($label, $name, $confirm, $tab_index) {
		echo _submit($label, $name, $confirm, $tab_index);
	}

	function __info($label, $data) {
		echo _info($label, $data);
	}

	function __action($label, $action, $params, $confirm = null) 
	{
		__open_form();
		foreach ($params as $key => $value)
			__hidden($key, $value);
		__submit_and_close($label, $action, $confirm);
	}

	function _h1($text) 
	{
		return '<h1>' . $text . '</h1>';
	}

	function _h2($text) 
	{
		return '<h2>' . $text . '</h2>';
	}

	function _br($n = 1) 
	{
		return $n ? '<br>' . _br($n - 1) : '';
	}

	function _space($n = 1) 
	{
		return $n ? '&nbsp;' . _space($n - 1) : '';
	}

	function _li($html) 
	{
		return '<li>' . $html . '</li>';
	}

	function _th($html, $class = null) 
	{
		if($class) return '<th class="' . $class . '">' . $html . '</th>';
		else return '<th>' . $html . '</th>';
	}

	function _td($html, $class = null) 
	{
		if($class) return '<td class="' . $class . '">' . $html . '</td>';
		else return '<td>' . $html . '</td>';
	}

	function _strong($text) 
	{
		return '<strong>' . $text . '</strong>';
	}

	function _label($text, $for) {
		return "<label for=\"$for\">$text</label>";
	}

	function _password($control_name, $control_label, $tab_index = 1) {
		return \View\controls::generate_password($control_name, $control_label, $tab_index);
	}

	function _textfield($control_name, $control_label, $tab_index = 1, $values = null, $attributes = null) {
		return \View\controls::generate_textfield($control_name, $control_label, $tab_index, $values, $attributes);
	}

	function _textarea($control_name, $control_label, $tab_index = 1, $values = null, $attributes = null) {
		return \View\controls::generate_textarea($control_name, $control_label, $tab_index, $values, $attributes);
	}

	function _checkbox($control_name, $control_label, $value, $tab_index = 1, $checked_values = null) {
		return \View\controls::generate_checkbox($control_name, $control_label, $value, $tab_index, $checked_values);
	}

	function _link($label, $type, $action = null, $params = null, $class = null, $confirm = null) 
	{
		return \View\controls::generate_internal_link($label, $type, $action, $params, $class, $confirm);
	}

	function _p($html) 
	{
		return '<p>' . $html . '</p>';
	}

	function _hidden($name, $value = "") 
	{
		return '<input type="hidden" name="' . $name . '" id="' . $name . '" value="' . $value . '">';
	}

	function _submit($label, $name, $confirm, $tab_index) {
		return "<input type=\"submit\"" . ($name ? " name=\"$name\"" : "") 
			. " style=\"width: auto;\" value=\"$label\" tabindex=\"$tab_index\""
			. ($confirm ? " onclick=\"return confirm('$confirm');\">" : ">");
	}

	function _info($label, $data) {
		return _strong($label . ": ") . $data . _br();		
	}

	function _span($html, $class = null) 
	{
		return "<span" . ($class ? " class=\"$class\"" : "") . ">$html</span>";
	}

	function _limit_with_ellipsis($text, $limit) 
	{
		return $text && strlen($text) > $limit
			? substr($text, 0, $limit - 3) . '...'
			: $text;
	}

