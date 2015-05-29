<?php
	if(!empty($_POST)){
		$ok = db_forum_admin::add_category(htmlspecialchars($_POST['title']), htmlspecialchars($_POST['description']));
		if($ok){
			$_SESSION['report_message'] = "Kategorin skapad"; 
			$redirect = $_SERVER['REQUEST_URI'];
		}
	}
?>