<?php

namespace Logic;

class util 
{
	public static function starts_with($str, $suffix)
	{
	     return (substr($str, 0, strlen($suffix)) === $suffix);
	}

	public static function is_all_set($properties, $array) 
	{
		foreach($properties as $prop)
			if (!isset($array[$prop]) || (!$array[$prop] && $array[$prop] !== 0)) 
				return false;
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

	public static function update_search_query($type, $action = "search") {
		$search_input_name = self::get_search_input_name($type, $action);
		$search_query = isset($_POST[$search_input_name]) 
			? $_POST[$search_input_name]
			: (isset($_SESSION[$search_input_name]) ? $_SESSION[$search_input_name] : '');
		$_SESSION[$search_input_name] = $search_query;
		return $search_query;
	}

	public static function get_search_input_name($type, $action = "search") {
		return $type . "_" . $action . "_input";
	}
}