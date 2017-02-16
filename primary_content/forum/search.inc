<?php 
	$search_query = \Logic\util::update_search_query("forum");
	$page = isset($_GET['page']) ? $_GET['page'] : 1;
	$posts = db_forum::search_posts($search_query, $_SESSION['id'], $page);
	if(empty($posts)) {
		__p("Inga inlägg med frasen: " . "<b><i>$search_query</i></b>" . " i rubrik eller brödtext kunde hittas.");
	}
	else {
		__h1("Hittade inlägg");
		$result_count = db_forum::get_post_count_from_search($search_query, $_SESSION['id']);
		\View\forum::show_posts($page, $posts, $result_count, true);
	}
