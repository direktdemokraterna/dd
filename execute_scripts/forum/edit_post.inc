<?php
	$post_info = db_forum::get_post_info($_GET['id']);

	if($post_info['user_id'] == $_SESSION['id'] && ($post_info['posted_time'] + 10 * 60) > time()){ // Allowed to edit post
		$processed_text = forum_helpers::html_to_bbcode($_POST['edit_post_content']);
		$ok = forum_helpers::update_post_content($_GET['id'], $processed_text, "edit");
		if($ok){
			$_SESSION['report_message'] = "Inlägget har redigerats.";
			$redirect = "index.php?type=forum&action=show_posts&topic_id=" . $post_info['topic_id'] . "&page=last";
		}
	}
	elseif($post_info['user_id'] != $_SESSION['id'] && ($post_info['posted_time'] + 10 * 60) > time()){
		$_SESSION['report_message'] = "Du har inte behörighet att redigera det inlägget.";
		db_error::insert_error_message($_SESSION['id'], $message , "red");
	}
	elseif($post_info['user_id'] == $_SESSION['id'] && ($post_info['posted_time'] + 10 * 60) < time()){
		$_SESSION['report_message'] = "Inlägg kan bara redigeras i 10 minuter efter att de postats, den tiden har redan passerat.";
		db_error::insert_error_message($_SESSION['id'], $message , "red");
	}
?>