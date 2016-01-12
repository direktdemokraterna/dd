<?php 
	$sort = isset($_GET['sort']) ? $_GET['sort'] : null;
	$page = isset($_GET['page']) ? $_GET['page'] : 1;
	$search_query = \Logic\util::update_search_query("vote");
	$votes = db_vote::search_votes($search_query, $_SESSION['id'], $sort, $page);
	__h1(_t("Found votes"));
	if(empty($votes)) {
		__p(_t("No votes with the phrase: ") . "<b><i>$search_query</i></b>" . _t(" in text or caption were found."));
	}
	else {
		$result_count = db_vote::search_votes_count($search_query, $_SESSION['id']);
		$vote_groups = \Logic\vote::group_by_constituency($votes);
		$url_without_page = "index.php?type=vote&action=search";
		\View\vote::make_vote_list($vote_groups, $result_count, $url_without_page, "vote", "view_vote", "search");
	} 
?>
