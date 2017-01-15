<?php
	$prop_id = $_GET['id'];
	$is_voting_as_delegate = $_SESSION['delegate_id'];
	$voter_id = $is_voting_as_delegate
		? $_SESSION['delegate_id']
		: $_SESSION['id'];
	$propinfo = db_prop::get_prop_info($prop_id);
	$constituency_id = $propinfo['constituency_id'];
	$number_of_ballots = db_prop::get_number_of_ballots($prop_id);
	$voter_allowed_to_vote = db_constituency::check_voter_constituency_access($voter_id, $constituency_id);
	$all_ballots_from_db = db_prop::get_prop_supporters($prop_id);
	$all_ballots = array();
	foreach($all_ballots_from_db as $row){
		$all_ballots[] = Array("user_code" => $row['user_code'], "voter_id" => $row['voter_id'], "voter_is_delegate_name" => $row['voter_is_delegate_name'], "support" => $row['support'], "delegate_id" => $row['delegate_id'], "delegate_name" => $row['delegate_name']);
	}
	$ballots_to_count = array_filter($all_ballots, 
		function($ballot) {return $ballot['user_code'];});
	$delegate_ballots = array_filter($all_ballots, 
		function($ballot) {return $ballot['voter_id'];});
	if($is_voting_as_delegate)
		$delegate_ballot = db_delegate::get_ballot_for_prop($prop_id, $voter_id);
?>

<script>
	var user_id = <?php echo json_encode($voter_id); ?>;
	var prop_id = <?php echo json_encode($prop_id); ?>;
	var constituency_id = <?php echo json_encode($constituency_id); ?>;
	var ballots_to_count = <?php echo \View\general::db_result_to_json($ballots_to_count); ?>;
	var delegate_ballots = <?php echo \View\general::db_result_to_json($delegate_ballots); ?>;
	var acting_as_delegate = <?php echo $is_voting_as_delegate ? "true" : "false"; ?>;
	var support = <?php echo isset($delegate_ballot) && $delegate_ballot['support'] ? 'true' : 'false'; ?>;
</script>

<?php 
	\View\controls::output_search_back_link();
	__h1(_t("Proposition: ") . $propinfo['title']);
	echo '<div class="vote_result_box">';
	if($propinfo['status'] == "pending") {
		__t("It is " . $propinfo['number_of_supporters'] . " member who support this proposition.");
		__br();
		__t("The necessary number of supporters for it to be subject for vote is " . (ceil($propinfo['number_of_voters'] * PROP_TO_VOTE_SUPPORT)) . ".");
	}
	elseif($propinfo['status'] == "affirmed"){
		$vote_id = db_vote::get_vote_id_from_prop_id($prop_id);
		__t("This proposition has reached sufficient support to be subject for vote. The vote can be found ");
		__link(_t("here"), 'vote', 'view_vote', 'id=' . $vote_id);
	}
	echo '</div>';
	if($voter_allowed_to_vote && $propinfo['status'] == "pending") {
		echo '<div class="vote_result_box" id="user_vote_box">';
			if(isset($delegate_ballot) && $delegate_ballot['support']) {
				__t(isset($delegate_ballot['delegate_id'])
					? 'You as delegate support this proposition through your delegate.'
					: 'You as delegate support this proposition yourself.');
			}
		echo '</div>';
	}
	echo '<p>';
	__info(_t("Type of proposed vote"), \View\vote::get_vote_type_description($propinfo['type']));
	__info(_t("Constituency"), $propinfo['constituency_name']);
	__info(_t("Created", array('class' => 'adj')), general_helpers::show_date($propinfo['timestamp_created']));
	__info(_t("Proposed by"), _link($propinfo['user_full_name'],
		'member', 'view', 'id=' . $propinfo['user_id']));
	__info(_t("Number of support-ballots"), $number_of_ballots['total_number_of_ballots']);
	__info(_t("Whereof personally cast ballots"), $number_of_ballots['number_of_direct_ballots']);
	__info(_t("Number of delegates who has voted"), $number_of_ballots['number_of_delegate_ballots']);
	__info(_t("Description"), '<br>' . \Logic\text::make_html_from_wiki_text($propinfo['description']));
	echo '</p>';
	if($number_of_ballots['number_of_delegate_ballots']){
		echo '<div class="" id="delegate_votes_box">';
		echo '<a href="javascript:void(0)" onclick="show_delegate_votes(\'support\')">' 
		. _t("See delegate ballots for this proposition") . '</a>';
		echo '</div>';
	}
	echo '<p>';
	__link(_t("See all support-ballots for this proposition"), 'vote', 'view_prop_ballots', 'id=' . $_GET['id']);
	echo '</p>';
	if($voter_allowed_to_vote) {
		echo '<p>';
		__link(_t("Link to this proposition's forum debate"), 'forum', 'show_posts', 'topic_id=' . $propinfo['forum_topic_id']);
		echo '</p>';
		if($propinfo['status'] == "pending") {
			echo '<div class="vote_box">';
			__open_form("yes-no");
			__hidden("prop_id", $prop_id);
			__hidden("ballot", "");
			echo '<div class="vote-buttons">';
			echo '<input type="submit" class="vote_button" style="display: none" id="green_vote" value="' 
			. _t("Support") . '" onmousedown="return encrypt_prop_ballot(true)">';
			echo '<input type="submit" class="vote_button" style="display: none" title="' 
			. _t("Click to stop supporting") . '" id="yellow_vote" value="' . _t("Supporting") 
			. '" onmousedown="return encrypt_prop_ballot(false)">';
			echo '</div></form>';
			echo '</div>';
			__t($is_voting_as_delegate ? "You vote as delegate." : "You vote as individual.");
		}
	}

	echo '<script>';
	echo 'var support_hint = "' . _t("Click on") . " \\\"" . _t("Support") . "\\\" " 
		. _t("if you want to support this proposition") . '";';
	echo 'var delegate_supporting = "' . _t("You support this proposition through your delegate ") . '";';
	echo 'var supporting = "' . _t("You support this proposition.") . '";';
	echo 'var stop_supporting_hint = " ' . _t("Click on") . " \\\"" . _t("Supporting") . "\\\" " 
		. _t("to stop supporting this proposition.") . '";';
	echo 'var support_withdrawn = "' . _t("You have withdrawn your support for this proposition.") . '";';
	echo 'var support_text = "' . _t("Support", array("form" => "present")) . '";';
	echo 'var not_support_text = "' . _t("Don't support") . '";';
	\View\vote::output_common_delegate_vote_box_translations_for_js();
	echo '</script>';
	if($voter_allowed_to_vote && $propinfo['status'] == "pending")
		include(dirname(__FILE__) . "/view_prop_user_vote_box_js.inc");
?>
