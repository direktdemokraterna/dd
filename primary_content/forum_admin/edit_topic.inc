<?php 
	$post_info = db_forum::get_full_post_info($_GET['id'], $_SESSION['id']);
	__h1("Moderera ämne: " . $post_info['title']);
	__h2("Flytta ämnet till ett annat forum");
	__open_form();
	__hidden("move_topic", 1);
	$move_options = db_general::make_hash(db_forum_admin::get_all_forums(), 'id', 'title');
	\View\controls::output_selector("forum_id", $move_options);
	__br();
	__submit_and_close("Flytta");
	__h2("Ta bort ämnet och flytta alla dess inlägg");
	__open_form();
	__hidden("delete_topic", 1);
	__submit_and_close("Ta bort");
?>

