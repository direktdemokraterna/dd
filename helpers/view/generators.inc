<?php
	function __li($content) 
	{
		echo '<li>' . $content . '</li>';
	}

	function __p($text) 
	{
		echo '<p>' . $text . '</p>';
	}

	function __strong($text) 
	{
		echo '<strong>' . $text . '</strong>';
	}

	function __br($n = 1) 
	{
		for ($i = 0; $i < $n; $i++)
			echo '<br>';
	}

	function __open_form($class = "standard-form") {
		echo '<form method="post" action="" class="' . $class . '">';
	}

	function __hidden($name, $value = "") 
	{
		 echo '<input type="hidden" name="' . $name . '" id="' . $name . '" value="' . $value . '">';
	}

	function __submit_and_close($label, $name = null, $confirm = null, $tab_index = 1) {
		__submit($label, $name, $confirm, $tab_index);
		echo '</form>';
	}

	function __submit($label, $name, $confirm, $tab_index) {
		echo "<input type=\"submit\"" . ($name ? " name=\"$name\"" : "") 
			. " style=\"width: auto;\" value=\"$label\" tabindex=\"$tab_index\""
			. ($confirm ? " onclick=\"return confirm('$confirm');\">" : ">");
	}

	function __label($text, $for) {
		echo "<label for=\"$for\">$text</label>";
	}

	function __link($label, $type, $action = null, $params = null, $class = null, $confirm = null) 
	{
		\View\controls::output_internal_link($label, $type, $action, $params, $class, $confirm);
	}

	function __info($label, $data) {
		__strong($label . ": ");
		echo $data;
		__br();		
	}

	function __space($count = 1) 
	{
		for ($i = 0; $i < $count; $i++)
			echo '&nbsp;';
	}

	function _span($html, $class = null) 
	{
		return "<span" . ($class ? " class=\"$class\"" : "") . ">$html</span>";
	}

	function __t($text, $hints = null) 
	{
		echo _t($text, $hints);
	}

	function __h1($text) 
	{
		echo '<h1>' . $text . '</h1>';
	}

	function __h2($text) 
	{
		echo '<h2>' . $text . '</h2>';
	}

	function _t($text, $hints = null) 
	{
		return \i18n\engine::translate($text, $hints);
	}

	function _limit_with_ellipsis($text, $limit) 
	{
		return $text && strlen($text) > $limit
			? substr($text, 0, $limit - 3) . '...'
			: $text;
	}

	function __action($label, $action, $params, $confirm = null) 
	{
		__open_form();
		foreach ($params as $key => $value)
			__hidden($key, $value);
		__submit_and_close($label, $action, $confirm);
	}
?>
