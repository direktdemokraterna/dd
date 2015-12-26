<?php 
	$search_query = \Logic\util::update_search_query("workgroup");
	$page = isset($_GET['page']) ? $_GET['page'] : 1;
	$result = db_workgroup::search_workgroups($search_query, $page);
	if(empty($result)) {
		_p(_t("No active workgroups with the phrase: ") . "<b><i>$search_query</i></b>" . _t(" in description or title were found."));
	}
	else {
		_h1(_t("Found workgroups"));
		$result_count = db_workgroup::get_workgroup_count_from_search($search_query);
		\View\workgroup::list_workgroups($result);
		//\View\workgroup::show_posts("index.php?type=forum&action=search", $page, $posts, $result_count);
	} 
?>

