<?php 
	$post_info = db_forum::get_full_post_info($_GET['id'], $_SESSION['id']);
	_h1(_t("Moderate topic: ") . $post_info['title']);
	_h2(_t("Move the topic to another forum"));
	_open_form();
	_hidden("move_topic", 1);
	$move_options = db_general::make_hash(db_forum_admin::get_all_forums(), 'id', 'title');
	\View\controls::make_selector("forum_id", $move_options);
	_br();
	_submit_and_close(_t("Move"));
	_h2(_t("Delete the topic and all its posts"));
	_open_form();
	_hidden("delete_topic", 1);
	_submit_and_close(_t("Delete"));
?>

