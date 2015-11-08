<?php 

if(isset($_POST['title']) && isset($_POST['is_restricted'])){

	$workgroup_info = db_workgroup::get_info($_GET['id']);

	if($workgroup_info['is_restricted'] > 0 && $_POST['is_restricted'] == 0){ 
		db_workgroup::make_un_restricted($_GET['id']);
	}
	elseif($workgroup_info['is_restricted'] == 0 && $_POST['is_restricted'] == 1){ 
		db_workgroup::make_restricted($_GET['id']);
	}

	if(isset($_POST['number_of_members'])){
		$number_of_members = (int)$_POST['number_of_members'];
	}
	else{
		$number_of_members =  db_workgroup::get_member_count($_GET['id']);
	}

	$ok = db_workgroup::update($_GET['id'], forum_helpers::process_text($_POST['description']), general_helpers::clean($_POST['title']), $number_of_members);

	if($ok)
		$_SESSION['report_message'] = "Arbetsgruppen ändrad";
	else
		\Logic\general::report_error("Inga ändringar gjorda");
}

elseif(isset($_POST['delete'])){

	if(db_workgroup::is_restricted($_GET['id'])){
		db_workgroup::make_unrestricted($_GET['id']);
	}

	$ok = db_workgroup::delete($_GET['id']);

	if($ok){
		$_SESSION['report_message'] = "Arbetsgruppen borttagen";
		$redirect = "index.php?type=workgroup";
	}
	else{
		$_SESSION['report_message'] = "Inga ändringar gjorda";
		$_SESSION['red_report_message'] = 1;
	}

}