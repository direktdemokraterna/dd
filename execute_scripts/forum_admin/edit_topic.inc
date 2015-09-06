<?php
	if(isset($_POST['delete_topic'])){
		$forum_id = db_forum::get_forum_from_post($_GET['id']);
		$ok = db_forum_admin::delete_topic($_GET['id']);
		if($ok){
			$_SESSION['report_message'] = "�mnet har raderats."; 
			$redirect = "index.php?type=forum&action=show_topics&id=" . $forum_id;
		}
	}
	elseif(isset($_POST['move_topic'])){
		$ok = db_forum_admin::move_topic($_GET['id'], $_POST['forum_id']);
		if($ok){
			$_SESSION['report_message'] = "�mnet har flyttats."; 
			$redirect = "index.php?type=forum&action=show_topics&id=" . $_POST['forum_id'];
		}
	}
	elseif(isset($_POST['edit'])){
		$edited_post_content = forum_helpers::process_post_text($_GET['id'], $_POST['edit_post_content']);
		$edited_post_content .= "\n\nInl�gget �ndrat av moderator " . date("Y-m-d G:i");
		$ok = db_forum::add_content_to_post($_GET['id'], $edited_post_content, "edit");
		if($ok){
			$_SESSION['report_message'] = "Inl�gget har redigerats."; 
			$redirect = "index.php?type=forum&action=show_posts&id=" . $_GET['id'];
		}
	}