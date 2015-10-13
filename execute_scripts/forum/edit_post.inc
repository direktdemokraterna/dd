<?php
	$post_info = db_forum::get_post_info($_GET['id']);

	if($post_info['user_id'] == $_SESSION['id'] && ($post_info['posted_time'] + 10 * 60) > time()){ // Allowed to edit post
		$ok = forum_helpers::update_post_content($_GET['id'], $_POST['edit_post_content'], "edit");
		if($ok){
			$_SESSION['report_message'] = "Inlägget har redigerats.";
			$redirect = "index.php?type=forum&action=show_posts&id=" . $post_info['topic_id'] . "&page=last";
		}
	}
	elseif($post_info['user_id'] != $_SESSION['id'] && ($post_info['posted_time'] + 10 * 60) > time()){
		$_SESSION['report_message'] = "Du har inte behörighet att redigera det inlägget.";
		db_helpers::insert_error_message($_SESSION['id'], $message , "red");
	}
	elseif($post_info['user_id'] == $_SESSION['id'] && ($post_info['posted_time'] + 10 * 60) < time()){
		$_SESSION['report_message'] = "Inlägg kan bara redigeras i 10 minuter efter att de postats, den tiden har redan passerat.";
		db_helpers::insert_error_message($_SESSION['id'], $message , "red");
	}
?>