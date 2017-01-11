<?php 
	$forum_info = db_forum::get_forum_info($_GET['id']); 
	if(empty($forum_info)) 
		__p(_t("Forum not found."));
	else {
		$forum_id = $forum_info['id'];
		$page = isset($_GET['page']) ? $_GET['page'] : 1;
		__h1($forum_info['title']);
		echo '<div class="forum_info">';
		__link(_t("Forums"), 'forum', 'show_forums');
		echo '<a href="#new_topic_form"><span class="btn-blue">Starta ny tråd</span></a></div>';
		$topics = db_forum::list_topics($forum_id, $_SESSION['id'], $page);
		if(empty($topics))
			__p(_t("No topics in this forum."));
		else {
			$topic_count = db_forum::get_topic_count($forum_id);
			\View\forum::output_topic_list($topics, $page, $topic_count);
		}
		\View\controls::output_text_editor(array(
			'name' => 'new_topic'
			,'legend' => _t("Create new thread in this forum")
			,'target_id' => $forum_info['id']
			,'submit_text' => _t("Send")
			,'title_label' => _t("Topic title")
			));
	}
?>

