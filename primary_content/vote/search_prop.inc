<?php 
	$search_query = \Logic\util::update_search_query("vote", "prop_search");
	$sort = isset($_GET['sort']) ? $_GET['sort'] : null;
	$page = isset($_GET['page']) ? $_GET['page'] : 1;
	$props = db_prop::search_props($search_query, $_SESSION['id'], $sort, $page);
	if(empty($props)) {
		echo "<p>Inga propositioner med frasen: <b><i>" . $search_query . 
		"</i></b> i text eller rubrik hittades.</p>";
	}
	else {
		echo "<h1>Funna propositioner</h1>";
		$result_count = db_prop::search_props_count($search_query, $_SESSION['id'], $page);
		vote_helpers::make_vote_list_header(null, $result_count);
		$prop_groups = vote_helpers::group_by_constituency($props);
		\View\vote::make_vote_list($prop_groups, "vote", "view_prop", "search_prop");
	} 
?>
