<?php
	__h1("Skapa ny proposition");
	__open_form();
	\View\vote::make_vote_type_selector(isset($_POST["type_of_vote"]) ? $_POST["type_of_vote"] : null);
	\View\vote::make_constituency_selector(
		isset($_POST["constituency_id"]) ? $_POST["constituency_id"] : null
		, $_SESSION['id']); 
	\View\vote::make_title_input(); 
	\View\vote::make_description_input(); 
	__br();
	__submit_and_close("Skicka", null, null, 5);
?>
