<?php 
	_h1(_t("Active votes"));
	$statuses = array('active', 'del_ended', 'continuous');
	vote_helpers::make_vote_list_header($statuses);
	$vote_groups = vote_helpers::get_vote_groups($statuses);
	\View\vote::make_vote_list($vote_groups, "vote", "view_vote", "search");
?>
