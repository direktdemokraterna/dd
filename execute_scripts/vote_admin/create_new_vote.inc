<?php 

	if(isset($_POST['vote_status']) && isset($_POST['type_of_vote']) && isset($_POST['constituency_id']) && isset($_POST['title'])){

		if(db_constituency::check_that_constituency_exists($_POST['constituency_id'])){

			if($_POST['type_of_vote'] == "yes-no" || $_POST['type_of_vote'] == "prio-vote" || $_POST['type_of_vote'] == "candidate-election" || $_POST['type_of_vote'] == "median" || $_POST['type_of_vote'] == "budget"){

				if($_POST['vote_status'] == "active"){
					
					$time_string = (int)$_POST['year'] . "-" . (int)$_POST['month'] . "-" . (int)$_POST['day'] . " " . (int)$_POST['hour'] . ":" . (int)$_POST['minute'] . ":00";
					
					$timestamp_ended = strtotime($time_string);
					$timestamp_delegate_ended = ($timestamp_ended - time()) / 2 + time();

					// Creating forum topic
					$forum_id = db_constituency::get_constituency_forum_id($_POST['constituency_id']);

					$forum_topic_id = db_forum::new_topic($_SESSION['id'], $forum_id, $_POST['title']);
					db_forum::add_content_to_post($forum_topic_id, $_POST['description']);


					$ok = db_vote_admin::create_vote($_POST['type_of_vote'], $_POST['vote_status'], $_POST['constituency_id'], $_POST['title'], $_POST['description'], $forum_topic_id, $timestamp_ended, $timestamp_delegate_ended); 

				}
				elseif($_POST['vote_status'] == "continuous"){

					// Creating forum topic
					$forum_id = db_constituency::get_constituency_forum_id($_POST['constituency_id']);

					$forum_topic_id = db_forum::new_topic($_SESSION['id'], $forum_id, $_POST['title']);
					db_forum::add_content_to_post($forum_topic_id, $_POST['description']);


					$ok = db_vote_admin::create_vote($_POST['type_of_vote'], $_POST['vote_status'], $_POST['constituency_id'], $_POST['title'], $_POST['description'], $forum_topic_id, null, null); 

				}

				if($ok){
					$_SESSION['report_message'] = "Omröstningen är skapad.";
					$redirect = "index.php?type=vote&action=view_vote&id=" . $ok;
				}
				else{
					$_SESSION['report_message'] = "Något gick fel. Ingen omröstning skapad.";
					$_SESSION['red_report_message'] = 1;
				}

			}

		}

	}