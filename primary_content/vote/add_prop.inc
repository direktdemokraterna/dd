<?php
	_h1(_t("Create new proposition"));
	_open_form();
	\View\vote::make_vote_type_selector(isset($_POST["type_of_vote"]) ? $_POST["type_of_vote"] : null);
	\View\vote::make_constituency_selector(
		isset($_POST["constituency_id"]) ? $_POST["constituency_id"] : null
		, $_SESSION['id']); 
	\View\vote::make_title_input(); 
	\View\vote::make_description_input(); 
	_br();
	_submit_and_close(_t("Send"), null, 5);
?>
