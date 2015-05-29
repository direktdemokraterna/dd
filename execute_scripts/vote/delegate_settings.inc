<?php
	
	if(isset($_POST['register_delegate'])){

		$ok = db_delegate::create_delegate($_SESSION['id']);

		if($ok){
			$_SESSION['report_message'] = "Din användare är nu delegat.";
			}
		else{
			$_SESSION['report_message'] = "Något gick fel.";
			$_SESSION['red_report_message'] = 1;
		}
		$redirect = $_SERVER['REQUEST_URI'];

	}

	elseif(isset($_POST['set_acting_as_delegate'])){

		if($_SESSION['acting_as_delegate']){
			if(db_delegate::stop_acting_as_delegate($_SESSION['id'])){
				$_SESSION['acting_as_delegate'] = 0;
				$_SESSION['report_message'] = "Nu röstar du som enskild användare.";
				}
		}
		else{
			if(db_delegate::start_acting_as_delegate($_SESSION['id'])){
				$_SESSION['acting_as_delegate'] = 1;
				$_SESSION['report_message'] = "Nu röstar du som delegat.";
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
			$_SESSION['report_message'] = "Valkretsaktivitet uppdaterad.";
			$redirect = $_SERVER['REQUEST_URI'];
		}

	}

