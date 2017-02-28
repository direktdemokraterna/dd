<?php
namespace View;

class calendar 
{
	public static function output_time_fields($calendar_info = null) {
		__textfield("year", "Datum", 1, $calendar_info);
		$month_options = self::generate_month_options();
		\View\controls::output_selector("month", $month_options, $calendar_info);
		$day_options = array();
		for($i=1; $i<32; $i++)
			$day_options[$i] = $i;
		\View\controls::output_selector("day", $day_options, $calendar_info);
		__textfield("time", "Tid", 4, $calendar_info,
			array("style"=>"width: 200px;"));
	}

	public static function generate_month_options() {
		$month_options = array();
		foreach (\Logic\calendar::$months as $index => $month)
			if ($index) $month_options[$index] = $month;
		return $month_options;
	}

	public static function output_location_field($calendar_info = null) {
		$counties = \db_constituency::get_counties();
		$location_options = array("internet" => "Internet");
		foreach($counties as $row)
			$location_options[$row['title']] = $row['title'];
		\View\controls::output_labeled_selector("location", "Plats", $location_options, $calendar_info);
	}

	public static function output_description_fields($calendar_info = null) {
		__textfield("title", "Titel", 6, $calendar_info
			, array("style"=>"width: 200px;"));
		__textarea("content", "Beskrivning", 7, $calendar_info
			, array("cols"=>"60", "rows"=>"5"));
	}

	public static function output_calendar_header_months($year, $month, $timestamp) {
		$previous_month = 1+($month + 10)%12;
		$next_month = 1+$month%12;
		$previous_year = $year;
		$next_year = $year;
		$show_previous_year = "";
		$show_next_year = "";
		if($month == 1){
			$previous_year--;
			$show_previous_year = " " . $previous_year;
		}
		elseif($month == 12){
			$next_year++;
			$show_next_year = " " . $next_year;
		}

		echo '<caption class="month_table_caption">';
		echo '<div class="previous_month">';
		__link(\general_helpers::get_month(null, $previous_month) . $show_previous_year
			, 'member', 'calendar', "year=$previous_year&month=$previous_month");
		echo '</div>';
		echo '<div class="next_month">';
		__link(\general_helpers::get_month(null, $next_month) . $show_next_year
			, 'member', 'calendar', "year=$next_year&month=$next_month");
		echo '</div>';
		echo '<div class="this_month">';
		echo strtolower(\general_helpers::get_month($timestamp)) . ' ' . $year;
		echo '</div>';		
		echo '</caption>';		
	}

	public static function output_calendar_header_days($day) {
		echo '<tr class="calendar_row">';
		foreach (\Logic\calendar::$days_short as $day)
			echo '<td class="calendar_weekday_cell">' . $day. '</td>';
		echo '</tr>';
	}

	public static function output_calendar_cell($year, $month, $day, $events_for_this_day, $day_counter) {
		$cell_class = $events_for_this_day ? "event_day" : "no_event_day";
		$events_presentation = self::get_events_presentation($events_for_this_day);
		echo '<td class="' . $cell_class . '"';
		if ($day_counter == $day && $month == date("n") && $year = date("Y"))
			echo ' id="this_day"';
		echo '>';
		$query_params = "year=$year&month=$month&day=$day_counter";
		__link($day_counter . $events_presentation, 'member', 'calendar', $query_params);
		echo '</td>';
	}

	private static function get_events_presentation($events_for_this_day) {
		if($events_for_this_day) {
			$events_presentation = "<span>";
			foreach ($events_for_this_day as $row) {
				$events_presentation .= "<strong>" . $row['title'] . '</strong><br>Tid: ' . $row['time'] . "<br>Plats: " . $row['location'] . "<br><br>";
			}
			$events_presentation .= "</span>";
			return $events_presentation;
		}
		return '';
	}
}
?>
