<?php
	if($_POST['access_type']==2) $access_type = "private";
	else $access_type = "public";
	$ok = db_forum_admin::add_forum($_POST['category'], general_helpers::clean($_POST['title']), general_helpers::clean($_POST['description']), $access_type);
	if($ok){
		$_SESSION['report_message'] = "Forumet skapat"; 
		$redirect = $_SERVER['REQUEST_URI'];
	}
?>