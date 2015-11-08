<?php 

if(isset($_POST['confirm_change'])){
	$is_member = db_workgroup::is_member($_GET['id'], $_SESSION['id']);
	if($is_member){
		$ok = db_workgroup::update($_GET['id'], forum_helpers::process_text($_POST['description']));
		if($ok)
			$_SESSION['report_message'] = "Beskrivningen ändrad";
		else
			\Logic\general::report_error("Inga ändringar gjorda");
	}
	else
		\Logic\general::report_error("Du är inte medlem i den arbetsgruppen");
}