<?php
	if(isset($_POST['delete'])){
		$topic_id = db_forum::get_topic($_GET['id']);
		$ok = db_forum_admin::delete_post($_GET['id']);
		if($ok){
			$_SESSION['report_message'] = "Inlägget har raderats."; 
			$redirect = "index.php?type=forum&action=show_posts&id=" . $topic_id;
		}
	}
	elseif(isset($_POST['move'])){
		$ok = db_forum_admin::move_post($_GET['id'], $_POST['topic_id']);
		if($ok){
			$_SESSION['report_message'] = "Inlägget har flyttats."; 
			$redirect = "index.php?type=forum&action=show_posts&id=" . $_POST['topic_id'];
		}
	}
	elseif(isset($_POST['create_new'])){
		$ok = db_forum_admin::create_topic_from_post($_GET['id'], $_POST['topic_title']);
		if($ok){
			$_SESSION['report_message'] = "En ny tråd har skapats från inlägget."; 
			$redirect = "index.php?type=forum&action=show_posts&id=" . $_GET['id'];
		}
	}
	elseif(isset($_POST['edit'])){
		$text = $_POST['edit_post_content'] . "\n\nInlägget ändrat av moderator " . date("Y-m-d G:i");
		$ok = forum_helpers::update_post_content($_GET['id'], $text, "edit");
		if($ok){
			$_SESSION['report_message'] = "Inlägget har redigerats."; 
			$redirect = "index.php?type=forum&action=show_posts&id=" . $_GET['id'];
		}
	}
?>