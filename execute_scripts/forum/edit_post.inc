<?php
	$post_info = db_forum::get_post_info($_GET['id']);

	if($post_info['user_id'] == $_SESSION['id'] && ($post_info['posted_time'] + 10 * 60) > time()){ // Allowed to edit post
		$ok = forum_helpers::update_post_content($_GET['id'], $_POST['edit_post_content'], "edit");
		if($ok){
			$_SESSION['report_message'] = _t("The post has been edited.");
			$redirect = "index.php?type=forum&action=show_posts&topic_id=" . $post_info['topic_id'] . "&page=last";
		}
	}
	elseif($post_info['user_id'] != $_SESSION['id'] && ($post_info['posted_time'] + 10 * 60) > time()){
		$_SESSION['report_message'] = _t("You don't have permission to edit that post.");
		db_error::insert_error_message($_SESSION['id'], $message , "red");
	}
	elseif($post_info['user_id'] == $_SESSION['id'] && ($post_info['posted_time'] + 10 * 60) < time()){
		$_SESSION['report_message'] = _t("Post can only be edited within 10 minutes after they have been posted, that time has already passed.");
		db_error::insert_error_message($_SESSION['id'], $message , "red");
	}
?>