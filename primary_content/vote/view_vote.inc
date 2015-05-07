<?php 
	$voteinfo = db_vote::get_vote_info($_GET['id']); 
	$user_allowed_to_vote = db_constituency::check_user_constituency_access($_SESSION['id'], $voteinfo['constituency_id']);

	if($voteinfo['type'] == "yes-no"){
		require(dirname(__FILE__)."/vote_types/yes-no.inc");
	}
	elseif($voteinfo['type'] == "prio-vote" || $voteinfo['type'] == "candidate-election"){
		require(dirname(__FILE__)."/vote_types/prio-vote.inc");
	}
	elseif($voteinfo['type'] == "median"){
		require(dirname(__FILE__)."/vote_types/median.inc");
	}
	elseif($voteinfo['type'] == "budget"){
		require(dirname(__FILE__)."/vote_types/budget.inc");
	}
?>