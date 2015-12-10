<?php
	$show_this_date = (isset($_GET['day']) || !isset($_GET['month']));
	$day = isset($_GET['day']) ? $_GET['day'] : date("j");
	$month = isset($_GET['month']) ? $_GET['month'] : date("n");
	$year = isset($_GET['year']) ? $_GET['year'] : date("Y");
	$timestamp = strtotime($year . "-" . $month . "-" . $day);
	if($show_this_date) {
		_h1(general_helpers::veckodag($timestamp) . ' ' . $day . ' ' . strtolower(general_helpers::manad($timestamp)) . ($year == date("Y") ? '' : ' ' . $year));
		$events = db_calendar::get_events($year, $month, $day);
		foreach($events as $row) {
			echo '<div class="event">';
			_h2($row['title']);
			_info(_t("Time"), $row['time']);
			_info(_t("Location"), $row['location']);
			_info(_t("Added by"), \View\member::generate_member_link($row['user_id'], $row['full_name']));
			_info(_t("Description"), \View\general::make_html_from_wiki_text($row['content']));
			_br();
			_strong(_t("Subscribed participants:", array('class' => 'adj')));
			_br();
			$participants = db_calendar::get_participants($row['event_id']);
			$is_participant = db_calendar::is_participant($row['event_id'], $_SESSION['id']);
			if(empty($participants)) {
				__("No subscribed participants");
				_br();
			}
			else 
				foreach($participants as $p_row) {
					echo \View\member::generate_member_link($p_row['user_id'], $p_row['full_name']);
					_br();
				}
			if(($timestamp + ONE_DAY_IN_SECONDS) > time()) {
				_br();
				_open_form("single_submit_button");
				_hidden("id", $row['event_id']);
				if($is_participant) {
					_hidden("type", "cancel_participate");
					_submit_and_close(_t("Unsubscribe for this activity"));
				}
				else {
					_hidden("type", "participate");
					_submit_and_close(_t("Subscribe for this activity"));
				}
			}
			if($row['user_id'] == $_SESSION['id'] && $row['timestamp'] > time()) 
				_link(_t("Edit activity"), 'member', 'calendar_edit', 'id=' . $row['event_id']);
			echo '</div>';
		}
	}
	else 
		_h1(strtolower(general_helpers::manad($timestamp)) . ' ' . $year);
	
	if($month == 1){
		$previous_month = 12;
		$previous_year = $year - 1;
		$next_month = $month + 1;
		$next_year = $year;
		$show_previous_year = " " . $previous_year;
		$show_next_year = "";
	}
	elseif($month == 12){
		$previous_month = $month -1;
		$previous_year = $year;
		$next_month = 1;
		$next_year = $year + 1;
		$show_previous_year = "";
		$show_next_year = " " . $next_year;
	}
	else{
		$previous_month = $month -1;
		$previous_year = $year;
		$next_month = $month + 1;
		$next_year = $year;
		$show_previous_year = "";
		$show_next_year = "";
	}

	$weekday_of_first_in_this_month = date("w", strtotime($year . "-" . $month . "-" . 1));
	if($weekday_of_first_in_this_month == 0) $weekday_of_first_in_this_month = 7; // Make Sunday day 7

	$days_in_this_month = date("t", $timestamp);
	$number_of_weeks_in_this_month = ceil(($days_in_this_month + $weekday_of_first_in_this_month - 1) / 7);

?>
	
<table class="month_table">
	<caption class="month_table_caption">
		
			<div class="previous_month"><a href="index.php?type=member&action=calendar&year=<?php echo $previous_year; ?>&month=<?php echo $previous_month; ?>"><?php echo general_helpers::manad(null, $previous_month) . $show_previous_year; ?></a></div>
			<div class="next_month"><a href="index.php?type=member&action=calendar&year=<?php echo $next_year; ?>&month=<?php echo $next_month; ?>"><?php echo general_helpers::manad(null, $next_month) . $show_next_year; ?></a></div>
			<div class="this_month"><?php echo strtolower(general_helpers::manad($timestamp)); ?> <?php echo $year; ?></div>
		
	</caption>
	<tr class="calendar_row">
		<td class="calendar_weekday_cell">Mån</td>
		<td class="calendar_weekday_cell">Tis</td>
		<td class="calendar_weekday_cell">Ons</td>
		<td class="calendar_weekday_cell">Tor</td>
		<td class="calendar_weekday_cell">Fre</td>
		<td class="calendar_weekday_cell">Lör</td>
		<td class="calendar_weekday_cell">Sön</td>
	</tr>

	<?php
		$day_counter = 0;
		$calendar_counter = 0;
	?>

	<?php for($i=0; $i<$number_of_weeks_in_this_month; $i++) : ?>
		
		<tr class="calendar_row">

			<?php for($j=0; $j<7; $j++) : ?>

				<?php
					$calendar_counter++;
				?>

				<?php if($calendar_counter < $weekday_of_first_in_this_month || $calendar_counter >= ($weekday_of_first_in_this_month + $days_in_this_month)) : ?>
					<td class="non_day"></td>
				<?php else : ?>
					<?php
						$day_counter++;
						$events_for_this_day = db_calendar::get_events($year, $month, $day_counter);
					?>
					<?php if(!empty($events_for_this_day)) : ?>
						<?php
							$events_presentation = "<span>";
							foreach ($events_for_this_day as $row) {
								$events_presentation .= "<strong>" . $row['title'] . "</strong><br>Tid: " . $row['time'] . "<br>Plats: " . $row['location'] . "<br><br>";
							}
							$events_presentation .= "</span>";
						?>

						<td class="event_day"<?php if($day_counter == $day && $month == date("n") && $year = date("Y")) echo " id=\"this_day\""; ?>><a href="index.php?type=member&action=calendar&year=<?php echo $year; ?>&month=<?php echo $month; ?>&day=<?php echo $day_counter; ?>"><?php echo $day_counter; ?><?php echo $events_presentation; ?></a></td>
					<?php else : ?>
						<td class="no_event_day"<?php if($day_counter == $day && $month == date("n") && $year = date("Y")) echo " id=\"this_day\""; ?>><a href="index.php?type=member&action=calendar&year=<?php echo $year; ?>&month=<?php echo $month; ?>&day=<?php echo $day_counter; ?>"><?php echo $day_counter; ?></a></td>
					<?php endif; ?>
				<?php endif; ?>

			<?php endfor; ?>

		</tr>

	<?php endfor; ?>

</table>

<br>
<p><a href="index.php?type=member&action=calendar_add">Lägg till aktivitet till kalendern</a></p>