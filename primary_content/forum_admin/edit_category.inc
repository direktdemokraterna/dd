<?php 
	$cat_info = db_forum_admin::get_category_info($_GET['id']);
	_h1($cat_info['title']);
	_open_form();
	\View\general::make_textfield("title", _t("Name"), 1, $cat_info);
	\View\general::make_textarea("description", _t("Description"), 2, $cat_info);
	_br();
	_submit_and_close(_t("Update"));
	_h2(_t("Forums under this category"));
	$sub_forums = db_forum_admin::list_sub_forums($_GET['id']); 
	if(!empty($sub_forums)) {
		foreach($sub_forums as $row) {
			echo '<div class="topic_list_row" style="text-align: left;">';
			echo '<span class="forum_name">';
			_link($row['forum_name'], 'forum_admin', 'edit_forum', 'id=' . $row['forum_id']);
			_br();
			echo '<span class="list_sub_text">' . $row['number_of_topics'] . _t(' topics, ') 
				. $row['number_of_posts'] . _t(" posts") . '</span>';
			echo '</span>';
			echo '<span class="forum_last_post">';
			if(isset($row['last_posted_id'])) {
				$post_info = db_forum::get_post_info($row['last_posted_id']);
				_link($post_info['title'], 'forum_admin', 'edit_topic', 'id=' 
					. $post_info['topic_id']);
				_br();
				echo '<span class="list_sub_text">' . _t('by ') 
					. \View\member::link($post_info, 'user_id') . ' ' . general_helpers::show_date($row['last_posted_time']) . '</span>';
			}
			else
				__("No posts");
			echo '</span>';
			echo '<div style="clear: both;"></div>';
			echo '</div>';					
		}
	}
	else 
		__("No subforums");
?>