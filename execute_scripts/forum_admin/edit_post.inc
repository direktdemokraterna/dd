<?php
	if(isset($_POST['delete'])){
		$topic_id = db_forum::get_topic($_GET['id']);
		$ok = db_forum_admin::delete_post($_GET['id']);
		if($ok){
			$message = "Inlägget har raderats."; 
			db_helpers::insert_error_message($_SESSION['id'], $message);
			$redirect = "index.php?type=forum&action=show_posts&id=" . $topic_id;
		}
	}
	elseif(isset($_POST['move'])){
		$ok = db_forum_admin::move_post($_GET['id'], $_POST['topic_id']);
		if($ok){
			$message = "Inlägget har flyttats."; 
			db_helpers::insert_error_message($_SESSION['id'], $message);
			$redirect = "index.php?type=forum&action=show_posts&id=" . $_POST['topic_id'];
		}
	}
	elseif(isset($_POST['create_new'])){
		$ok = db_forum_admin::create_topic_from_post($_GET['id'], $_POST['topic_title']);
		if($ok){
			$message = "En ny tråd har skapats från inlägget."; 
			db_helpers::insert_error_message($_SESSION['id'], $message);
			$redirect = "index.php?type=forum&action=show_posts&id=" . $_GET['id'];
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