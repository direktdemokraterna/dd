<?php
	if(!empty($_POST)){
		$ok = db_forum_admin::update_forum($_POST['category'], htmlspecialchars($_POST['title']), htmlspecialchars($_POST['description']), $_GET['id']);
		if($ok){
			$_SESSION['report_message'] = "Foruminformation uppdaterad."; 
			$redirect = $_SERVER['REQUEST_URI'];
		}
	}
?>