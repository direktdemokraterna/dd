<?php
	$post_info = db_forum::get_post_info($_GET['id']);
	if($post_info['user_id'] == $_SESSION['id']) {
		if (\Logic\forum::is_recent_post($post_info)) {
			$ok = Logic\forum::set_post_content($_GET['id'], $_POST['edit_post_content'], "edit");
			if($ok){
				$_SESSION['report_message'] = "Inlägget har redigerats";
				$redirect = "index.php?type=forum&action=show_posts&topic_id=" . $post_info['topic_id'] . "&page=last";
			}
		}
		else
			\Logic\util::report_error("Inlägg kan bara redigeras i " . EDIT_POST_TIME_WINDOW_IN_MINUTES . " minuter efter att de har skapats");
	}
	else
		\Logic\util::report_error("Du har inte behörighet att redigera det inlägget");
?>