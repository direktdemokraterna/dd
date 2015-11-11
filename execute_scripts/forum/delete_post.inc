<?php
	$post_info = db_forum::get_post_info($_GET['id']);
	$is_post_new = ($post_info['posted_time'] + 10 * 60) > time();
	$is_user_author = $post_info['user_id'] == $_SESSION['id'];
	if(!$is_user_author)
		\Logic\util::report_error("Du har inte behörighet att radera det inlägget.");
	elseif(!$is_post_new)
		\Logic\util::report_error("Inlägg kan bara raderas i 10 minuter efter att de postats, den tiden har redan passerats.");
	else {
		$ok = db_forum::delete_post($_GET['id']);
		if($ok){
			$_SESSION['report_message'] = "Inlägget har raderats.";
			$redirect = "index.php?type=forum&action=show_posts&topic_id=" . $post_info['topic_id'] . "&page=last";
		}
	}
?>