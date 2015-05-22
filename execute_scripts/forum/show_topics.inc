<?php
	if(isset($_POST['new_topic_title']) && isset($_POST['new_topic_content'])){
		$check_access = db_forum::check_access($_SESSION['id'], $_POST['forum_id']);
		if(!$check_access){
			$message = "Du har inte behörighet till det forumet.";
			db_helpers::insert_error_message($_SESSION['id'], $message, "red");
			$redirect = $_SERVER['REQUEST_URI'];
		}
		else{
			$topic_insert_id = db_forum::new_topic($_SESSION['id'], $_POST['forum_id'], $_POST['new_topic_title']);
			if($topic_insert_id){
				$new_topic_content = forum_helpers::process_post_text($topic_insert_id, $_POST['new_topic_content']);
				db_forum::add_content_to_post($topic_insert_id, $new_topic_content);

				$message = "Tråden skapad.";
				db_helpers::insert_error_message($_SESSION['id'], $message);
				$redirect = "index.php?type=forum&action=show_posts&id=" . $topic_insert_id;
			}
		}

	}
?>