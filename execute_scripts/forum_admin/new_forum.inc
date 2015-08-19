<?php
	if(!empty($_POST)){
		if($_POST['access_type']==2) $access_type = "private";
		else $access_type = "public";
		$ok = db_forum_admin::add_forum($_POST['category'], htmlspecialchars($_POST['title'], ENT_COMPAT,'ISO-8859-1', true), htmlspecialchars($_POST['description'], ENT_COMPAT,'ISO-8859-1', true), $access_type);
		if($ok){
			$_SESSION['report_message'] = "Forumet skapat"; 
			$redirect = $_SERVER['REQUEST_URI'];
		}
	}
?>