<h1>Avslutade omröstningar</h1>
<?php 
	$statuses = array('ended', 'finished');
	vote_helpers::make_vote_list_header($statuses);
	$vote_groups = vote_helpers::get_vote_groups($statuses);
	\View\vote::make_vote_list($vote_groups, "vote", "view_vote");
?>
