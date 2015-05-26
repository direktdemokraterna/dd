<?php
	if(isset($_POST['delete_topic'])){
		$forum_id = db_forum::get_forum_from_post($_GET['id']);
		$ok = db_forum_admin::delete_topic($_GET['id']);
		if($ok){
			$message = "Ämnet har raderats."; 
			db_helpers::insert_error_message($_SESSION['id'], $message);
			$redirect = "index.php?type=forum&action=show_topics&id=" . $forum_id;
		}
	}
	elseif(isset($_POST['move_topic'])){
		$ok = db_forum_admin::move_topic($_GET['id'], $_POST['forum_id']);
		if($ok){
			$message = "Ämnet har flyttats."; 
			db_helpers::insert_error_message($_SESSION['id'], $message);
			$redirect = "index.php?type=forum&action=show_topics&id=" . $_POST['forum_id'];
		}
	}
	elseif(isset($_POST['edit'])){
		$edited_post_content = forum_helpers::process_post_text($_GET['id'], $_POST['edit_post_content']);
		$edited_post_content .= "\n\nInlägget ändrat av moderator " . date("Y-m-d G:i");
		$ok = db_forum::add_content_to_post($_GET['id'], $edited_post_content, "edit");
		if($ok){
			$message = "Inlägget har redigerats."; 
			db_helpers::insert_error_message($_SESSION['id'], $message);
			$redirect = "index.php?type=forum&action=show_posts&id=" . $_GET['id'];
		}
	}