<?php
	if(!empty($_POST)){
		$ok = db_forum_admin::add_category(htmlspecialchars($_POST['title'], ENT_COMPAT,'ISO-8859-1', true), htmlspecialchars($_POST['description'], ENT_COMPAT,'ISO-8859-1', true));
		if($ok){
			$_SESSION['report_message'] = "Kategorin skapad"; 
			$redirect = $_SERVER['REQUEST_URI'];
		}
	}
?>