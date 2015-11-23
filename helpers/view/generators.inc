<?php
	function _li($content) 
	{
		echo '<li>' . $content . '</li>';
	}

	function _p($text) 
	{
		echo '<p>' . $text . '</p>';
	}

	function _strong($text) 
	{
		echo '<strong>' . $text . '</strong>';
	}

	function _br() 
	{
		echo '<br>';
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
		echo '<h1>' . _t($text) . '</h1>';
	}

	function _h2($text) 
	{
		echo '<h2>' . _t($text) . '</h2>';
	}

	function _t($text) 
	{
		return \i18n\engine::translate($text);
	}
?>
