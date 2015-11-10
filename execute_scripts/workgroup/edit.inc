<?php 
	$is_member = db_workgroup::is_member($_GET['id'], $_SESSION['id']);
	if($is_member){
		$ok = db_workgroup::update($_GET['id'], forum_helpers::process_text($_POST['edit_description_content']));
		if($ok)
			$_SESSION['report_message'] = "Beskrivningen ändrad";
		else
			\Logic\util::report_error("Inga ändringar gjorda");
	}
	else
		\Logic\util::report_error("Du är inte medlem i den arbetsgruppen");
?>