<?php
	function __t($text, $hints = null) 
	{
		echo _t($text, $hints);
	}

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

	function __open_form($class = "standard-form") {
		echo '<form method="post" action="" class="' . $class . '">';
	}

	function __link($label, $type, $action = null, $params = null, $class = null, $confirm = null) 
	{
		echo _link($label, $type, $action, $params, $class, $confirm);
	}

	function __label($text, $for) {
		echo _label($text, $for);
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

	function _t($text, $hints = null) 
	{
		return \i18n\engine::translate($text, $hints);
	}

	function _h1($text) 
	{
		return _h(1, $text);
	}

	function _h2($text) 
	{
		return _h(2, $text);
	}

	function _br($n = 1) 
	{
		return $n ? '<br>' . _br($n - 1) : '';
	}

	function _space($n = 1) 
	{
		return $n ? '&nbsp;' . _space($n - 1) : '';
	}

	function _strong($text) 
	{
		return '<strong>' . $text . '</strong>';
	}

	function _label($text, $for) {
		return "<label for=\"$for\">$text</label>";
	}

	function _link($label, $type, $action = null, $params = null, $class = null, $confirm = null) 
	{
		return _link($label, $type, $action, $params, $class, $confirm);
	}

	function _li($html) 
	{
		return '<li>' . $html . '</li>';
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

	function _h($n, $text) 
	{
		return '<h$n>' . $text . '</h$n>';
	}

	function _limit_with_ellipsis($text, $limit) 
	{
		return $text && strlen($text) > $limit
			? substr($text, 0, $limit - 3) . '...'
			: $text;
	}
?>
