<?php 
	$forum_info = db_forum_admin::get_forum_info($_GET['id']);
	__h1($forum_info['title']);
	__open_form();
	__textfield("title", _t("Name"), 1, $forum_info);
	__textarea("description", _t("Description"), 2, $forum_info);
	\View\forum::output_category_selector($forum_info['category_id']);
	__br();
	__submit_and_close(_t("Update"));
?>
