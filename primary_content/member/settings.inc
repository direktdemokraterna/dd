
<?php 
	$tab_index = 1;
	$user_settings = db_user::get_user_data($_SESSION['id']); 
	_h1(_t("Change my profile"));
	
	_h2(_t("User information"));
	_open_form();
	\View\member::output_edit_fields($user_settings, false, $tab_index);
	_br();
	_submit_and_close(_t("Change"), "profile");

	_h2(_t("Presentation"));
	\View\general::output_text_editor(array(
		'name' => 'description'
		,'legend' => _t('Personal description (visible to all members)')
		,'target_id' => $user_settings['id']
		,'submit_text' => _t("Change")
		,'content' => $user_settings['description']));

	_h2(_t("Profile image"));
	echo '<form enctype="multipart/form-data" class="standard-form" method="post" action="">';
	_br();
	_label(_t("Personal image ") . "(jpg, gif " . _t("or") . " png)",  "settings_image");
	echo '<input type="file" name="image" value="" id="settings_image">';
	_br();
	_label(_t("Current image:"), "");
	_br();
	echo '<img class="image150" src="' . USERIMG_PATH . $user_settings['image'] . '">';
	_br();
	_submit_and_close(_t("Change"), "image");
	
	_h2(_t("Settings"));
	_open_form();
	\View\general::make_checkbox("show_email", _t("Show email address"), 1, $tab_index++, $user_settings);	
	\View\general::make_checkbox("show_telephone", _t("Show telephone number"), 1, $tab_index++, $user_settings);
	\View\general::make_checkbox("show_skype", _t("Show Skype name"), 1, $tab_index++, $user_settings);	
	_br();
	_submit_and_close(_t("Change"), "settings");
	
	_h2(_t("Change password"));
	_open_form();
	\View\general::make_password("old_password", _t("Old password"), $tab_index++);
	\View\general::make_password("new_password1", _t("New password"), $tab_index++);
	\View\general::make_password("new_password2", _t("Repeat new password"), $tab_index++);
	_br();
	_submit_and_close(_t("Change"), "password");
?>