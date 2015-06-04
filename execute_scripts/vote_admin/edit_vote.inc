<?php 

if(isset($_POST['update'])){

	if(isset($_POST['vote_id']) && isset($_POST['type_of_vote']) && isset($_POST['constituency_id']) && isset($_POST['forum_topic_id']) && isset($_POST['title'])){

		if($_POST['vote_id'] == $_GET['id']){

			if(db_constituency::check_that_constituency_exists($_POST['constituency_id'])){ 

				if($_POST['type_of_vote'] == "yes-no" || $_POST['type_of_vote'] == "prio-vote" || $_POST['type_of_vote'] == "candidate-election" || $_POST['type_of_vote'] == "median" || $_POST['type_of_vote'] == "budget"){

					$ok1 = db_vote_admin::update_vote($_POST['type_of_vote'], $_POST['constituency_id'], $_POST['title'], $_POST['description'], $_POST['forum_topic_id'], $_POST['vote_id']);

					if(isset($_POST['year']) && isset($_POST['month']) && isset($_POST['day']) && isset($_POST['hour']) && isset($_POST['minute']) && isset($_POST['delegate_year']) && isset($_POST['delegate_month']) && isset($_POST['delegate_day']) && isset($_POST['delegate_hour']) && isset($_POST['delegate_minute'])){

						$time_string = (int)$_POST['year'] . "-" . (int)$_POST['month'] . "-" . (int)$_POST['day'] . " " . (int)$_POST['hour'] . ":" . (int)$_POST['minute'] . ":00";
						$delegate_time_string = (int)$_POST['delegate_year'] . "-" . (int)$_POST['delegate_month'] . "-" . (int)$_POST['delegate_day'] . " " . (int)$_POST['delegate_hour'] . ":" . (int)$_POST['delegate_minute'] . ":00";

						$timestamp_ended = strtotime($time_string);
						$timestamp_delegate_ended = strtotime($delegate_time_string);

						$ok2 = db_vote_admin::update_time_ended($timestamp_ended, $timestamp_delegate_ended, $_POST['vote_id']);

					}

					if($ok1 || $ok2){
						$_SESSION['report_message'] = "Omröstningen är uppdaterad.";
						$redirect = $_SERVER['REQUEST_URI'];
					}
					else{
						$_SESSION['report_message'] = "Databasfel. Ingen uppdatering gjord.";
						$_SESSION['red_report_message'] = 1;
					}

				}
				else{
					$_SESSION['report_message'] = "Fel omröstningstyp. Ingen ändring gjord.";
					$_SESSION['red_report_message'] = 1;
				}

			}
			else{
				$_SESSION['report_message'] = "Valkretsfel. Ingen ändring gjord.";
				$_SESSION['red_report_message'] = 1;
			}

		}

	}

}

elseif(isset($_POST['end_vote'])){
	$voteinfo = db_vote::get_vote_info($_GET['id']);

	if($voteinfo['status'] == "active" || $voteinfo['status'] == "del_ended"){
		$ok = db_vote_admin::end_vote($_GET['id']);
		vote_helpers::substitute_active_for_passive_user_codes($_GET['id']);
	}
}

elseif(isset($_POST['end_delegate_vote'])){
	$voteinfo = db_vote::get_vote_info($_GET['id']);

	if($voteinfo['status'] == "active"){
		$ok = db_vote_admin::end_delegate_vote($_GET['id']);
	}
}

elseif(isset($_POST['restore_delegate_vote'])){
	$voteinfo = db_vote::get_vote_info($_GET['id']);

	if($voteinfo['status'] == "del_ended"){
		$ok = db_vote_admin::restore_delegate_vote($_GET['id']);
	}

}

elseif(isset($_POST['restore_vote'])){
	$voteinfo = db_vote::get_vote_info($_GET['id']);

	if($voteinfo['status'] == "ended"){
		$ok = db_vote_admin::restore_vote($_GET['id']);
		vote_helpers::restore_active_user_codes($_GET['id']);
	}
}

elseif(isset($_POST['finish_vote'])){
	$voteinfo = db_vote::get_vote_info($_GET['id']);

	if($voteinfo['status'] == "continuous"){
		$ok = db_vote_admin::finish_vote($_GET['id']);
		vote_helpers::substitute_active_for_passive_user_codes($_GET['id']);
	}
}

elseif(isset($_POST['restore_finished_vote'])){
	$voteinfo = db_vote::get_vote_info($_GET['id']);

	if($voteinfo['status'] == "finished"){
		$ok = db_vote_admin::restore_finished_vote($_GET['id']);
		vote_helpers::restore_active_user_codes($_GET['id']);
	}
}

elseif(isset($_POST['make_continuous'])){
	$voteinfo = db_vote::get_vote_info($_GET['id']);

	if($voteinfo['status'] == "active"){
		$ok = db_vote_admin::make_continuous($_GET['id']);
	}
}

elseif(isset($_POST['make_active'])){
	$voteinfo = db_vote::get_vote_info($_GET['id']);

	if($voteinfo['status'] == "continuous"){
		$ok = db_vote_admin::make_active($_GET['id']);
	}
}

if(isset($ok)){
	if($ok){
		$_SESSION['report_message'] = "Omröstningen är ändrad.";
		$redirect = $_SERVER['REQUEST_URI'];
		}
	else{
		$_SESSION['report_message'] = "Databasfel. Ingen ändring gjord.";
		$_SESSION['red_report_message'] = 1;
	}
}