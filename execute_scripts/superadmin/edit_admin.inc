<?php
	if($_POST){
		if(!empty($_POST['check_list'])) {
			$ok = db_admin::update_admin_roles_for_user($_POST['check_list'], $_GET['id']);
		}
		else{
			$ok = db_admin::remove_all_admin_roles_for_user($_GET['id']);
		}

		if($ok>0){
			$_SESSION['report_message'] = "Administratörsrättigheter uppdaterade.";
			$redirect = $_SERVER['REQUEST_URI'];
		}

	}
?>