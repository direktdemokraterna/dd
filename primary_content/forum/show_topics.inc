<?php 
	$forum_info = db_forum::get_forum_info($_GET['id']); 
	if(empty($forum_info)) 
		_p(_t("Forum not found."));
	else {
		echo '<div class="forum_info">';
		_link(_t("Forums"), 'forum', 'show_forums');
		echo '</div>';
		$page = isset($_GET['page']) ? $_GET['page'] : 1;
		_h1($forum_info['title']);
		$topics = db_forum::list_topics($forum_info['id'], $_SESSION['id'], $page);
		if(empty($topics))
			_p(_t("No topics in this forum."));
		else 
			\View\forum::output_topic_list($topics);
		\View\general::output_text_editor(array(
			'name' => 'new_topic'
			,'legend' => _t("Create new thread in this forum")
			,'target_id' => $forum_info['id']
			,'submit_text' => _t("Send")
			,'title_label' => _t("Topic title")
			));
	}
?>

