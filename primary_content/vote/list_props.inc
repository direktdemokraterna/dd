<h1>Lagda propositioner</h1>
<?php 
	$statuses = array('pending');
	vote_helpers::make_prop_list_header($statuses);
	$prop_groups = vote_helpers::get_prop_groups($statuses);
	\View\vote::make_vote_list($prop_groups, "vote", "view_prop");
?>
