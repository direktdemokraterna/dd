<?php 
	$voteinfo = db_vote::get_vote_info($_GET['id']); 
	$user_allowed_to_vote = db_constituency::check_voter_constituency_access($_SESSION['id'], $voteinfo['constituency_id']);
	if($user_allowed_to_vote)
		\View\vote::make_add_alternative_form($voteinfo);
?>