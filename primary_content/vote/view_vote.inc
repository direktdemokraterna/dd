<?php 
	$voteinfo = db_vote::get_vote_info($_GET['id']); 
	$user_allowed_to_vote = db_constituency::check_voter_constituency_access($_SESSION['id'], $voteinfo['constituency_id']);
	$number_of_delegate_ballots = db_delegate::number_of_delegate_ballots_for_vote($voteinfo['id']);
	$all_ballots = db_vote::get_ballots($voteinfo['id']);
	$ballots_to_count = array_filter($all_ballots, 
		function($ballot) {return $ballot['user_code'];});
	$ballots_to_count_json = \View\general::db_result_to_json($ballots_to_count);
	$delegate_ballots = array_filter($all_ballots, 
		function($ballot) {return $ballot['voter_id'];});
	$delegate_ballots_json = \View\general::db_result_to_json($delegate_ballots);
	if($_SESSION['delegate_id']){
		$delegate_constituency_access = db_constituency::check_voter_constituency_access($_SESSION['delegate_id'], $voteinfo['constituency_id']);
		$delegate_ballot = db_delegate::get_ballot_for_vote($voteinfo['id'], $_SESSION['delegate_id']);
	}
?>

<script>
	var user_id = <?php echo json_encode($_SESSION['id']); ?>;
	var vote_id = <?php echo json_encode($voteinfo['id']); ?>;
	var constituency_id = <?php echo json_encode($voteinfo['constituency_id']); ?>;
	var ballots_to_count = <?php echo $ballots_to_count_json; ?>;
	var delegate_ballots = <?php echo $delegate_ballots_json; ?>;
	var acting_as_delegate = <?php if(!empty($delegate_constituency_access)) echo "true"; else echo "false"; ?>;
</script>

<?php 
	if (isset($_GET['from_action']))
		\View\controls::output_search_back_link();
	\View\vote::output_vote_header($voteinfo);
	\View\general::open_div("vote_result_box");
	\View\vote::output_vote_result_with_header($voteinfo, $ballots_to_count);
	__br();
	if($voteinfo['status'] == "ended" || $voteinfo['status'] == "finished")
		echo _t("The vote is finished. It finished ") 
		. general_helpers::show_date($voteinfo['timestamp_ended']) . '.';
	elseif($voteinfo['status'] == "del_ended")
		echo _t("The vote finishes ") . general_helpers::show_date($voteinfo['timestamp_ended']) 
			. _t('. For delegates the possibility to vote closed ') 
			. general_helpers::show_date($voteinfo['timestamp_delegate_ended']) . '.';
	elseif($voteinfo['status'] == "continuous")
		__t("This is a continous vote and it continues until it is ended through a new yes/no vote.");
	else
		echo _t("The vote finishes ") . general_helpers::show_date($voteinfo['timestamp_ended'])
			. _t(". For delegates the possibility to vote closes ") . general_helpers::show_date($voteinfo['timestamp_delegate_ended']) . ".";
	\View\general::close_div();

	\View\general::open_div("vote_result_box", "user_vote_box");
	if($_SESSION['delegate_id']) {
		if(empty($delegate_ballot))
			__t("You have not yet voted in this vote as delegate.");
		else {
			if(isset($delegate_ballot['delegate_id']))
				__t("You as delegate have let your delegate vote in this vote.");
			else
				__t("You as delegate have cast your own ballot in this vote.");
			__br();
			__t("Your ballot:");
			__br();
			echo \View\vote::get_ballot_content($voteinfo['type'], $delegate_ballot['ballot']);
		}
	}
	else __t("No ballot has been cast in your name in this vote.");
	\View\general::close_div();
	echo '<p>';
	__strong(_t("Constituency: ") . $voteinfo['constituency_name']);
	__br();
	if($voteinfo['proposition_created']) {
		__strong(_t("Proposition created: "));
		echo general_helpers::show_date($voteinfo['proposition_created']);
		__br();
		__strong(_t("Proposition created by: "));
		__link($voteinfo['user_full_name'], 'member', 'view', 'id=' . $voteinfo['user_id']);
	}
  	else 
		__strong(_t("Vote ", array('class' => 'noun')) . _t("created by administrator", array('class' => 'adj')));
	__br();
	__strong(_t("Vote started: "));
	echo general_helpers::show_date($voteinfo['timestamp_created']);
	__br();	
	if($voteinfo['status'] == "continuous"){
		__strong(_t("The vote is continous."));
		__br();
	}
	else {
		__info(_t("Delegate voting closes"), general_helpers::show_date($voteinfo['timestamp_delegate_ended']));
		__info(_t("Vote closes"), general_helpers::show_date($voteinfo['timestamp_ended']));
  	}
	__info(_t("Number of cast ballots"), $voteinfo['number_of_ballots']);
	__info(_t("Whereof personally cast ballots"), $voteinfo['number_of_direct_ballots']);
	__info(_t("Number of delegates who has voted"), $number_of_delegate_ballots);
	__info(_t("Description"), '<br>' . \Logic\text::make_html_from_wiki_text($voteinfo['description']));
	echo '</p>';
	if($voteinfo['number_of_ballots'] > $voteinfo['number_of_direct_ballots']
		&& ($voteinfo['type'] == "yes-no" || $voteinfo['type'] == "median")) {
		echo '<div class="" id="delegate_votes_box">';
		echo '<a href="javascript:void(0)" onclick="show_delegate_votes(\'' . $voteinfo['type'] . '\')">' . _t("See delegate ballots for this vote") . '</a>';
		echo '</div>';
	}
	echo '<p>';
	__link(_t("See all ballots for this vote"), 'vote', 'view_ballots', 'id=' . $voteinfo['id']);
	echo '</p>';
	if($user_allowed_to_vote) {
		echo '<p>';
		__link(_t("Link to this vote's forum debate"), 'forum', 'show_posts', 'topic_id=' . $voteinfo['forum_topic_id']);
		echo '</p>';
		echo '<div class="vote_box">';
		include(__DIR__ . \View\vote::get_vote_form_include($voteinfo['type']));
		echo '</div>';
		__t($_SESSION['delegate_id'] ? "You vote as delegate." : "You vote as individual.");
	}
	echo '<script>';
	\View\vote::output_common_delegate_vote_box_translations_for_js();
	echo 'var yes_text = "' . _t("Yes") . '";';
	echo 'var no_text = "' . _t("No") . '";';
	echo '</script>';
	$vote_script_include = \View\vote::get_vote_script_include($voteinfo['type']);
	if ($vote_script_include)
		include(dirname(__FILE__) . $vote_script_include);
?>

