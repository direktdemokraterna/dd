<?php 
	__h1("Alla omröstningar");
	$vote_count = db_vote::list_votes_count($_SESSION['id']);
	if ($vote_count) {
		$vote_groups = \Logic\vote::get_vote_groups();
		\View\vote::make_vote_list($vote_groups, $vote_count, "vote_admin", "edit_vote");		
	}
	else 
		echo "Det finns inga omröstningar i dina valkretsar";
?>
