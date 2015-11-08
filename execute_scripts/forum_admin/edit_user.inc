<?php
	if(!empty($_POST['check_list'])) {
		$ok = db_forum_admin::update_forums_for_user($_POST['check_list'], $_GET['id']);
		$list_changed = $ok>0;
		$_SESSION['report_message'] = $list_changed
			? "Forumbehörigheter uppdaterade."
			: "Inga ändringar gjorda.";
	}
?>