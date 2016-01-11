<?php 
	$user_data = db_user::get_user_data($_GET['id']);
	__link('<- ' . _t("Back to the member page"), 'member', 'view', 'id=' . $_GET['id']);
	__h1(_t("Edit member"));
	if($user_data['deletion_time'])
		__p(_t("This member's membership was terminated ") . strtolower(general_helpers::show_date($user_data['deletion_time'])) . '.');
	__open_form();
	__hidden("edit_user", 1);
	\View\member::output_edit_fields($user_data);
	__br();
	__submit_and_close(_t("Update"));
	__open_form();
	__hidden("change_password", 1);
	__hidden("username", $user_data['username']);
	__hidden("user_email", $user_data['email']);
	__submit_and_close(_t("Generate new password"), null, _t("Do you really want to replace the password for this user with an auto-generated password?"));
?>
