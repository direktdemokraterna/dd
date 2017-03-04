<?php
	$show_this_date = (isset($_GET['day']) || !isset($_GET['month']));
	$day = isset($_GET['day']) ? $_GET['day'] : date("j");
	$month = isset($_GET['month']) ? $_GET['month'] : date("n");
	$year = isset($_GET['year']) ? $_GET['year'] : date("Y");
	$timestamp = strtotime($year . "-" . $month . "-" . $day);
	if($show_this_date) {
		__h1(general_helpers::get_weekday($timestamp) . ' ' . $day . ' ' . strtolower(general_helpers::get_month($timestamp)) . ($year == date("Y") ? '' : ' ' . $year));
		$events = db_calendar::get_events($year, $month, $day);
		foreach($events as $row) {
			echo '<div class="event">';
			__h2($row['title']);
			__info("Tid", $row['time']);
			__info("Plast", $row['location']);
			__info("Tillagd av", \View\member::link($row, 'user_id'));
			__info("Beskrivning", \Logic\text::make_html_from_wiki_text($row['content']));
			__br();
			__strong("Anmälda deltagare:");
			__br();
			$participants = db_calendar::get_participants($row['event_id']);
			$is_participant = db_calendar::is_participant($row['event_id'], $_SESSION['id']);
			if(empty($participants)) {
				echo "Inga anmälda deltagare";
				__br();
			}
			else 
				foreach($participants as $p_row) {
					echo \View\member::link($p_row, 'user_id');
					__br();
				}
			if(($timestamp + DAY_IN_SECONDS) > time()) {
				__br();
				__open_form("single_submit_button");
				__hidden("id", $row['event_id']);
				if($is_participant) {
					__hidden("type", "cancel_participate");
					__submit_and_close("Avanmäl dig från denna aktivitet");
				}
				else {
					__hidden("type", "participate");
					__submit_and_close("Anmäl dig till denna aktivitet");
				}
			}
			if($row['user_id'] == $_SESSION['id'] && $row['timestamp'] > time()) 
				__link("Ändra aktivitet", 'member', 'calendar_edit', 'id=' . $row['event_id']);
			echo '</div>';
		}
	}
	else 
		__h1(strtolower(general_helpers::get_month($timestamp)) . ' ' . $year);
	
	$weekday_of_first_in_this_month = date("w", strtotime($year . "-" . $month . "-" . 1));
	if($weekday_of_first_in_this_month == 0) $weekday_of_first_in_this_month = 7; // Make Sunday day 7

	$days_in_this_month = date("t", $timestamp);
	$number_of_weeks_in_this_month = ceil(($days_in_this_month + $weekday_of_first_in_this_month - 1) / 7);
	
	echo '<table class="month_table">';
	\View\calendar::output_calendar_header_months($year, $month, $timestamp);
	\View\calendar::output_calendar_header_days($day);
	$day_counter = 0;
	$calendar_counter = 0;
	for($i=0; $i<$number_of_weeks_in_this_month; $i++) {
		echo '<tr class="calendar_row">';
		for($j=0; $j<7; $j++) {
			$calendar_counter++;
			if($calendar_counter < $weekday_of_first_in_this_month || $calendar_counter >= ($weekday_of_first_in_this_month + $days_in_this_month))
				echo '<td class="non_day"></td>';
			else {
				$day_counter++;
				$events_for_this_day = db_calendar::get_events($year, $month, $day_counter);
				\View\calendar::output_calendar_cell($year, $month, $day, $events_for_this_day, $day_counter);
			}
		}
		echo '</tr>';
	}
	echo '</table>';
	__br();
	__p(_link("Lägg till aktivitet till kalendern", 'member', 'calendar_add'));
?>
