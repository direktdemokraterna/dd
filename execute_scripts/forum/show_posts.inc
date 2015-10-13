<?php
if(isset($_POST['new_post_content'])){
	$forum_id = db_forum::get_forum_from_post_id($_POST['topic_id']);
	$check_access = db_forum::check_access($_SESSION['id'], $forum_id);
	if(!$check_access){
		$_SESSION['report_message'] = "Du har inte behörighet till det forumet.";
		$_SESSION['red_report_message'] = 1;
		$redirect = $_SERVER['REQUEST_URI'];
	}
	else{
		$post_insert_id = db_forum::new_post($_SESSION['id'], $_POST['topic_id']);
		if($post_insert_id){
			$ok = db_forum::add_content_to_post($post_insert_id, $_POST['new_post_content']);
			if($ok){
				$_SESSION['report_message'] = "Inlägg skapat.";
				$redirect = "index.php?type=forum&action=show_posts&id=" . $_POST['topic_id'];
			}
		}
	}
}
?>