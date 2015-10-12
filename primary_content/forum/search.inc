<?php 
	$page = isset($_GET['page']) ? $_GET['page'] : 1;
	$posts = db_forum::search_posts($_POST['forum_search_input'], $_SESSION['id'], $page);
	$post_count = db_forum::get_post_count_from_search($_POST['forum_search_input'], $_SESSION['id']);
	if(empty($posts)) {
		echo "<p>Inga inlägg.</p>";
	}
	else {
		echo "<h1>Sök i forum</h1>";
		\View\forum_post_helper::show_posts($page, $posts, $post_count);
	} 
?>

