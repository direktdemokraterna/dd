
<?php 
	$tab_index = 1;
	$user_settings = db_user::get_user_data($_SESSION['id']); 
	__h1("Ändra min profil");
	
	__h2("Användarinformation");
	__open_form();
	\View\member::output_edit_fields($user_settings, false, $tab_index);
	__br();
	__submit_and_close("Ändra", "profile");

	__h2("Presentation");
	\View\controls::output_text_editor(array(
		'name' => 'description'
		,'legend' => "Personlig beskrivning (synlig för alla medlemmar)"
		,'target_id' => $user_settings['id']
		,'submit_text' => "Ändra"
		,'content' => $user_settings['description']));

	__h2("Bild");
	echo '<form enctype="multipart/form-data" class="standard-form" method="post" action="">';
	__br();
	__label("Personlig bild (jpg, gif eller png)",  "settings_image");
	echo '<input type="file" name="image" value="" id="settings_image">';
	__br();
	__label("Nuvarande bild:", "");
	__br();
	echo '<img class="image150" src="' . USERIMG_PATH . 'userimg_150_width/' . $user_settings['image'] . '">';
	__br();
	__submit_and_close("Ändra", "image");
	
	__h2("Inställningar");
	__open_form();
	__checkbox("show_email", "Visa mejladress", 1, $tab_index++, $user_settings);	
	__checkbox("show_telephone", "Visa telefonnummer", 1, $tab_index++, $user_settings);
	__checkbox("show_skype", "Visa Skype-namn", 1, $tab_index++, $user_settings);	
	__br();
	__submit_and_close("Ändra", "settings");
	
	__h2("Ändra lösenord");
	__open_form();
	__password("old_password", "Gammalt lösenord", $tab_index++);
	__password("new_password1", "Nytt lösenord", $tab_index++);
	__password("new_password2", "Upprepa nytt lösenord", $tab_index++);
	__br();
	__submit_and_close("Ändra", "password");
?>