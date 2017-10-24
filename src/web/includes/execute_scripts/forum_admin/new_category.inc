<?php
	$ok = db_forum_admin::add_category(general_helpers::clean($_POST['title']), general_helpers::clean($_POST['description']));
	if($ok)
		$_SESSION['report_message'] = "Kategori skapad"; 
?>