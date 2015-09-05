<?php
	if(!empty($_POST['check_list'])) {
		$ok = db_constituency::update_constituencies_for_user($_POST['check_list'], $_GET['id']);
	}

	if($ok>0){
		$_SESSION['report_message'] = "Valkretsbehörigheter uppdaterade.";
		$redirect = $_SERVER['REQUEST_URI'];
	}
	else{
		$_SESSION['report_message'] = "Inga ändringar gjorda.";
		$redirect = $_SERVER['REQUEST_URI'];
	}
?>