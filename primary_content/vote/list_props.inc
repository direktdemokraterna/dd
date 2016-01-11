<?php 
	__h1(_t("Active propositions"));
	$status = 'pending';
	$prop_count = db_prop::list_props_count($status, $_SESSION['id']);
	if ($prop_count) {
		$page = isset($_GET['page']) ? $_GET['page'] : 1;
		$prop_groups = vote_helpers::get_prop_groups($status);
		$url_without_page = "index.php?type=vote&action=list_props";
		\View\vote::make_proposition_list($prop_groups, $page, $prop_count, $url_without_page, "vote", "view_prop");
	}
	else 
		__t("There are no active propositions in your constituencies");
?>
