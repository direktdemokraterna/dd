<?php 
	$alternative_info = db_vote::get_alternative_info($_GET['id']);
	__h1("Ändra omröstningsalternativ");
	__open_form();
	__hidden("alternative_id", $alternative_info['id']);
	if(isset($alternative_info['user_id']))
		__textfield("username", "Användare", 1, $alternative_info['alternative_title']);
	else 
		__textfield("title", "Titel", 1, $alternative_info['alternative_title']);
	__textarea("description", "Beskrivning", 2, $alternative_info['alternative_description']);
	__submit_and_close("Uppdatera");
?>
