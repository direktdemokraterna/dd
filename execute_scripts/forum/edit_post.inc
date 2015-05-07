<?
	$post_info = db_forum::get_post_info($_GET['id']);

	if($post_info['user_id'] == $_SESSION['id'] && ($post_info['posted_time'] + 10 * 60) > time()){ // Allowed to edit post

		$edited_post_content = forum_helpers::process_post_text($_GET['id'], $_POST['edit_post_content']);
		$ok = db_forum::add_content_to_post($_GET['id'], $edited_post_content, "edit");

		if($ok){
			$message = "Inlägget har redigerats.";
			db_helpers::insert_error_message($_SESSION['id'], $message);
			$redirect = "index.php?type=forum&action=show_posts&id=" . $post_info['topic_id'] . "&page=last";
			header("Location: $redirect");
			exit();
		}
	}
	elseif($post_info['user_id'] != $_SESSION['id'] && ($post_info['posted_time'] + 10 * 60) > time()){
		$message = "Du har inte behörighet att redigera det inlägget.";
		db_helpers::insert_error_message($_SESSION['id'], $message , "red");
	}
	elseif($post_info['user_id'] == $_SESSION['id'] && ($post_info['posted_time'] + 10 * 60) < time()){
		$message = "Inlägg kan bara redigeras i 10 minuter efter att de postats, den tiden har redan passerat.";
		db_helpers::insert_error_message($_SESSION['id'], $message , "red");
	}
?>