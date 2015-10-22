<?php
	if(isset($_POST['new_topic_title']) && isset($_POST['new_topic_content'])){
		$check_access = db_forum::check_access($_SESSION['id'], $_POST['forum_id']);
		if(!$check_access){
			$_SESSION['report_message'] = "Du har inte behörighet till det forumet.";
			$_SESSION['red_report_message'] = 1;
			$redirect = $_SERVER['REQUEST_URI'];
		}
		else{
			$topic_insert_id = db_forum::new_topic($_SESSION['id'], $_POST['forum_id'], $_POST['new_topic_title']);
			if($topic_insert_id){
				$ok = db_forum::add_content_to_post($topic_insert_id, $_POST['new_topic_content']);
				if($ok){
					$_SESSION['report_message'] = "Tråden skapad.";
					$redirect = "index.php?type=forum&action=show_posts&topic_id=" . $topic_insert_id;
				}
			}
		}
	}
?>