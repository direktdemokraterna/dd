<?php 
	$user_data = db_user::get_user_data($_GET['id']);
	__link('<- ' . "Tillbaka till medlemmens sida", 'member', 'view', 'id=' . $_GET['id']);
	__h1("Redigera medlem");
	if($user_data['deletion_time'])
		__p("Den här användarens medlemskap avslutades " . strtolower(general_helpers::show_date($user_data['deletion_time'])) . '.');
	__open_form();
	__hidden("edit_user", 1);
	\View\member::output_edit_fields($user_data);
	__br();
	__submit_and_close("Uppdatera");
	__open_form();
	__hidden("change_password", 1);
	__hidden("username", $user_data['username']);
	__hidden("user_email", $user_data['email']);
	__submit_and_close("Skapa nytt lösenord", null, "Vill du verkligen ersätta lösenordet för denna användare med ett maskinskapat lösenord?");
?>
