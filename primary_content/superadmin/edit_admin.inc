<?php 
	$userdata = db_user::get_user_data($_GET['id']); 
	__h1($userdata['first_name'] . " " . $userdata['last_name']);
	__strong(_t("Administrator roles for this user"));
	__br();
	__open_form("standard-form checkbox-form");
	echo '<ul class="checkbox-grid">';
	$admin_roles = db_admin::get_all_admin_roles_and_if_user_belongs($_GET['id']);
	foreach($admin_roles as $row) {
		echo '<li><input type="checkbox" name="check_list[]" id="' . $row['title'] . '" value="' . $row['id'] 
			. '"' . ($row['user_role'] ? ' checked>' : '>');
		__label(_t($row['title']), $row['title']);
		echo '</li>';
	}
	echo '</ul><div class="clear"></div><br>';
	__submit_and_close(_t('Change'));
?>
