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
		$time = isset($_POST['time'])
			? general_helpers::clean($_POST['time'])
			: "";
		$location = general_helpers::clean($_POST['location']);		
		if(db_calendar::add_event($timestamp, $year, $month, $day, $time, $_SESSION['id'], $location, $title, $content)){
			$insert_counter = 1;
		}
		if(isset($_POST['repeat_type']) && $_POST['repeat_number'] > 1 && $_POST['repeat_number'] < 53){
			$plus_time = \Logic\calendar::get_repeat_time($_POST['repeat_type']);
			if(isset($plus_time)){
				$new_timestamp = $timestamp;
				for($i=1; $i<$_POST['repeat_number']; $i++){
					$new_timestamp = strtotime ($plus_time, $new_timestamp);
					$new_year = date("Y", $new_timestamp);
					$new_month = date("n", $new_timestamp);
					$new_day = date("j", $new_timestamp);
					if(db_calendar::add_event($new_timestamp, $new_year, $new_month, $new_day, $time, $_SESSION['id'], $location, $title, $content))
						$insert_counter++;
				}
			}
		}
		if(isset($insert_counter)){
			$message = $insert_counter . " aktiviteter lagda till kalendern.";
			$redirect = "index.php?type=member&action=calendar";
		}
		else {
			$_SESSION['report_message'] = "Något gick fel. Ingen aktivitet lagd i kalendern";
			$_SESSION['red_report_message'] = 1;
		}	
	}
	else{
		$_SESSION['report_message'] = "Ett eller flera obligatoriska fält är inte ifyllda"; 
		$_SESSION['red_report_message'] = 1;
	}
?>