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
}