<?php
	if(isset($_POST['report_post_argument'])){
		$forum_id = db_forum::get_forum_from_post_id($_POST['post_id']);
		$check_access = db_forum::check_access($_SESSION['id'], $forum_id);
		if(!$check_access){
			$_SESSION['report_message'] = "Du har inte behörighet till det forumet.";
			$_SESSION['red_report_message'] = 1;
			$redirect = $_SERVER['REQUEST_URI'];
		}
		else{
			$report_insert_id = db_forum::new_report($_POST['post_id'], $_SESSION['id'], htmlspecialchars($_POST['report_post_argument']));
			if($report_insert_id){
				$_SESSION['report_message'] = "Anmälan är mottagen.";
				$redirect = "index.php?type=forum&action=show_posts&id=" . $_POST['topic_id'];
			}
		}
	}
?>