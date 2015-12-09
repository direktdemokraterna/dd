<?php 
	$user_data = db_user::get_user_data($_GET['id']);
	_link('<- ' . _t("Back to the member page"), 'member', 'view', 'id=' . $_GET['id']);
	_h1(_t("Edit member"));
	if($user_data['deletion_time'])
		_p(_t("This member has been removed from the list of members ") . strtolower(general_helpers::show_date($user_data['deletion_time'])) . '.');
	_open_form();
	_hidden("edit_user", 1);
	\View\member::output_edit_fields($user_data);
	_br();
	_submit_and_close(_t("Update"));
	_open_form();
	_hidden("change_password", 1);
	_hidden("username", $user_data['username']);
	_hidden("user_email", $user_data['email']);
	_submit_and_close(_t("Generate new password"), _t("Do you really want to replace the password for this user with an auto-generated password?"));
?>
