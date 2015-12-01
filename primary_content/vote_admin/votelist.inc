<?php 
	_h1(_t("All votes"));
	vote_helpers::make_vote_list_header();
	$vote_groups = vote_helpers::get_vote_groups();
	\View\vote::make_vote_list($vote_groups, "vote_admin", "edit_vote");
?>
