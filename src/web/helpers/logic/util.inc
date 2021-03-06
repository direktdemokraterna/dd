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

	public static function page_has_error() 
	{
		return isset($_SESSION['red_report_message']) && $_SESSION['red_report_message'];
	}

	public static function report_error($message, $has_session = true) 
	{
		if ($has_session) {
			$_SESSION['report_message'] = $message;
			$_SESSION['red_report_message'] = 1;
		}
		else setcookie('error', $message, strtotime('+30 seconds'));
	}

	public static function update_search_query($type, $action = "search") {
		$search_input_name = self::get_search_input_name($type, $action);
		$search_query = isset($_GET[$search_input_name])
			? $_GET[$search_input_name]
			: (isset($_SESSION[$search_input_name]) ? $_SESSION[$search_input_name] : '');
		$_SESSION[$search_input_name] = $search_query;
		return $search_query;
	}

	public static function get_search_input_name($type, $action = "search") {
		return $type . "_" . $action . "_input";
	}

	public static function get_request_params(){
		$query_params = array();
		parse_str($_SERVER['QUERY_STRING'], $query_params);
		return $query_params;
	}

	public static function make_param_string($query_params) {
		unset($query_params['type']);
		unset($query_params['action']);
		return implode('&', array_map(function ($key, $value) {return "$key=$value";}
			, array_keys($query_params), $query_params));
	}
}