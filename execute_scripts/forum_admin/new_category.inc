<?php
	if(!empty($_POST)){
		$ok = db_forum_admin::add_category(htmlspecialchars($_POST['title']), htmlspecialchars($_POST['description']));
		if($ok){
			$message = "Kategorin skapad"; 
			db_helpers::insert_error_message($_SESSION['id'], $message);
			$redirect = $_SERVER['REQUEST_URI'];
		}
	}
?>