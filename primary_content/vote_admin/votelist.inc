<?php 
	_h1(_t("All votes"));
	$vote_count = db_vote::list_votes_count($_SESSION['id']);
	if ($vote_count) {
		$page = isset($_GET['page']) ? $_GET['page'] : 1;
		$vote_groups = vote_helpers::get_vote_groups($page);
		$url_without_page = "index.php?type=vote_admin&action=votelist";
		\View\vote::make_vote_list($vote_groups, $page, $vote_count, $url_without_page, "vote_admin", "edit_vote");		
	}
	else 
		__("There are no votes in your constituencies");
?>
