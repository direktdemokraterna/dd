<?php
	if(isset($_POST['report_post_argument'])){
		$forum_id = db_forum::get_forum_from_post_id($_POST['post_id']);
		$check_access = db_forum::check_access($_SESSION['id'], $forum_id);
		if($check_access){
			$report_insert_id = db_forum::new_report($_POST['post_id'], $_SESSION['id'], general_helpers::clean($_POST['report_post_argument']));
			if($report_insert_id){
				$_SESSION['report_message'] = "Rapporten har mottagits";
				$redirect = "index.php?type=forum&action=show_posts&post_id=" . $_POST['post_id'];
			}
		}
		else
			\Logic\util::report_error("Du har inte tillgång till det forumet");
	}
?>