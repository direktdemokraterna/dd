<?php
	if(isset($_POST['alternative_id'])){

		if($_POST['alternative_id'] == $_GET['id']){

			$alternative_info = db_vote::get_alternative_info($_GET['id']);

			if(isset($_POST['username'])){
				$alternative_title = db_user::get_user_full_name($alternative_info['user_id']);
			}
			else{
				$alternative_title = $_POST['title'];
			}

			$ok = db_vote_admin::update_alternative($alternative_title, $_POST['description'], $_GET['id']);

			if($ok){
				$message = "Omröstningsalternativ ändrat.";
				db_helpers::insert_error_message($_SESSION['id'], $message);
				$redirect = "index.php?type=vote_admin&action=edit_alternatives&id=" . $alternative_info['vote_id'];
			}
			else{
				$message = "Något gick fel. Ingen ändring gjord.";
				db_helpers::insert_error_message($_SESSION['id'], $message, "red");
				$redirect = $_SERVER['REQUEST_URI'];
			}

		}

	}