<?php

namespace Logic;

define("DAY_IN_SECONDS", 24*60*60);

class calendar 
{
	public static $months = array("INGEN_MÅNAD", "Januari", "Februari", "Mars", "April"
		, "Maj", "Juni", "Juli", "Augusti"
		, "September", "Oktober", "November", "December");	
	public static $week_day_names = array("Söndag", "Måndag", "Tisdag", "Onsdag", "Torsdag", "Fredag", "Lördag");
	public static $days_short = array("Mån", "Tis", "Ons", "Tor", "Fre", "Lör", "Sön");	

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
