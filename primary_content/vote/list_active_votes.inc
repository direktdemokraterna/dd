<?php 
	_h1(_t("Active votes"));
	$statuses = array('active', 'del_ended', 'continuous');
	$vote_count = db_vote::list_votes_count($_SESSION['id'], $statuses);
	if ($vote_count) {
		$page = isset($_GET['page']) ? $_GET['page'] : 1;
		$vote_groups = vote_helpers::get_vote_groups($page, $statuses);
		$url_without_page = "index.php?type=vote&action=list_active_votes";
		\View\vote::make_vote_list($vote_groups, $page, $vote_count, $url_without_page, "vote", "view_vote");
	}
	else 
		__("There are no active votes in your constituencies");
?>
