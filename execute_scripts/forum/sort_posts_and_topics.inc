<?
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

?>