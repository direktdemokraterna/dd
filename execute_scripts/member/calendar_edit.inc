<?php

	if(!empty($_POST['year']) && !empty($_POST['month']) && !empty($_POST['day']) && !empty($_POST['location']) && !empty($_POST['title']) && !empty($_POST['content'])){

		$year = (int)$_POST['year'];
		$month = (int)$_POST['month'];
		$day = (int)$_POST['day'];

		$event_date = $year . "-" . $month . "-" . $day;
		$event_time = strtotime($event_date);
			
		$timestamp = $event_time - ($event_time % 86400) + 86399;

		$content = forum_helpers::process_text($_POST['content']);
		$title = htmlspecialchars($_POST['title']);
		if(isset($_POST['time'])){
			$time = htmlspecialchars($_POST['time']);
		}
		else{
			$time = "";
		}
		$location = htmlspecialchars($_POST['location']);
		
		if(db_calendar::edit_event($timestamp, $year, $month, $day, $time, $location, $title, $content, $_GET['id'])){
			$_SESSION['report_message'] = "Aktiviteten har ändrats.";
			$redirect = "index.php?type=member&action=calendar&year=" . $year . "&month=" . $month . "&day=" . $day;
		}
		else {
			$_SESSION['report_message'] = "Något gick fel. Ingen ändring gjord.";
			$_SESSION['red_report_message'] = 1;
		}
		
	}

	else{
		$_SESSION['report_message'] = "Något fält som måste vara ifyllt var inte ifyllt."; 
		$_SESSION['red_report_message'] = 1;
	}

?>