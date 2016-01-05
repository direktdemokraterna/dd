<?php
	if(!empty($_POST['check_list']))
		$ok = \Logic\constituency::update_constituencies_for_user($_POST['check_list'], $_GET['id']);
	if($ok)
		$_SESSION['report_message'] = _t("Constituency permissions updated.");
	else
		$_SESSION['report_message'] = _t("No changes made.");
?>