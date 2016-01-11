<?php 
	$is_member = db_workgroup::is_member($_GET['id'], $_SESSION['id']);
	if($is_member){
		$ok = db_workgroup::update($_GET['id'], \Logic\text::process_text($_POST['edit_description_content']));
		if($ok)
			$_SESSION['report_message'] = _t("Description changed");
		else
			\Logic\util::report_error(_t("No changes made"));
	}
	else
		\Logic\util::report_error(_t("You are not member of that workgroup"));
?>