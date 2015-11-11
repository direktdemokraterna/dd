<?php
namespace Logic;

class util 
{	
	public static function is_all_set($properties, $array) 
	{
		foreach($properties as $prop)
			if (!isset($array[$prop])) return false;
		return true;
	}

	public static function has_error() 
	{
		return $_SESSION['red_report_message'];
	}

	public static function report_error($message) 
	{
		$_SESSION['report_message'] = $message;
		$_SESSION['red_report_message'] = 1;
	}

	public static function starts_With($haystack, $needle) {
		return strpos($haystack, $needle) === 0;
	}
}