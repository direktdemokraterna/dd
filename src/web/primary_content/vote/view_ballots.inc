<?php
	$voteinfo = db_vote::get_vote_info($_GET['id']); 
	$ballots = db_vote::get_ballots($_GET['id']);
	__h1("Alla röster i omröstningen: " . $voteinfo['title']);
	\View\vote::list_ballots($voteinfo['type'], $ballots);
?>
