<?php
	if(!isset($_GET['day']) && isset($_GET['month'])){
		$show_this_date = false;
	}
	else{
		$show_this_date = true;
	}
	
	if(isset($_GET['day'])){
		$day = $_GET['day'];
	}
	else{
		$day = date("j");
	}

	if(isset($_GET['month'])){
		$month = $_GET['month'];
	}
	else{
		$month = date("n");
	}

	if(isset($_GET['year'])){
		$year = $_GET['year'];
	}
	else{
		$year = date("Y");
	}

	$timestamp = strtotime($year . "-" . $month . "-" . $day);
?>


<?php if($show_this_date) : ?>

	<?php if($year == date("Y")) : ?>

		<h1><?php echo general_helpers::veckodag($timestamp); ?> <?php echo $day; ?> <?php echo strtolower(general_helpers::manad($timestamp)); ?></h1>

	<?php else : ?>

		<h1><?php echo general_helpers::veckodag($timestamp); ?> <?php echo $day; ?> <?php echo strtolower(general_helpers::manad($timestamp)); ?> <?php echo $year; ?></h1>

	<?php endif; ?>	

	<?php
		$events = db_calendar::get_events($year, $month, $day);
	?>

	<?php foreach($events as $row) : ?>
		<div class="event">
			<h2 style="margin-top: 10px;"><?php echo $row['title']; ?></h2>

			<strong>Tidpunkt: </strong><?php echo $row['time']; ?><br>
			<strong>Plats: </strong><?php echo $row['location']; ?><br>
			<strong>Upplagd av: </strong><a href="index.php?type=member&action=view&id=<?php echo $row['user_id']; ?>"><?php echo $row['full_name']; ?></a><br>
			<strong>Beskrivning: </strong><?php echo \View\general::make_html_from_wiki_text($row['content']); ?><br>
			<br>
			<strong>Anmälda deltagare:</strong><br>

			<?php
				$participants = db_calendar::get_participants($row['event_id']);
				$is_participant = db_calendar::is_participant($row['event_id'], $_SESSION['id']);
			?>

			<?php if(empty($participants)) : ?>
				Inga anmälda deltagare.<br>
			<?php else : ?>
				<?php foreach($participants as $p_row) : ?>
					<a href="index.php?type=member&action=view&id=<?php echo $p_row['user_id']; ?>"><?php echo $p_row['full_name']; ?></a><br>
				<?php endforeach; ?>
			<?php endif; ?>

			<?php if(($timestamp + 24*3600) > time()) : ?>
				<br>
				<?php if($is_participant) : ?>
					<form method="post" action="" class="single_submit_button"><input type="hidden" name="type" value="cancel_participate"><input type="hidden" name="id" value="<?php echo $row['event_id']; ?>"><input type="submit" value="Avanmäl dig till denna händelse"></form>
				<?php else : ?>
					<form method="post" action="" class="single_submit_button"><input type="hidden" name="type" value="participate"><input type="hidden" name="id" value="<?php echo $row['event_id']; ?>"><input type="submit" value="Anmäl dig till denna händelse"></form>
				<?php endif; ?>
			<?php endif; ?>
			
			<?php if($row['user_id'] == $_SESSION['id'] && $row['timestamp'] > time()) : ?>
				<a href="index.php?type=member&action=calendar_edit&id=<?php echo $row['event_id']; ?>">Redigera denna händelse</a>
			<?php endif; ?>

		</div>
	<?php endforeach; ?>



<?php else : ?>

	<h1><?php echo strtolower(general_helpers::manad($timestamp)); ?> <?php echo $year; ?></h1>

<?php endif; ?>


<?php
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