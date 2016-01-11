<?php 
	_h1(_t("Forums"));
	$forums = db_forum::list_forums(); 
	$category = "";
	echo '<div class="principal_list">';
	foreach($forums as $row) {
		if($category != $row['cat_name']) {
			echo '<div class="topic_list_top_row" style="text-align: left;"><span class="cat_name">'
				. $row['cat_name'] . '</span></div>';
			$category = $row['cat_name'];
		}
		echo '<div class="topic_list_row" style="text-align: left;">';
		echo '<span class="forum_name">';
		_link($row['forum_name'], 'forum', 'show_topics', 'id=' . $row['forum_id']);
		_br();
		echo '<span class="list_sub_text">' . $row['number_of_topics'] . _t(' topics, ') 
			. $row['number_of_posts'] . _t(' posts') . '</span>';
		echo '</span>';
		echo '<span class="forum_last_post">';
		if(isset($row['last_posted_id'])) {
			$post_info = db_forum::get_post_info($row['last_posted_id']);
			_link($post_info['title'], 'forum', 'show_posts', 'topic_id=' . $post_info['topic_id']);
			_br();
			echo '<span class="list_sub_text">' . _t("by ") 
				. \View\member::link($post_info, 'user_id') . ' ' . general_helpers::show_date($row['last_posted_time']) . '</span>';
		}
		else 
			__("No posts");
		echo '</span>';
		echo '<div style="clear: both;"></div>';
		echo '</div>';
	}
	echo '</div>';
?>