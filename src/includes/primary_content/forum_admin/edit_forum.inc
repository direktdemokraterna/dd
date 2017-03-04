<?php 
	$forum_info = db_forum_admin::get_forum_info($_GET['id']);
	__h1($forum_info['title']);
	__open_form();
	__textfield("title", "Namn", 1, $forum_info);
	__textarea("description", "Beskrivning", 2, $forum_info);
	\View\forum::output_category_selector($forum_info['category_id']);
	__br();
	__submit_and_close("Uppdatera");
?>
