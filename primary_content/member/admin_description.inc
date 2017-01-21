<?php 
	$admin_role_info = db_admin::get_admin_role_info($_GET['id']);
	__h1($admin_role_info['title']);
	echo '<p>';
	__strong("Beskrivning:");
	__br();
	echo empty($admin_role_info['description']) 
		? "Ingen beskrivning."
		: $admin_role_info['description'];
	echo '</p>';
	$list_of_admins = db_admin::get_admin_role_users($_GET['id']);
	echo '<p>';
	__strong("Medlemmar som har denna admin-behörighet:");
	__br();
	foreach($list_of_admins as $row) {
		echo \View\member::link($row);
		__br();
	}
?>
