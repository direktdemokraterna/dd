
<?php 
	$tab_index = 1;
	$user_settings = db_user::get_user_data($_SESSION['id']); 
	_h1(_t("Change my profile"));
	
	_h2(_t("Change user information"));
	_open_form();
	_hidden("form_type", "profile");
	\View\member::output_edit_fields($user_settings, false, $tab_index);
	_br();
	_submit_and_close(_t("Change"));

	_h2(_t("Change presentation"));
	_open_form();
	_hidden("form_type", "description");
	\View\general::make_textarea("settings_description", _t("Personal description (visible to all members)"), $tab_index++, forum_helpers::de_process_text($user_settings['description']));	
	_submit_and_close(_t("Change"));
	
	_h2(_t("Change profile image"));
	echo '<form enctype="multipart/form-data" class="standard-form" method="post" action="">';
	_hidden("form_type", "image");
	_br();
	_label(_t("Personal image ") . "(jpg, gif " . _t("or") . " png)",  "settings_image");
	echo '<input type="file" name="image" value="" id="settings_image">';
	_br();
	_label(_t("Current image:"), "");
	_br();
	echo '<img class="image150" src="' . USERIMG_PATH . $user_settings['image'] . '">';
	_br();
	_submit_and_close(_t("Change"));
	
	_h2(_t("Change settings"));
	_open_form();
	_hidden("form_type", "settings");
	\View\general::make_checkbox("show_email", _t("Show email address"), 1, $tab_index++, $user_settings);	
	\View\general::make_checkbox("show_telephone", _t("Show telephone number"), 1, $tab_index++, $user_settings);
	\View\general::make_checkbox("show_skype", _t("Show Skype name"), 1, $tab_index++, $user_settings);	
	_br();
	_submit_and_close(_t("Change"));
	
	_h2(_t("Change password"));
	_open_form();
	_hidden("form_type", "password");
	\View\general::make_password("old_password", _t("Old password"), $tab_index++);
	\View\general::make_password("new_password1", _t("New password"), $tab_index++);
	\View\general::make_password("new_password2", _t("Repeat new password"), $tab_index++);
	_br();
	_submit_and_close(_t("Change"));
?>