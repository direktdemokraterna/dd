<?php

	if(!empty($_POST['type']) && !empty($_POST['id'])){
		$check_event = db_calendar::get_event($_POST['id']);

		if(!empty($check_event['timestamp']) && $check_event['timestamp'] > time()){

			if($_POST['type'] == "participate"){
				$ok = db_calendar::participate($_POST['id'], $_SESSION['id']);
				if($ok){
					$message = "Du är anmäld till denna aktivitet.";
					db_helpers::insert_error_message($_SESSION['id'], $message);
					$redirect = $_SERVER['REQUEST_URI'];;
				}
			}
			elseif($_POST['type'] == "cancel_participate"){
				$ok = db_calendar::cancel_participate($_POST['id'], $_SESSION['id']);
				if($ok){
					$message = "Du är inte längre anmäld till denna aktivitet.";
					db_helpers::insert_error_message($_SESSION['id'], $message);
					$redirect = $_SERVER['REQUEST_URI'];;
				}
			}
		}
		else{
			$message = "Anmälan är stängd för den här aktiviteten.";
			db_helpers::insert_error_message($_SESSION['id'], $message, "red");
			$redirect = $_SERVER['REQUEST_URI'];;
		}
	}

?>	