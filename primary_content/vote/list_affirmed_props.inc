<h1>Beviljade propositioner</h1>
<?php 
	$status = 'affirmed';
	vote_helpers::make_prop_list_header($status);
	$prop_groups = vote_helpers::get_prop_groups($status);
	\View\vote::make_vote_list($prop_groups, "vote", "view_prop");
?>
