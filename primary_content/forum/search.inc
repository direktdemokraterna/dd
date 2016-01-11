<?php 
	$search_query = \Logic\util::update_search_query("forum");
	$page = isset($_GET['page']) ? $_GET['page'] : 1;
	$posts = db_forum::search_posts($search_query, $_SESSION['id'], $page);
	if(empty($posts)) {
		__p(_t("No posts with the phrase: ") . "<b><i>$search_query</i></b>" . _t(" in text or caption were found."));
	}
	else {
		__h1(_t("Found posts"));
		$result_count = db_forum::get_post_count_from_search($search_query, $_SESSION['id']);
		\View\forum::show_posts("index.php?type=forum&action=search", $page, $posts, $result_count);
	} 
?>

