<?php
	$post_info = db_forum::get_post_info($_GET['id']);
	$is_within_edit_time_window = time() < $post_info['posted_time'] + EDIT_POST_TIME_WINDOW_IN_MINUTES * 60;
	if($post_info['user_id'] == $_SESSION['id']) {
		if ($is_within_edit_time_window) {
			$ok = forum_helpers::update_post_content($_GET['id'], $_POST['edit_post_content'], "edit");
			if($ok){
				$_SESSION['report_message'] = _t("The post has been edited.");
				$redirect = "index.php?type=forum&action=show_posts&topic_id=" . $post_info['topic_id'] . "&page=last";
			}
		}
		else
			\Logic\util::report_error(_t("Post can only be edited within " . EDIT_POST_TIME_WINDOW_IN_MINUTES . " minute after they have been posted, that time has already passed."));
	}
	else
		\Logic\util::report_error(_t("You don't have permission to edit that post."));
?>