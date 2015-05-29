<?php 

	if(isset($_POST['new_prop_title']) && isset($_POST['new_prop_description']) && isset($_POST['constituency_id']) && ($_POST['type_of_vote'] == "yes-no" || $_POST['type_of_vote'] == "prio-vote" || $_POST['type_of_vote'] == "candidate-election" || $_POST['type_of_vote'] == "median" || $_POST['type_of_vote'] == "budget")){

		$title = htmlspecialchars($_POST['new_prop_title']);
		$description = forum_helpers::process_text($_POST['new_prop_description']);

		$constituency_check = db_constituency::check_user_constituency_access($_SESSION['id'], $_POST['constituency_id']);
		if($constituency_check){
			$insert_id = db_prop::add_prop($_POST['type_of_vote'], $_SESSION['id'], null, $_POST['constituency_id'], $title, $description);
			if($insert_id){
				$_SESSION['report_message'] = "Propositionen är skapad.";
				$redirect = "index.php?type=vote&action=view_prop&id=" . $insert_id;
			}
		}
		else{
			$_SESSION['report_message'] = "Du har inte behörighet till den valkretsen.";
			$_SESSION['red_report_message'] = 1;
		}

	}

	else{
		$_SESSION['report_message'] = "Något fält var inte korrekt ifyllt.";
		$_SESSION['red_report_message'] = 1;
	}

?>