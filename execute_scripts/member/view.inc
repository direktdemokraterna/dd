<?php 

if(isset($_POST['delete_user'])){
	$ok = db_member_admin::delete_user($_GET['id']);
	if($ok){
		$_SESSION['report_message'] = "Användaren är borttagen ur medlemslistan";
		$redirect = $_SERVER['REQUEST_URI'];
	}
}
elseif(isset($_POST['restore_user'])){
	$ok = db_member_admin::restore_user($_GET['id']);
	if($ok){
		$_SESSION['report_message'] = "Användaren har återställts i medlemslistan";
		$redirect = $_SERVER['REQUEST_URI'];
	}
}

?>