<?php 
	$search_query = isset($_POST['vote_search_input']) 
		? $_POST['vote_search_input']
		: (isset($_SESSION['vote_search_input']) ? $_SESSION['vote_search_input'] : '');
	$_SESSION['vote_search_input'] = $search_query;

	$sort = isset($_GET['sort']) ? $_GET['sort'] : null;
	$page = isset($_GET['page']) ? $_GET['page'] : 1;
	$votes = db_vote::search_votes($search_query, $_SESSION['id'], $sort, $page);
	if(empty($votes) && empty($props)) {
		echo "<p>Inga omröstningar hittades.</p>";
	}
	else {
		echo "<h1>Funna omröstningar</h1>";
		$result_count = db_vote::search_votes_count($search_query, $_SESSION['id'], $page);
		vote_helpers::make_vote_list_header(null, $result_count);
		$vote_groups = vote_helpers::group_by_constituency($votes);
		\View\vote_helper::make_vote_list($vote_groups, "vote", "view_vote");
	} 
?>
