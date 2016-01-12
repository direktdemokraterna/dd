<?php 
	$search_query = \Logic\util::update_search_query("vote", "search_prop");
	$sort = isset($_GET['sort']) ? $_GET['sort'] : null;
	$page = isset($_GET['page']) ? $_GET['page'] : 1;
	$props = db_prop::search_props($search_query, $_SESSION['id'], $sort, $page);
	__h1(_t("Found propositions"));
	if(empty($props)) {
		__p(_t("No propositions with the phrase: ") . "<b><i>$search_query</i></b>" . _t(" in text or caption were found."));
	}
	else {
		$result_count = db_prop::search_props_count($search_query, $_SESSION['id'], $page);
		$prop_groups = \Logic\vote::group_by_constituency($props);
		\View\vote::make_proposition_list($prop_groups, $result_count, "vote", "view_prop", "search_prop");
	} 
?>
