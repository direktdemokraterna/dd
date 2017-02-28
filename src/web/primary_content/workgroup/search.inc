<?php 
	$search_query = \Logic\util::update_search_query("workgroup");
	$page = isset($_GET['page']) ? $_GET['page'] : 1;
	$result = db_workgroup::search_workgroups($search_query, $page);
	if(empty($result)) {
		__p("Inga aktiva arbetsgrupper med sökordet: " . "<b><i>$search_query</i></b>" . " i namn eller beskrivning.");
	}
	else {
		__h1("Funna arbetsgrupper");
		$result_count = db_workgroup::get_workgroup_count_from_search($search_query);
		\View\workgroup::list_workgroups($result);
	} 
?>

