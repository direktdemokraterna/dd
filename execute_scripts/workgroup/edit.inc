<?php 

if(isset($_POST['confirm_change'])){

	$is_member = db_workgroup::is_member($_GET['id'], $_SESSION['id']);

	if($is_member){
		$ok = db_workgroup::update($_GET['id'], forum_helpers::process_text($_POST['description']));

		if($ok){
			$_SESSION['report_message'] = "Beskrivningen ändrad";
			$redirect = $_SERVER['REQUEST_URI'];
		}
		else{
			$_SESSION['report_message'] = "Inga ändringar gjorda";
			$_SESSION['red_report_message'] = 1;
		}
	}
	else{
		$_SESSION['report_message'] = "Du är inte medlem i den arbetsgruppen";
		$_SESSION['red_report_message'] = 1;
	}

}