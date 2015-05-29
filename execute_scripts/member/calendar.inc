<?php

	if(!empty($_POST['type']) && !empty($_POST['id'])){
		$check_event = db_calendar::get_event($_POST['id']);

		if(!empty($check_event['timestamp']) && $check_event['timestamp'] > time()){

			if($_POST['type'] == "participate"){
				$ok = db_calendar::participate($_POST['id'], $_SESSION['id']);
				if($ok){
					$_SESSION['report_message'] = "Du är anmäld till denna aktivitet.";
					$redirect = $_SERVER['REQUEST_URI'];;
				}
			}
			elseif($_POST['type'] == "cancel_participate"){
				$ok = db_calendar::cancel_participate($_POST['id'], $_SESSION['id']);
				if($ok){
					$_SESSION['report_message'] = "Du är inte längre anmäld till denna aktivitet.";
					$redirect = $_SERVER['REQUEST_URI'];;
				}
			}
		}
		else{
			$_SESSION['report_message'] = "Anmälan är stängd för den här aktiviteten.";
			$_SESSION['red_report_message'] = 1;
			$redirect = $_SERVER['REQUEST_URI'];;
		}
	}

?>	