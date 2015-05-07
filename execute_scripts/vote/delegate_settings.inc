<?php
	
	if(isset($_POST['register_delegate'])){

		$ok = db_delegate::create_delegate($_SESSION['id']);

		if($ok){
			$message = "Din användare är nu delegat.";
			db_helpers::insert_error_message($_SESSION['id'], $message);
		}
		else{
			$message = "Något gick fel.";
			db_helpers::insert_error_message($_SESSION['id'], $message, "red");
		}
		$redirect = $_SERVER['REQUEST_URI'];

	}

	elseif(isset($_POST['set_acting_as_delegate'])){

		if($_SESSION['acting_as_delegate']){
			if(db_delegate::stop_acting_as_delegate($_SESSION['id'])){
				$_SESSION['acting_as_delegate'] = 0;
				$message = "Nu röstar du som enskild användare.";
				db_helpers::insert_error_message($_SESSION['id'], $message);
			}
		}
		else{
			if(db_delegate::start_acting_as_delegate($_SESSION['id'])){
				$_SESSION['acting_as_delegate'] = 1;
				$message = "Nu röstar du som delegat.";
				db_helpers::insert_error_message($_SESSION['id'], $message);
			}
		}
		$redirect = $_SERVER['REQUEST_URI'];

	}

	elseif(isset($_POST['set_constituencies'])){

		if(!empty($_POST['constituencies'])) {
			$ok = db_delegate::update_delegate_constituencies($_POST['constituencies'], $_SESSION['id']);
		}
		else{
			$ok = db_delegate::remove_all_delegate_constituencies($_SESSION['id']);
		}

		if($ok>0){
			$message = "Valkretsaktivitet uppdaterad.";
			db_helpers::insert_error_message($_SESSION['id'], $message);
			$redirect = $_SERVER['REQUEST_URI'];
		}

	}

