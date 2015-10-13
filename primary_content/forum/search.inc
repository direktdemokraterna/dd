<?php 
	$page = isset($_GET['page']) ? $_GET['page'] : 1;
	$search_query = isset($_POST['forum_search_input']) 
		? $_POST['forum_search_input']
		: (isset($_SESSION['forum_search_input']) ? $_SESSION['forum_search_input'] : '');
	$_SESSION['forum_search_input'] = $search_query;
	
	$posts = db_forum::search_posts($search_query, $_SESSION['id'], $page);
	$post_count = db_forum::get_post_count_from_search($search_query, $_SESSION['id']);
	if(empty($posts)) {
		echo "<p>Inga inlägg.</p>";
	}
	else {
		echo "<h1>Sök i forum</h1>";
		\View\forum_post_helper::show_posts("index.php?type=forum&action=search", $page, $posts, $post_count);
	} 
?>

