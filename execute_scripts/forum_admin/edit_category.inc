<?php
	if(!empty($_POST)){
		$ok = db_forum_admin::update_category(htmlspecialchars($_POST['title'], ENT_COMPAT,'ISO-8859-1', true), htmlspecialchars($_POST['description'], ENT_COMPAT,'ISO-8859-1', true), $_GET['id']);
		if($ok){
			$_SESSION['report_message'] = "Kategoriinformation uppdaterad.";
			$redirect = $_SERVER['REQUEST_URI'];
		}
	}
?>