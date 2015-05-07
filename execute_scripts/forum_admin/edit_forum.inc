<?php
	if(!empty($_POST)){
		$ok = db_forum_admin::update_forum($_POST['category'], htmlspecialchars($_POST['title']), htmlspecialchars($_POST['description']), $_GET['id']);
		if($ok){
			$message = "Foruminformation uppdaterad."; 
			db_helpers::insert_error_message($_SESSION['id'], $message);
			$redirect = $_SERVER['REQUEST_URI'];
		}
	}
?>