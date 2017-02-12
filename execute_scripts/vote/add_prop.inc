<?php 

if(!isset($_POST['new_prop_title']) || empty($_POST['new_prop_title'])) {
	$_SESSION['report_message'] = "Rubrik saknas.";
	$_SESSION['red_report_message'] = 1;		
} 
else if(!isset($_POST['new_prop_description']) || empty($_POST['new_prop_description'])) {
	$_SESSION['report_message'] = "Beskrivning saknas.";
	$_SESSION['red_report_message'] = 1;		
} 
else if(!isset($_POST['constituency_id']) || empty($_POST['constituency_id'])) {
	$_SESSION['report_message'] = "Valkrets saknas.";
	$_SESSION['red_report_message'] = 1;		
} 
else if(!isset($_POST['type_of_vote']) || !in_array($_POST['type_of_vote'], 
	array("yes-no", "prio-vote", "candidate-election", "median", "budget"))){
	$_SESSION['report_message'] = "Omröstningstyp saknas.";
	$_SESSION['red_report_message'] = 1;		
}
else {
	$title = general_helpers::clean($_POST['new_prop_title']);
	$description = \Logic\text::process_text($_POST['new_prop_description']);
	$constituency_check = db_constituency::check_voter_constituency_access($_SESSION['id'], $_POST['constituency_id']);
	if($constituency_check){
		$insert_id = db_prop::add_prop($_POST['type_of_vote'], $_SESSION['id'], $_POST['constituency_id'], $title, $description);
		if($insert_id){
			//db_notice::make_proposition_created_notice($insert_id);
			$_SESSION['report_message'] = "Propositionen har skapats.";
			$redirect = "index.php?type=vote&action=view_prop&id=" . $insert_id;
		}
		else{
			$_SESSION['report_message'] = "Något gick fel. Propositionen kunde inte skapas.";
			$_SESSION['red_report_message'] = 1;
		}		
	}
	else{
		$_SESSION['report_message'] = "Du har inte tillgång till den valkretsen.";
		$_SESSION['red_report_message'] = 1;
	}
}
?>