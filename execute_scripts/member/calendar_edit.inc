<?php

	if(!empty($_POST['year']) && !empty($_POST['month']) && !empty($_POST['day']) && !empty($_POST['location']) && !empty($_POST['title']) && !empty($_POST['content'])){

		$year = (int)$_POST['year'];
		$month = (int)$_POST['month'];
		$day = (int)$_POST['day'];

		$event_date = $year . "-" . $month . "-" . $day;
		$event_time = strtotime($event_date);
			
		$timestamp = $event_time - ($event_time % 86400) + 86399;

		$content = \Logic\text::process_text($_POST['content']);
		$title = general_helpers::clean($_POST['title']);
		if(isset($_POST['time'])){
			$time = general_helpers::clean($_POST['time']);
		}
		else{
			$time = "";
		}
		$location = general_helpers::clean($_POST['location']);
		
		if(db_calendar::edit_event($timestamp, $year, $month, $day, $time, $location, $title, $content, $_GET['id'])){
			$_SESSION['report_message'] = "Aktiviteten har uppdaterats";
			$redirect = "index.php?type=member&action=calendar&year=" . $year . "&month=" . $month . "&day=" . $day;
		}
		else {
			$_SESSION['report_message'] = Något gick fel. Inga ändringar utförda.;
			$_SESSION['red_report_message'] = 1;
		}
		
	}

	else{
		$_SESSION['report_message'] = "Ett eller flera obligatoriska fält är inte ifyllda"; 
		$_SESSION['red_report_message'] = 1;
	}

?>