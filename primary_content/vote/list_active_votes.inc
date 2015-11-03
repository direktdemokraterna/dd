<h1>Pågående omröstningar</h1>
<?php 
	$statuses = array('active', 'del_ended', 'continuous');
	vote_helpers::make_vote_list_header($statuses);
	$vote_groups = vote_helpers::get_vote_groups($statuses);
	\View\vote::make_vote_list($vote_groups, "vote", "view_vote");
?>
