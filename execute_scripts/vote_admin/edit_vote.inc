<?php 

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
						$message = "Omröstningen är ändrad.";
						db_helpers::insert_error_message($_SESSION['id'], $message);
						$redirect = $_SERVER['REQUEST_URI'];
					}
					else{
						$message = "Databasfel. Ingen ändring gjord.";
						db_helpers::insert_error_message($_SESSION['id'], $message, "red");
					}

				}
				else{
					$message = "Fel omröstningstyp. Ingen ändring gjord.";
					db_helpers::insert_error_message($_SESSION['id'], $message, "red");
				}

			}
			else{
				$message = "Valkretsfel. Ingen ändring gjord.";
				db_helpers::insert_error_message($_SESSION['id'], $message, "red");
			}

		}

	}
