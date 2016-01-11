<?php
	$topic_id = \Logic\forum::get_requested_topic();
	$page = \Logic\forum::get_requested_page($topic_id);	
	$posts = db_forum::get_posts($topic_id, $_SESSION['id'], $page);
	$post_count = db_forum::get_post_count($topic_id);
	if (isset($_GET['from_action']))
		\View\controls::output_search_back_link();
	else
		\View\forum::show_topic_breadcrumbs($topic_id);		
	\View\forum::show_topic_title($topic_id);
	if(empty($posts))
		echo _p(_t("The thread doesn't exist or you don't have permission to read it."));
	else {
		\View\forum::show_posts("index.php?type=forum&action=show_posts&topic_id=" . $topic_id, $page, $posts, $post_count);
		if(isset($_SESSION['is_forum_admin']))
			echo '<p><a href="index.php?type=forum_admin&action=edit_topic&id=' . $topic_id . '" style="float: right;">' . _t("Moderate topic") . '</a></p>';
		\View\controls::output_text_editor(array(
			'name' => 'new_post'
			,'legend' => _t('Reply in the thread')
			,'target_id' => $topic_id
			,'submit_text' => _t("Send")));
	}
?>
