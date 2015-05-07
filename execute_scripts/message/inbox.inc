<?php
	if(isset($_POST['delete'])){
		$deleted = db_message::delete_inbox($_POST['check_list'], $_SESSION['id']);
		if($deleted>0){
			if($deleted>1){
				$message = $deleted . " meddelanden raderade.";
			}
			else{
				$message = "1 meddelande raderat.";
			}
			db_helpers::insert_error_message($_SESSION['id'], $message);
			$redirect = $_SERVER['REQUEST_URI'];
		}
	}

	if(isset($_GET['recipient_delete'])){
		$message_array = Array($_GET['recipient_delete']);
		$deleted = db_message::delete_inbox($message_array, $_SESSION['id']);
		if($deleted>0){
			if($deleted>1){
				$message = $deleted . " meddelanden raderade.";
			}
			else{
				$message = "1 meddelande raderat.";
			}
			db_helpers::insert_error_message($_SESSION['id'], $message);
			$redirect = $_SERVER['REQUEST_URI'];
		}
	}

	if(isset($_GET['sender_delete'])){
		$message_array = Array($_GET['sender_delete']);
		$deleted = db_message::delete_outbox($message_array, $_SESSION['id']);
		if($deleted>0){
			if($deleted>1){
				$message = $deleted . " meddelanden raderade.";
			}
			else{
				$message = "1 meddelande raderat.";
			}
			db_helpers::insert_error_message($_SESSION['id'], $message);
			$redirect = $_SERVER['REQUEST_URI'];
		}
	}

	if(isset($_GET['cancel'])){
		$cancelled = db_message::cancel($_GET['cancel'], $_SESSION['id']);
		if($cancelled>0){
			$message = "Meddelandet har ångrats och mottagaren hann aldrig läsa det.";
			db_helpers::insert_error_message($_SESSION['id'], $message);
			$redirect = $_SERVER['REQUEST_URI'];
		}
	}
?>