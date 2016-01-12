<?php 
	__h1(_t("Closed votes", array('class' => 'adj')));
	$statuses = array('ended', 'finished');
	$vote_count = db_vote::list_votes_count($_SESSION['id'], $statuses);
	if ($vote_count) {
		$vote_groups = vote_helpers::get_vote_groups($statuses);
		$url_without_page = "index.php?type=vote&action=list_old_votes";
		\View\vote::make_vote_list($vote_groups, $vote_count, $url_without_page, "vote", "view_vote");
	}
	else 
		__t("There are no closed votes in your constituencies");
?>
