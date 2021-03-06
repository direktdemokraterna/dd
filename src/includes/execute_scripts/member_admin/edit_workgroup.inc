<?php 
if(isset($_POST['delete'])){
	if(db_workgroup::is_restricted($_GET['id']))
		db_workgroup::make_unrestricted($_GET['id']); //todo: doesn't exist yet
	$ok = db_workgroup::delete($_GET['id']);
	if($ok){
		$_SESSION['report_message'] = "Arbetsgrupp borttagen";
		$redirect = "index.php?type=workgroup";
	}
	else
		\Logic\util::report_error("Inga ändringar utförda");
}
else if(isset($_POST['title']) && isset($_POST['is_restricted'])){
	$workgroup_info = db_workgroup::get_info($_GET['id']);
	if(($workgroup_info['membership_vote_id'] > 0) != $_POST['is_restricted']) {
		if ($_POST['is_restricted'])
			db_workgroup::make_restricted($_GET['id']);
		else 
			db_workgroup::make_un_restricted($_GET['id']);
		$restricted_changed = true;
		$number_of_members = null;
	}
	else $number_of_members = isset($_POST['number_of_members'])
		? (int)$_POST['number_of_members']
		: null;
	$ok = db_workgroup::update($_GET['id'], null, 
		general_helpers::clean($_POST['title']), $number_of_members);
	if($ok || $restricted_changed)
		$_SESSION['report_message'] = "Arbetsgrupp ändrad";
	else
		\Logic\util::report_error("Inga ändringar utförda");
}
else if(isset($_POST['edit_description_content'])){
	$ok = db_workgroup::update($_GET['id'], \Logic\text::process_text($_POST['edit_description_content']));
	if($ok)
		$_SESSION['report_message'] = "Beskrivning ändrad";
	else
		\Logic\util::report_error("Inga ändringar utförda");
}
