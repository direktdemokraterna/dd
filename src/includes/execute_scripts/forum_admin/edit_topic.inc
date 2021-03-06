<?php
	if(isset($_POST['delete_topic'])){
		$forum_id = db_forum::get_forum_from_post($_GET['id']);
		$ok = db_forum_admin::delete_topic($_GET['id']);
		if($ok){
			$_SESSION['report_message'] = "Tråden har raderats"; 
			$redirect = "index.php?type=forum&action=show_topics&id=" . $forum_id;
		}
	}
	elseif(isset($_POST['move_topic'])){
		$ok = db_forum_admin::move_topic($_GET['id'], $_POST['forum_id']);
		if($ok){
			$_SESSION['report_message'] = "Tråden har flyttats"; 
			$redirect = "index.php?type=forum&action=show_topics&id=" . $_POST['forum_id'];
		}
	}
	elseif(isset($_POST['edit'])){
		$text = $_POST['edit_post_content'] . "\n\n" . "Tråden har ändrats av moderator" . date("Y-m-d G:i");
		$ok = Logic\forum::set_post_content($_GET['id'], $text, "edit"); 
		if($ok){
			$_SESSION['report_message'] = "Inlägget har ändrats";
			$redirect = "index.php?type=forum&action=show_posts&post_id=" . $_GET['id'];
		}
	}
?>