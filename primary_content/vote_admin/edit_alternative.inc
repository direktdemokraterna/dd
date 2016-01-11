<?php 
	$alternative_info = db_vote::get_alternative_info($_GET['id']);
	_h1(_t("Edit vote alternative"));
	_open_form();
	_hidden("alternative_id", $alternative_info['id']);
	if(isset($alternative_info['user_id']))
		\View\controls::make_textfield("username", _t("User"), 1, $alternative_info['alternative_title']);
	else 
		\View\controls::make_textfield("title", _t("Title"), 1, $alternative_info['alternative_title']);
	\View\controls::make_textarea("description", _t("Description"), 2, $alternative_info['alternative_description']);
	_submit_and_close(_t("Update"));
?>
