<?php
namespace View;

class calendar 
{
	public static function output_time_fields($calendar_info = null) {
		\View\general::make_textfield("year", _t("Date"), 1, $calendar_info);
		$month_options = array();
		foreach (\Logic\calendar::$months as $index => $month)
			$month_options[$index + 1] = _t($month);
		\View\general::make_selector("month", $month_options, $calendar_info);
		$day_options = array();
		for($i=1; $i<32; $i++)
			$day_options[$i] = $i;
		\View\general::make_selector("day", $day_options, $calendar_info);
		\View\general::make_textfield("time", _t("Time"), 4, $calendar_info,
			array("style"=>"width: 200px;"));
	}

	public static function output_location_field($calendar_info = null) {
		$counties = \db_constituency::get_counties();
		$location_options = array("Internet" => "Internet");
		foreach($counties as $row)
			$location_options[$row['title']] = $row['title'];
		\View\general::make_labeled_selector("location", _("Location"), $location_options, $calendar_info);
	}

	public static function output_description_fields($calendar_info = null) {
		\View\general::make_textfield("title", _t("Caption"), 6, $calendar_info
			, array("style"=>"width: 200px;"));
		\View\general::make_textarea("content", _t("Description"), 7, $calendar_info
			, array("cols"=>"60", "rows"=>"5"));
	}
}
?>
