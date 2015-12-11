<?php
	if(isset($_GET['page'])) $page = $_GET['page']; else $page = 1;
	$i = 0;
	$user_full_name = db_user::get_user_full_name($_GET['id']);
	_h1(_t("Thread starts by ") . $user_full_name);
	$topics = db_forum::get_topics_by_user($_GET['id'], $_SESSION['id'], $page);
	if(empty($topics))
		_p(_t("No thread starts."));
	else 
		\View\forum::output_topic_list($topics);
?>