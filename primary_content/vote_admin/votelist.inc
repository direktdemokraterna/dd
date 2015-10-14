<h1>Alla omröstningar</h1>
<?php 
	vote_helpers::make_vote_list_header();
	$vote_groups = vote_helpers::get_vote_groups();
	\View\vote_helpers::make_vote_list($vote_groups, "vote_admin", "edit_vote");
?>
