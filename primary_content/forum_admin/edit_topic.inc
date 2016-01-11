<?php 
	$post_info = db_forum::get_full_post_info($_GET['id'], $_SESSION['id']);
	__h1(_t("Moderate topic: ") . $post_info['title']);
	__h2(_t("Move the topic to another forum"));
	__open_form();
	__hidden("move_topic", 1);
	$move_options = db_general::make_hash(db_forum_admin::get_all_forums(), 'id', 'title');
	\View\controls::output_selector("forum_id", $move_options);
	__br();
	__submit_and_close(_t("Move"));
	__h2(_t("Delete the topic and all its posts"));
	__open_form();
	__hidden("delete_topic", 1);
	__submit_and_close(_t("Delete"));
?>

