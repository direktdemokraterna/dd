<?php
	if(isset($_POST['new_topic_title']) && isset($_POST['new_topic_content'])){
		$check_access = db_forum::check_access($_SESSION['id'], $_POST['target_id']);
		if($check_access){
			$topic_insert_id = db_forum::new_topic($_SESSION['id'], $_POST['target_id'], $_POST['new_topic_title']);
			if($topic_insert_id){
				$ok = db_forum::add_content_to_post($topic_insert_id, $_POST['new_topic_content']);
				if($ok){
					$_SESSION['report_message'] = "Tråden har skapats";
					$redirect = "index.php?type=forum&action=show_posts&topic_id=" . $topic_insert_id;
				}
			}
		}
		else
			\Logic\util::report_error("Du kan inte skriva i det här forumet");
	}
?>