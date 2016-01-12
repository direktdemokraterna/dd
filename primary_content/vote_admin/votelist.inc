<?php 
	__h1(_t("All votes"));
	$vote_count = db_vote::list_votes_count($_SESSION['id']);
	if ($vote_count) {
		$vote_groups = \Logic\vote::get_vote_groups();
		$url_without_page = "index.php?type=vote_admin&action=votelist";
		\View\vote::make_vote_list($vote_groups, $vote_count, $url_without_page, "vote_admin", "edit_vote");		
	}
	else 
		__t("There are no votes in your constituencies");
?>
