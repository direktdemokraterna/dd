<?php 

if(isset($_POST['title']) && isset($_POST['is_restricted'])){

	$ok = db_workgroup::update($_GET['id'], forum_helpers::process_text($_POST['description']), general_helpers::clean($_POST['title']), (int)$_POST['number_of_members'], (int)$_POST['is_restricted']);

	if($ok){
		$_SESSION['report_message'] = "Arbetsgruppen ändrad";
		$redirect = $_SERVER['REQUEST_URI'];
	}
	else{
		$_SESSION['report_message'] = "Inga ändringar gjorda";
		$_SESSION['red_report_message'] = 1;
	}

}