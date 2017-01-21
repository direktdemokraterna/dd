<?php
	$topic_id = \Logic\forum::get_requested_topic();
	$page = \Logic\forum::get_requested_page($topic_id);	
	$posts = db_forum::get_posts($topic_id, $_SESSION['id'], $page);
	$post_count = db_forum::get_post_count($topic_id);
	if (! \View\controls::output_search_back_link())
	{
		\View\forum::show_topic_title($topic_id);
		\View\forum::show_topic_breadcrumbs($topic_id);			
	}
	
	if(empty($posts))
		__p("Tråden existerar inte eller så har du inte behörighet att läsa den");
	else {
		\View\forum::show_posts($page, $posts, $post_count);
		if(isset($_SESSION['is_forum_admin']))
			echo '<p><a href="index.php?type=forum_admin&action=edit_topic&id=' . $topic_id . '" style="float: right;">Moderera ämne</a></p>';
		\View\controls::output_text_editor(array(
			'name' => 'new_post'
			,'legend' => "Svara i tråden"
			,'target_id' => $topic_id
			,'submit_text' => "Skicka"));
	}
?>
