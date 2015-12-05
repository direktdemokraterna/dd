<?php 
	_h1(_t("Active propositions"));
	$status = 'pending';
	vote_helpers::make_prop_list_header($status);
	$prop_groups = vote_helpers::get_prop_groups($status);
	\View\vote::make_vote_list($prop_groups, "vote", "view_prop");
?>
