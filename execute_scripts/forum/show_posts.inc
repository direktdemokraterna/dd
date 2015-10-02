<?php
// sort posts and topics
	if(isset($_GET['id'])){
		$topic_id = db_forum::get_topic($_GET['id']);

		if($topic_id != $_GET['id']){ // $_GET['id'] is not a topic, calculating topic and relevant page
			$number_of_posts_in_topic = db_forum::get_number_of_posts($topic_id);
			if($number_of_posts_in_topic > POSTS_PER_PAGE){
				$posts_before_this_post = db_forum::count_posts_before_post_id($topic_id, $_GET['id']);
				$page = ceil(($posts_before_this_post+1) / POSTS_PER_PAGE);
				$redirect = "index.php?type=forum&action=show_posts&id=" . $topic_id . "&page=" . $page . "#post" . $_GET['id'];
			}
			else{
				$redirect = "index.php?type=forum&action=show_posts&id=" . $topic_id . "#post" . $_GET['id'];
			}
			header("Location: $redirect");
			exit();
		}

		if(isset($_GET['page'])){
			if($_GET['page'] == "last"){
				$number_of_posts_in_topic = db_forum::get_number_of_posts($topic_id);
				$page = ceil($number_of_posts_in_topic / POSTS_PER_PAGE);
				$redirect = "index.php?type=forum&action=show_posts&id=" . $topic_id . "&page=" . $page;
				header("Location: $redirect");
				exit();
			}
		}
	}

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
				$new_post_content = forum_helpers::process_post_text($post_insert_id, $_POST['new_post_content']);
				db_forum::add_content_to_post($post_insert_id, $new_post_content);

				$_SESSION['report_message'] = "Inlägg skapat.";
				$redirect = "index.php?type=forum&action=show_posts&id=" . $_POST['topic_id'];
			}
		}
	}
?>