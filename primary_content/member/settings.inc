
<?php 
	$tab_index = 1;
	$user_settings = db_user::get_user_data($_SESSION['id']); 
	__h1(_t("Change my profile"));
	
	__h2(_t("User information"));
	__open_form();
	\View\member::output_edit_fields($user_settings, false, $tab_index);
	__br();
	__submit_and_close(_t("Change"), "profile");

	__h2(_t("Presentation"));
	\View\controls::output_text_editor(array(
		'name' => 'description'
		,'legend' => _t('Personal description (visible to all members)')
		,'target_id' => $user_settings['id']
		,'submit_text' => _t("Change")
		,'content' => $user_settings['description']));

	__h2(_t("Profile image"));
	echo '<form enctype="multipart/form-data" class="standard-form" method="post" action="">';
	__br();
	__label(_t("Personal image ") . "(jpg, gif " . _t("or") . " png)",  "settings_image");
	echo '<input type="file" name="image" value="" id="settings_image">';
	__br();
	__label(_t("Current image:"), "");
	__br();
	echo '<img class="image150" src="' . USERIMG_PATH . $user_settings['image'] . '">';
	__br();
	__submit_and_close(_t("Change"), "image");
	
	__h2(_t("Settings"));
	__open_form();
	__checkbox("show_email", _t("Show email address"), 1, $tab_index++, $user_settings);	
	__checkbox("show_telephone", _t("Show telephone number"), 1, $tab_index++, $user_settings);
	__checkbox("show_skype", _t("Show Skype name"), 1, $tab_index++, $user_settings);	
	__br();
	__submit_and_close(_t("Change"), "settings");
	
	__h2(_t("Change password"));
	__open_form();
	__password("old_password", _t("Old password"), $tab_index++);
	__password("new_password1", _t("New password"), $tab_index++);
	__password("new_password2", _t("Repeat new password"), $tab_index++);
	__br();
	__submit_and_close(_t("Change"), "password");
?>