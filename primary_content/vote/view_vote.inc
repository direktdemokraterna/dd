<?php 
	$voteinfo = db_vote::get_vote_info($_GET['id']); 
	$user_allowed_to_vote = db_constituency::check_user_constituency_access($_SESSION['id'], $voteinfo['constituency_id']);
	$number_of_delegate_ballots = db_delegate::number_of_delegate_ballots_for_vote($_GET['id']);

	$list_of_votes_from_db = db_vote::get_ballots($_GET['id']);
	$list_of_votes = Array();
	foreach($list_of_votes_from_db as $row){
		if($voteinfo['type'] == "yes-no"){
			$list_of_votes[] = Array("user_code" => $row['user_code'], "voter_is_delegate_id" => $row['voter_is_delegate_id'], "voter_is_delegate_name" => $row['voter_is_delegate_name'], "alternative" => $row['ballot'], "delegate_id" => $row['delegate_id'], "delegate_name" => $row['delegate_name']);
		}
		elseif($voteinfo['type'] == "median"){
			$list_of_votes[] = Array("user_code" => $row['user_code'], "voter_is_delegate_id" => $row['voter_is_delegate_id'], "voter_is_delegate_name" => $row['voter_is_delegate_name'], "value" => $row['ballot'], "delegate_id" => $row['delegate_id'], "delegate_name" => $row['delegate_name']);
		}
		elseif($voteinfo['type'] == "prio-vote" || $voteinfo['type'] == "candidate-election" || $voteinfo['type'] == "workgroup-election"){
			$list_of_votes[] = Array("user_code" => $row['user_code'], "voter_is_delegate_id" => $row['voter_is_delegate_id'], "voter_is_delegate_name" => $row['voter_is_delegate_name'], "prio_ranking" => $row['ballot'], "delegate_id" => $row['delegate_id'], "delegate_name" => $row['delegate_name']);
		}
	}

	if($_SESSION['delegate_id']){
		$check_delegate_constituency_access = db_constituency::check_delegate_constituency_access($_SESSION['delegate_id'], $voteinfo['constituency_id']);
		$delegate_ballot = db_delegate::get_ballot_for_vote($_GET['id'], $_SESSION['delegate_id']);
	}
?>

<script>
	var user_id = <?php echo json_encode($_SESSION['id']); ?>;
	var vote_id = <?php echo json_encode($voteinfo['vote_id']); ?>;
	var constituency_id = <?php echo json_encode($voteinfo['constituency_id']); ?>;
	var list_of_votes = <?php echo json_encode($list_of_votes); ?>;
	var acting_as_delegate = <?php if(!empty($check_delegate_constituency_access)) echo "true"; else echo "false"; ?>;
</script>

<?php 
	if (isset($_GET['from_action']))
		\View\vote::output_back_link();
	\View\vote::output_vote_header($voteinfo);

	\View\general::open_div("vote_result_box");
	if($voteinfo['type'] == "yes-no")
		vote_helpers::output_yes_no_result($list_of_votes);
	elseif($voteinfo['type'] == "prio-vote")
		vote_helpers::output_prio_vote_result($_GET['id']);
	elseif($voteinfo['type'] == "candidate-election")
		vote_helpers::output_candidate_election_result($_GET['id']);
	elseif($voteinfo['type'] == "workgroup-election")
		vote_helpers::output_workgroup_election_result($_GET['id'], $voteinfo['from_proposition_id']);
	elseif($voteinfo['type'] == "median")
		vote_helpers::output_median_result($list_of_votes);
	_br();
	if($voteinfo['status'] == "ended" || $voteinfo['status'] == "finished")
		echo _t("The vote is finished. It finished ") 
		. general_helpers::show_date($voteinfo['timestamp_ended']) . '.';
	elseif($voteinfo['status'] == "del_ended")
		echo _t("The vote finishes ") . general_helpers::show_date($voteinfo['timestamp_ended']) 
			. _t('. For delegates the possibility to vote closed ') 
			. general_helpers::show_date($voteinfo['timestamp_delegate_ended']) . '.';
	elseif($voteinfo['status'] == "continuous")
		__("This is a continous vote and it continues until it is ended through a new yes/no vote.");
	else
		echo _t("The vote finishes ") . general_helpers::show_date($voteinfo['timestamp_ended'])
			. _t(". For delegates the possibility to vote closes ") . general_helpers::show_date($voteinfo['timestamp_delegate_ended']) . ".";
	\View\general::close_div();

	\View\general::open_div("vote_result_box", "user_vote_box");
	if($_SESSION['delegate_id']) {
		if(empty($delegate_ballot))
			__("You have not yet voted in this vote as delegate.");
		else {
			if(isset($delegate_ballot['delegate_id']))
				__("You as delegate have let your delegate vote in this vote.");
			else
				__("You as delegate have cast your own ballot in this vote.");
			_br();
			__("Your ballot:");
			_br();
			echo \View\vote::get_ballot_content($voteinfo['type'], $delegate_ballot['ballot']);
		}
	}
	else __("No ballot has been cast in your name in this vote.");
	\View\general::close_div();
	echo '<p>';
	_strong(_t("Constituency: ") . $voteinfo['constituency_name']);
	_br();
	if($voteinfo['status'] != "continuous" && $voteinfo['status'] != "finished") {
		_strong(_t("Proposition created: "));
		echo general_helpers::show_date($voteinfo['proposition_created']);
		_br();
		_strong(_t("Proposition created by: "));
		_link($voteinfo['user_full_name'], 'member', 'view', 'id=' . $voteinfo['user_id']);
	}
  	else 
		_strong(_t("Vote created by administrator"));
	_br();
	_strong(_t("Vote started: "));
	echo general_helpers::show_date($voteinfo['timestamp_created']);
	_br();	
	if($voteinfo['status'] == "continuous"){
		_strong(_t("The vote is continous."));
		_br();
	}
	else {
		_info("Delegate voting closes", general_helpers::show_date($voteinfo['timestamp_delegate_ended']));
		_info("Vote closes", general_helpers::show_date($voteinfo['timestamp_ended']));
  	}
	_info("Number of cast ballots", $voteinfo['number_of_ballots']);
	_info("Whereof personally cast ballots", $voteinfo['number_of_direct_ballots']);
	_info("Number of delegates who has voted", $number_of_delegate_ballots);
	_info("Description", '<br>' . \View\general::make_html_from_wiki_text($voteinfo['description']));
	echo '</p>';
	if($voteinfo['number_of_ballots'] > $voteinfo['number_of_direct_ballots']
		&& ($voteinfo['type'] == "yes-no" || $voteinfo['type'] == "median")) {
		echo '<div class="" id="delegate_votes_box">';
		echo '<a href="javascript:void(0)" onclick="show_delegate_votes()">' . _t("See delegate ballots for this vote") . '</a>';
		echo '</div>';
	}
	echo '<p>';
	_link(_t("See all ballots for this vote"), 'vote', 'view_ballots', 'id=' . $_GET['id']);
	echo '</p>';
	if($user_allowed_to_vote) {
		echo '<p>';
		_link(_t("Link to this vote's forum debate"), 'forum', 'show_posts', 'topic_id=' . $voteinfo['forum_topic_id']);
		echo '</p>';
		echo '<div class="vote_box">';
		include(dirname(__FILE__) . \View\vote::get_vote_form_include($voteinfo['type']));
		echo '</div>';
		__($_SESSION['delegate_id'] ? "You vote as delegate." : "You vote as individual.");
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

