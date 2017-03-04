<?php 
	$voteinfo = db_vote::get_vote_info($_GET['id']); 
	__h1("Ändra omröstning: " . $voteinfo['title']);
	__open_form();
	__hidden("vote_id", $voteinfo['id']);
	\View\vote::make_vote_type_selector($voteinfo['type']);
	\View\vote::make_constituency_selector($voteinfo['constituency_id'], $_SESSION['id'], 2); 
	__textfield("title", "Titel", 3, $voteinfo); 
	__textarea("description", "Beskrivning", 4, $voteinfo);
	\View\vote::output_vote_status($voteinfo['status']); 
	__textfield("forum_topic_id", "Forumtråd", 5, $voteinfo); 
	__br();
	__label("Omröstningen avslutas", "year");
	\View\vote::make_vote_end_time_select($voteinfo['timestamp_ended']); 
	__br();
	__label("Delegatröstning avslutas", "delegate_year");
	\View\vote::make_vote_end_time_select($voteinfo['timestamp_delegate_ended'], 'delegate_');
	__br();
	__submit_and_close("Uppdatera");
?>
