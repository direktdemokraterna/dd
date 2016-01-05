<?php 

if(!isset($_POST['new_prop_title']) || empty($_POST['new_prop_title'])) {
	$_SESSION['report_message'] = _t("Title missing.");
	$_SESSION['red_report_message'] = 1;		
} 
else if(!isset($_POST['new_prop_description']) || empty($_POST['new_prop_description'])) {
	$_SESSION['report_message'] = _t("Description missing.");
	$_SESSION['red_report_message'] = 1;		
} 
else if(!isset($_POST['constituency_id']) || empty($_POST['constituency_id'])) {
	$_SESSION['report_message'] = _t("Constituency missing.");
	$_SESSION['red_report_message'] = 1;		
} 
else if(!isset($_POST['type_of_vote']) || !in_array($_POST['type_of_vote'], 
	array("yes-no", "prio-vote", "candidate-election", "median", "budget"))){
	$_SESSION['report_message'] = _t("Vote type missing or is invalid.");
	$_SESSION['red_report_message'] = 1;		
}
else {
	$title = general_helpers::clean($_POST['new_prop_title']);
	$description = forum_helpers::process_text($_POST['new_prop_description']);
	$constituency_check = db_constituency::check_voter_constituency_access($_SESSION['id'], $_POST['constituency_id']);
	if($constituency_check){
		$insert_id = db_prop::add_prop($_POST['type_of_vote'], $_SESSION['id'], $_POST['constituency_id'], $title, $description);
		if($insert_id){
			$_SESSION['report_message'] = _t("The proposition is created.");
			$redirect = "index.php?type=vote&action=view_prop&id=" . $insert_id;
		}
		else{
			$_SESSION['report_message'] = _t("Something went wrong. The proposition could not be created.");
			$_SESSION['red_report_message'] = 1;
		}		
	}
	else{
		$_SESSION['report_message'] = _("You don't have access to that constituency.");
		$_SESSION['red_report_message'] = 1;
	}
}
?>