<?php
	__h1("Administratörer");
	$admin_roles = db_admin::get_all_admin_roles();
	foreach($admin_roles as $admin_role) {
		__h2($admin_role['title']);
			$admins_for_this_role = db_admin::get_admin_role_users($admin_role['id']);
		foreach($admins_for_this_role as $admin){
			echo \View\member::link($admin);
			__br();			
		}
	}
?>

