<?php
	_h1(_t("Administrators"));
	$admin_roles = db_admin::get_all_admin_roles();
	foreach($admin_roles as $admin_role) {
		_h2(_t($admin_role['title']));
			$admins_for_this_role = db_admin::get_admin_role_users($admin_role['id']);
		foreach($admins_for_this_role as $admin){
			echo \View\member::link($admin);
			_br();			
		}
	}
?>

