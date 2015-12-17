<?php
	$ok = db_forum_admin::update_category(general_helpers::clean($_POST['title']), general_helpers::clean($_POST['description']), $_GET['id']);
	if($ok)
		$_SESSION['report_message'] = _t("Category information updated.");
?>