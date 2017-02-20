
<?php 
	$tab_index = 1;
	$user_settings = db_user::get_user_data($_SESSION['id']); 
	__h1("Ändra min profil");
	
	__h2("Användarinformation");
	__open_form();
	\View\member::output_edit_fields($user_settings, false, $tab_index);
	__br();
	__submit_and_close("Ändra", "profile", null, $tab_index++);

	__h2("Presentation");
	\View\controls::output_text_editor(array(
	    'tab_index' => $tab_index++,
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
	__submit_and_close("Ändra", "image", null, $tab_index++);
	
	__h2("Inställningar");
	__open_form();
	__checkbox("show_email", "Visa mejladress", 1, $tab_index++, $user_settings);	
	__checkbox("show_telephone", "Visa telefonnummer", 1, $tab_index++, $user_settings);
	__checkbox("show_skype", "Visa Skype-namn", 1, $tab_index++, $user_settings);	
	__br();
	__submit_and_close("Ändra", "settings", null, $tab_index++);
	
	__h2("Ändra lösenord");
	__open_form();
	__password("old_password", "Gammalt lösenord", $tab_index++);
	__password("new_password1", "Nytt lösenord", $tab_index++);
	__password("new_password2", "Upprepa nytt lösenord", $tab_index++);
	__br();
	__submit_and_close("Ändra", "password", null, $tab_index);

	__h2("Notifieringar");
	__open_form();
	$notice_user_settings = db_notice::get_user_settings($_SESSION['id']);
	__strong("När någon citerar ett inlägg av dig");
	__checkbox("view_quoting_post", "Visa i toppmenyn", 1, $tab_index++, $notice_user_settings['view_quoting_post']);
	__checkbox("email_quoting_post", "Mejla avisering", 1, $tab_index++, $notice_user_settings['email_quoting_post']);
	__br();
	__strong("När en ny omröstning startar");
	__checkbox("view_vote_started", "Visa i toppmenyn", 1, $tab_index++, $notice_user_settings['view_vote_started']);
	__checkbox("email_vote_started", "Mejla avisering", 1, $tab_index++, $notice_user_settings['email_vote_started']);
	__br();
	__strong("När en omröstning avslutas");
	__checkbox("view_vote_finished", "Visa i toppmenyn", 1, $tab_index++, $notice_user_settings['view_vote_finished']);
	__checkbox("email_vote_finished", "Mejla avisering", 1, $tab_index++, $notice_user_settings['email_vote_finished']);
	__br();
	__strong("När en proposition skapas");
	__checkbox("view_proposition_created", "Visa i toppmenyn", 1, $tab_index++, $notice_user_settings['view_proposition_created']);
	__checkbox("email_proposition_created", "Mejla avisering", 1, $tab_index++, $notice_user_settings['email_proposition_created']);
	__br();
	__strong("När du får ett personligt meddelande");
	__checkbox("email_message", "Mejla avisering", 1, $tab_index++, $notice_user_settings['email_message']);
	__br();
	__strong("Hur ofta vill du få mejlaviseringar");
	$interval_options = Array(
		0 => "Omedelbart"
		,3600 => "Varje timme"
		,86400 => "Varje dag"
		,604800 => "Varje vecka"
	);
	__br();
	\View\controls::output_selector("email_notification_interval", $interval_options, $notice_user_settings['email_notification_interval']);
	__br();
	__submit_and_close("Uppdatera", "notice", null, $tab_index++);

?>