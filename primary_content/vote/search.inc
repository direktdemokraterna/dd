<?php 
	$sort = isset($_GET['sort']) ? $_GET['sort'] : null;
	$page = isset($_GET['page']) ? $_GET['page'] : 1;
	$search_query = \Logic\util::update_search_query("vote");
	$votes = db_vote::search_votes($search_query, $_SESSION['id'], $sort, $page);
	if(empty($votes)) {
		echo "<p>Inga omröstningar med frasen: <b><i>" . $search_query . 
		"</i></b> i text eller rubrik hittades.</p>";
	}
	else {
		echo "<h1>Funna omröstningar</h1>";
		$result_count = db_vote::search_votes_count($search_query, $_SESSION['id'], $page);
		vote_helpers::make_vote_list_header(null, $result_count);
		$vote_groups = vote_helpers::group_by_constituency($votes);
		\View\vote::make_vote_list($vote_groups, "vote", "view_vote", "search");
	} 
?>
