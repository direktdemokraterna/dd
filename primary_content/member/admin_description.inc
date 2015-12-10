<?php 
	$admin_role_info = db_admin::get_admin_role_info($_GET['id']);
	_h1($admin_role_info['title']);
	echo '<p>';
	_strong(_t("Description:"));
	_br();
	echo empty($admin_role_info['description']) 
		? _t("No description.")
		: $admin_role_info['description'];
	echo '</p>';
	$list_of_admins = db_admin::get_admin_role_users($_GET['id']);
	echo '<p>';
	_strong(_t("Members who has this role:"));
	_br();
	foreach($list_of_admins as $row) {
		echo \View\member::link($row);
		_br();
	}
?>
