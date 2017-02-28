<?php
	if(!empty($_POST['check_list'])) 
		$ok = db_admin::update_admin_roles_for_user($_POST['check_list'], $_GET['id']);
	else
		$ok = db_admin::remove_all_admin_roles_for_user($_GET['id']);
	if($ok)
		$_SESSION['report_message'] = "Adminroller uppdaterade";
?>