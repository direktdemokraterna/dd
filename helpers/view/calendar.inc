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
		_link(\general_helpers::manad(null, $previous_month) . $show_previous_year
			, 'member', 'calendar', "year=$previous_year&month=$previous_month");
		echo '</div>';
		echo '<div class="next_month">';
		_link(\general_helpers::manad(null, $next_month) . $show_next_year
			, 'member', 'calendar', "year=$next_year&month=$next_month");
		echo '</div>';
		echo '<div class="this_month">';
		echo strtolower(\general_helpers::manad($timestamp)) . ' ' . $year;
		echo '</div>';		
		echo '</caption>';		
	}

	public static function output_calendar_header_days($day) {
		echo '<tr class="calendar_row">';
		foreach (\Logic\calendar::$days_short as $day)
			echo '<td class="calendar_weekday_cell">' . _t($day). '</td>';
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
		_link($day_counter . $events_presentation, 'member', 'calendar', $query_params);
		echo '</td>';
	}

	private static function get_events_presentation($events_for_this_day) {
		if($events_for_this_day) {
			$events_presentation = "<span>";
			foreach ($events_for_this_day as $row) {
				$events_presentation .= "<strong>" . $row['title'] . "</strong><br>Tid: " . $row['time'] . "<br>" . _t("Location: ") . $row['location'] . "<br><br>";
			}
			$events_presentation .= "</span>";
			return $events_presentation;
		}
		return '';
	}
}
?>
