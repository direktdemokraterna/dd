<?php 
	$alternative_info = db_vote::get_alternative_info($_GET['id']);
	__h1(_t("Edit vote alternative"));
	__open_form();
	__hidden("alternative_id", $alternative_info['id']);
	if(isset($alternative_info['user_id']))
		__textfield("username", _t("User"), 1, $alternative_info['alternative_title']);
	else 
		__textfield("title", _t("Title"), 1, $alternative_info['alternative_title']);
	__textarea("description", _t("Description"), 2, $alternative_info['alternative_description']);
	__submit_and_close(_t("Update"));
?>
