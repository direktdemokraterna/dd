<?php
	if(isset($_POST['delete'])){
		$topic_id = db_forum::get_topic($_GET['id']);
		$ok = db_forum_admin::delete_post($_GET['id']);
		if($ok){
			$_SESSION['report_message'] = "Inl�gget har raderats."; 
			$redirect = "index.php?type=forum&action=show_posts&id=" . $topic_id;
		}
	}
	elseif(isset($_POST['move'])){
		$ok = db_forum_admin::move_post($_GET['id'], $_POST['topic_id']);
		if($ok){
			$_SESSION['report_message'] = "Inl�gget har flyttats."; 
			$redirect = "index.php?type=forum&action=show_posts&id=" . $_POST['topic_id'];
		}
	}
	elseif(isset($_POST['create_new'])){
		$ok = db_forum_admin::create_topic_from_post($_GET['id'], $_POST['topic_title']);
		if($ok){
			$_SESSION['report_message'] = "En ny tr�d har skapats fr�n inl�gget."; 
			$redirect = "index.php?type=forum&action=show_posts&id=" . $_GET['id'];
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