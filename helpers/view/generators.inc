<?php
	function _li($content) 
	{
		echo '<li>' . $content . '</li>';
	}

	function _p($text = null) 
	{
		echo '<p>' . $text ? $text . '</p>' : '<p>';
	}

	function __p() 
	{
		echo '</p>';
	}

	function _strong($text) 
	{
		echo '<strong>' . $text . '</strong>';
	}

	function _br($n = 1) 
	{
		for ($i = 0; $i < $n; $i++)
			echo '<br>';
	}

	function _open_form($class = "standard-form") {
		echo '<form method="post" action="" class="' . $class . '">';
	}

	function _hidden($name, $value) 
	{
		 echo '<input type="hidden" name="' . $name . '" id="' . $name . '" value="' . $value . '">';
	}

	function _submit_and_close($label, $confirm = null, $tab_index = 1) {
		_submit($label, $confirm, $tab_index);
		echo '</form>';
	}

	function _submit($label, $confirm,  $tab_index) {
		echo '<input type="submit" style="width: auto;" value="' . $label . '" tabindex="' . $tab_index .
			($confirm ? '" onclick="return confirm(\'' . $confirm . '\');' : '') . '">';
	}

	function _label($text, $for) {
		echo '<label for"' . $for . '">' . $text . '</label>';
	}

	function _text_field($title, $value, $tab_index = 1) {
		echo '<input type="text" name="' . $title . '" id="' . $title 
		. '" tabindex="' . $tab_index . '" value="' . $value . '">';
	}

	function _link($label, $type, $action = null, $params = null, $class = null, $confirm = null) 
	{
		\View\general::output_internal_link($label, $type, $action, $params, $class, $confirm);
	}

	function _info($label, $data) {
		_strong(_t($label) . ": ");
		echo $data;
		_br();		
	}

	function _space($count) 
	{
		for ($i = 0; $i < $count; $i++)
			echo '&nbsp;';
	}

	function __($text, $hints = null) 
	{
		echo _t($text, $hints);
	}

	function _h1($text) 
	{
		echo '<h1>' . $text . '</h1>';
	}

	function _h2($text) 
	{
		echo '<h2>' . $text . '</h2>';
	}

	function _t($text, $hints = null) 
	{
		return \i18n\engine::translate($text, $hints);
	}
?>
