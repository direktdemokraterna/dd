<?php 
	$forum_info = db_forum_admin::get_forum_info($_GET['id']);
	_h1($forum_info['title']);
	_open_form();
	\View\controls::make_textfield("title", _t("Name"), 1, $forum_info);
	\View\controls::make_textarea("description", _t("Description"), 2, $forum_info);
	\View\forum::output_category_selector($forum_info['category_id']);
	_br();
	_submit_and_close(_t("Update"));
?>
