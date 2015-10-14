<h1>Före detta propositioner</h1>
<?php 
	$statuses = array('rejected', 'affirmed');
	vote_helpers::make_prop_list_header($statuses);
	$prop_groups = vote_helpers::get_prop_groups($statuses);
	\View\vote_helper::make_vote_list($prop_groups, "vote", "view_prop");
?>
