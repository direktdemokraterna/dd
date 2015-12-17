<?php

namespace Logic;

define("ONE_DAY_IN_SECONDS", 24*3600);

class calendar 
{
	public static $months = array("January", "February", "March", "April"
		, "May", "June", "July", "August"
		, "September", "October", "November", "December");	

	public static $days_short = array("Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun");	

	public static function get_repeat_time($repeat_type) 
	{
		switch ($repeat_type) {
			case 'day': return "+1 day";
			case 'week': return "+1 week";
			case '2weeks': return "+2 weeks";
			case 'month': return "+1 month";
			default: return null;
		}
	}
}
