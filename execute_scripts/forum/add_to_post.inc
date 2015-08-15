<?php
	$post_info = db_forum::get_post_info($_GET['id']);

	if($post_info['user_id'] == $_SESSION['id']){ // Allowed to add to post

		$add_to_post_content = forum_helpers::process_post_text($_GET['id'], $_POST['add_to_post_content']);
		$ok = db_forum::add_content_to_post($_GET['id'], "\n\nTILLÄGG:\n" . $add_to_post_content, "add");

		if($ok){
			$_SESSION['report_message'] = "Inlägget har försetts med tillägg.";
			$redirect = "index.php?type=forum&action=show_posts&id=" . $post_info['topic_id'] . "&page=last";
			header("Location: $redirect");
			exit();
		}
	}
	else{
		$_SESSION['report_message'] = "Du har inte behörighet till det inlägget.";
		db_helpers::insert_error_message($_SESSION['id'], $message , "red");
	}
?>