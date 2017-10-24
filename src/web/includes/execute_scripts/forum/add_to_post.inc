<?php
	$post_id = $_GET['id'];
	$post_info = db_forum::get_post_info($post_id);
	if($post_info['user_id'] == $_SESSION['id']){ // Allowed to add to post
		$text = "\n\nTILLÄGG:\n" . $_POST['add_to_post_content'];
		$ok = Logic\forum::set_post_content($post_id, $text, "add");
		if($ok){
			$_SESSION['report_message'] = "Inlägget har blivit uppdaterat";
			$redirect = "index.php?type=forum&action=show_posts&post_id=" . $post_id . "#post" . $post_id;
		}
	}
	else
		\Logic\util::report_error("Du kan inte ändra det inlägget");
?>