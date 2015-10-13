<?php
	$post_info = db_forum::get_post_info($_GET['id']);

	if($post_info['user_id'] == $_SESSION['id']){ // Allowed to add to post
		$text = "\n\nTILLÄGG:\n" . $_POST['edit_post_content'];
		$ok = forum_helpers::update_post_content($_GET['id'], $text, "add");
		if($ok){
			$_SESSION['report_message'] = "Inlägget har försetts med tillägg.";
			$redirect = "index.php?type=forum&action=show_posts&id=" . $post_info['topic_id'] . "&page=last";
		}
	}
	else{
		$_SESSION['report_message'] = "Du har inte behörighet till det inlägget.";
		db_helpers::insert_error_message($_SESSION['id'], $message , "red");
	}
?>