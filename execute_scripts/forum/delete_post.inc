<?
	$post_info = db_forum::get_post_info($_GET['id']);

	if($post_info['user_id'] == $_SESSION['id'] && ($post_info['posted_time'] + 10 * 60) > time()){ // Allowed to delete post
		$ok = db_forum::delete_post($_GET['id']);

		if($ok){
			$message = "Inlägget har raderats.";
			db_helpers::insert_error_message($_SESSION['id'], $message);
			$redirect = "index.php?type=forum&action=show_posts&id=" . $post_info['topic_id'] . "&page=last";
			header("Location: $redirect");
			exit();
		}
	}
	elseif($post_info['user_id'] != $_SESSION['id'] && ($post_info['posted_time'] + 10 * 60) > time()){
		$message = "Du har inte behörighet att radera det inlägget.";
		db_helpers::insert_error_message($_SESSION['id'], $message , "red");
	}
	elseif($post_info['user_id'] == $_SESSION['id'] && ($post_info['posted_time'] + 10 * 60) < time()){
		$message = "Inlägg kan bara raderas i 10 minuter efter att de postats, den tiden har redan passerats.";
		db_helpers::insert_error_message($_SESSION['id'], $message , "red");
	}
?>