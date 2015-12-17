<?php
	$post_info = db_forum::get_post_info($_GET['id']);
	$is_recent_post = \Logic\forum::is_recent_post($post_info);
	$is_user_author = $post_info['user_id'] == $_SESSION['id'];
	if(!$is_user_author)
		\Logic\util::report_error(_t("You don't have permission to delete that post.");
	elseif(!$is_recent_post)
		\Logic\util::report_error(_t("Post can only be deleted within 10 minutes after they have been posted, that time has already passed."));
	else {
		$ok = db_forum::delete_post($_GET['id']);
		if($ok){
			$_SESSION['report_message'] = _t("Post deleted.");
			$redirect = "index.php?type=forum&action=show_posts&topic_id=" . $post_info['topic_id'] . "&page=last";
		}
	}
?>