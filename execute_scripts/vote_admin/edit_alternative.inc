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
				$_SESSION['report_message'] = "Omröstningsalternativ ändrat.";
				$redirect = "index.php?type=vote_admin&action=edit_alternatives&id=" . $alternative_info['vote_id'];
			}
			else{
				$_SESSION['report_message'] = "Något gick fel. Ingen ändring gjord.";
				$_SESSION['red_report_message'] = 1;
				$redirect = $_SERVER['REQUEST_URI'];
			}

		}

	}