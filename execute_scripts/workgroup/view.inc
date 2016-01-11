<?php
if(isset($_POST['cancel_exclude'])){
	$ok = db_workgroup::cancel_exclude($_POST['id'], $_POST['user'], $_SESSION['id']);
	if($ok){
		$_SESSION['report_message'] = _t("Your support for exclusion has been withdrawn.");
	}
}
else if(isset($_POST['support_exclude'])){
	$ok = db_workgroup::support_exclude($_POST['id'], $_POST['user'], $_SESSION['id']);
	$excluded = db_workgroup::calculate_exclusion($_POST['id'], $_POST['user']);
	if($excluded == "excluded"){
		$_SESSION['report_message'] = _t("You have supported an exclusion. The member in question is now excluded.");
	}
	elseif($excluded == "still member"){
		$_SESSION['report_message'] = _t("You have supported an exclusion. The member in question is still member of the group.");
	}
}
else if(isset($_POST['cancel_support_candidate'])){
	$ok = db_workgroup::cancel_support($_POST['id'], $_POST['user'], $_SESSION['id']);
	if($ok){
		$_SESSION['report_message'] = _t("Your support for membership has been withdrawn.");
	}
}
else if(isset($_POST['support_candidate'])){
	$ok = db_workgroup::support_membership($_POST['id'], $_POST['user'], $_SESSION['id']);
	$affirmed = db_workgroup::check_candidate_support($_POST['id'], $_POST['user']);
	if($affirmed == "new member"){
		$_SESSION['report_message'] = _t("You have supported a candidacy. The candidate is now member.");
	}
	elseif($affirmed == "still candidate"){
		$_SESSION['report_message'] = _t("You have supported a candidacy. The candidate still needs more support.");
	}

}
else if(isset($_POST['submit_candidacy'])){
	$ok = db_workgroup::submit_candidacy($_POST['id'], $_SESSION['id']);
	if($ok) $_SESSION['report_message'] = _t("Your membership application is registered.");
}
else if(isset($_POST['cancel_candidacy'])){
	$ok = db_workgroup::cancel_candidacy($_POST['id'], $_SESSION['id']);
	if($ok) $_SESSION['report_message'] = _t("Your membership application is removed.");
}
else if(isset($_POST['support_workgroup'])){
	$ok = db_workgroup::add_supporting_member($_POST['id'], $_SESSION['id']);
	if($ok){
		$created = db_workgroup::is_active($_POST['id']);
		if($created==1){
			$_SESSION['report_message'] = _t("The workgroup is now activated and you are included as member.");
		}
		else{
			$_SESSION['report_message'] = _t("Your membership application is registered.");
		}
	} 
}
else if(isset($_POST['cancel_support_workgroup'])){
	$ok = db_workgroup::remove_supporting_member($_POST['id'], $_SESSION['id']);
	if($ok) $_SESSION['report_message'] = _t("You no longer support the activation of this workgroup.");
}
else if(isset($_POST['cancel_membership'])){
	$ok = db_workgroup::drop_member($_POST['id'], $_SESSION['id']);
	if($ok) $_SESSION['report_message'] = _t("You are no longer a member of this workgroup.");
}	
?>