<?php 
	$admin_role_info = db_admin::get_admin_role_info($_GET['id']);
	__h1(_t($admin_role_info['title']));
	echo '<p>';
	__strong(_t("Description:"));
	__br();
	echo empty($admin_role_info['description']) 
		? _t("No description.")
		: $admin_role_info['description'];
	echo '</p>';
	$list_of_admins = db_admin::get_admin_role_users($_GET['id']);
	echo '<p>';
	__strong(_t("Members who has this role:"));
	__br();
	foreach($list_of_admins as $row) {
		echo \View\member::link($row);
		__br();
	}
?>
