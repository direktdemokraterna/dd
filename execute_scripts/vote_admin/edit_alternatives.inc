<?php
	if(isset($_POST['delete'])){
		if($_POST['vote_id'] == $_GET['id']){
			$deleted = db_vote_admin::delete_alternatives($_POST['check_list'], $_POST['vote_id']);
			if($deleted>1){
				$message = $deleted . " omröstningsalternativ raderade.";
			}
			else{
				$message = "1 omröstningsalternativ raderat.";
			}

			db_helpers::insert_error_message($_SESSION['id'], $message);
			$redirect = $_SERVER['REQUEST_URI'];
			
		}
	}

	elseif(isset($_POST['new_alternative'])){
		if($_POST['vote_id'] == $_GET['id']){

			if(isset($_POST['username'])){

				$user_id = db_user::get_user_data_from_username($_POST['username']);
				if($user_id['id']){
					$constituency_id = db_constituency::get_vote_constituency_id($_POST['vote_id']);
					if(db_constituency::check_user_constituency_access($user_id['id'], $constituency_id)){
						$ok = db_vote::add_candidate($_POST['vote_id'], $user_id['id'], $_POST['description']);
					}
					else{
						$message = "Användaren har inte valkretsbehörighet. Inget omröstningsalternativ skapat.";
						db_helpers::insert_error_message($_SESSION['id'], $message, "red");
						$redirect = $_SERVER['REQUEST_URI'];
					}
				}
				else{
					$message = "Fel användarnamn. Inget omröstningsalternativ skapat.";
					db_helpers::insert_error_message($_SESSION['id'], $message, "red");
					$redirect = $_SERVER['REQUEST_URI'];
				}

			}

			elseif(isset($_POST['title'])){
				$ok = db_vote_admin::add_alternative_by_admin($_POST['vote_id'], $_POST['title'], $_POST['description']);
			}

			if($ok){
				$message = "Omröstningsalternativ skapat.";
				db_helpers::insert_error_message($_SESSION['id'], $message);
				$redirect = $_SERVER['REQUEST_URI'];
			}
			else{
				$message = "Något gick fel. Inget omröstningsalternativ skapat.";
				db_helpers::insert_error_message($_SESSION['id'], $message, "red");
				$redirect = $_SERVER['REQUEST_URI'];
			}

		}

	}