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

	function _open_form() {
		echo '<form method="post" action="" class="standard-form">';
	}

	function _hidden($name, $value) 
	{
		 echo '<input type="hidden" name=" ' . $name . '" value="' . $value . '">';
	}

	function _submit_and_close($label, $confirm = null) {
		_submit($label, $confirm);
		echo '</form>';
	}

	function _submit($label, $confirm) {
		echo '<input type="submit" style="width: auto;" value="' . $label . 
			($confirm ? '" onclick="return confirm(\'' . $confirm . '\');' : '') . '">';
	}

	function _link($label, $type, $action = null, $params = null, $class = null, $confirm = null) 
	{
		\View\general::output_internal_link($label, $type, $action, $params, $class, $confirm);
	}

	function _space($count) 
	{
		for ($i = 0; $i < $count; $i++)
			echo '&nbsp;';
	}

	function __($text) 
	{
		echo _t($text);
	}

	function _h1($text) 
	{
		echo '<h1>' . $text . '</h1>';
	}

	function _h2($text) 
	{
		echo '<h2>' . $text . '</h2>';
	}

	function _t($text) 
	{
		return \i18n\engine::translate($text);
	}
?>
