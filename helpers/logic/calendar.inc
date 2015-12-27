<?php

namespace Logic;

define("DAY_IN_SECONDS", 24*60*60);

class calendar 
{
	public static $months = array("NO_MONTH", "January", "February", "March", "April"
		, "May", "June", "July", "August"
		, "September", "October", "November", "December");	
	public static $week_day_names = array("Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday");
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
