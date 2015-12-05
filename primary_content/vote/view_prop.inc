<?php 
	$propinfo = db_prop::get_prop_info($_GET['id']);
	$number_of_ballots = db_prop::get_number_of_ballots($_GET['id']);
	$user_allowed_to_vote = db_constituency::check_user_constituency_access($_SESSION['id'], $propinfo['constituency_id']);
	$list_of_votes_from_db = db_prop::get_prop_supporters($_GET['id']);
	$list_of_votes = Array();
	foreach($list_of_votes_from_db as $row){
		$list_of_votes[] = Array("user_code" => $row['user_code'], "voter_is_delegate_id" => $row['voter_is_delegate_id'], "voter_is_delegate_name" => $row['voter_is_delegate_name'], "support" => $row['support'], "delegate_id" => $row['delegate_id'], "delegate_name" => $row['delegate_name']);
	}

	if($_SESSION['delegate_id']){
		$check_delegate_constituency_access = db_constituency::check_delegate_constituency_access($_SESSION['delegate_id'], $propinfo['constituency_id']);
		$delegate_ballot = db_delegate::get_ballot_for_prop($_GET['id'], $_SESSION['delegate_id']);
	}
?>

<script>
	var user_id = <?php echo json_encode($_SESSION['id']); ?>;
	var prop_id = <?php echo json_encode($propinfo['prop_id']); ?>;
	var constituency_id = <?php echo json_encode($propinfo['constituency_id']); ?>;
	var list_of_votes = <?php echo json_encode($list_of_votes); ?>;
	var acting_as_delegate = <?php if(!empty($check_delegate_constituency_access)) echo "true"; else echo "false"; ?>;
	var support = <?php echo isset($delegate_ballot) && $delegate_ballot['support'] ? 'true' : 'false'; ?>;
</script>

<?php 
	if (isset($_GET['from_action']))
		\View\vote::output_back_link();
	_h1(_t("Proposition: ") . $propinfo['title']);
	echo '<div class="vote_result_box">';
	if($propinfo['status'] == "pending") {
		__("It is " . $propinfo['number_of_supporters'] . " member who support this proposition.");
		_br();
		__("The necessary number of supporters for it to be subject for vote is " . (ceil($propinfo['number_of_voters'] * PROP_TO_VOTE_SUPPORT)) . ".");
	}
	elseif($propinfo['status'] == "affirmed"){
		$vote_id = db_vote::get_vote_id_from_prop_id($propinfo['prop_id']);
		__("This proposition has reached sufficient support to be subject for vote. The vote can be found ");
		_link(_t("here"), 'vote', 'view_vote', 'id=' . $vote_id);
	}
	echo '</div>';
	echo '<div class="vote_result_box" id="user_vote_box">';
		if(isset($delegate_ballot) && $delegate_ballot['support']) {
			__(isset($delegate_ballot['delegate_id'])
				? 'You as delegate support this proposition through your delegate.'
				: 'You as delegate support this proposition yourself.');
		}
	echo '</div>';
	echo '<p>';
	_info("Type of proposed vote", \View\vote::get_vote_type_description($propinfo['type']));
	_info("Constituency", $propinfo['constituency_name']);
	_info("Created", general_helpers::show_date($propinfo['timestamp_created']));
	_info("Proposed by", \View\general::generate_internal_link($propinfo['user_full_name'],
		'member', 'view', 'id=' . $propinfo['user_id']));
	_info("Number of support-ballots", $number_of_ballots['total_number_of_ballots']);
	_info("Whereof personally cast ballots", $number_of_ballots['number_of_direct_ballots']);
	_info("Number of delegates who has voted", $number_of_ballots['number_of_delegate_ballots']);
	_info("Description", '<br>' . \View\general::make_html_from_wiki_text($propinfo['description']));
	echo '</p>';
	if($number_of_ballots['number_of_delegate_ballots']){
		echo '<div class="" id="delegate_votes_box">';
		echo '<a href="javascript:void(0)" onclick="show_delegate_votes(\'prop\')">' 
		. _t("See delegate ballots for this proposition") . '</a>';
		echo '</div>';
	}
	echo '<p>';
	_link(_t("See all support-ballots for this proposition"), 'vote', 'view_prop_ballots', 'id=' . $_GET['id']);
	echo '</p>';
	if($user_allowed_to_vote) {
		echo '<p>';
		_link(_t("Link to this proposition's forum debate"), 'forum', 'show_posts', 'topic_id=' . $propinfo['forum_topic_id']);
		echo '</p>';
	}
	if($user_allowed_to_vote && $propinfo['status'] == "pending") {
		echo '<div class="vote_box">';
		_open_form("yes-no");
		_hidden("prop_id", $propinfo['prop_id']);
		_hidden("ballot", "");
		echo '<input type="submit" class="vote_button" style="display: none" id="green_vote" value="' 
		. _t("Support") . '" onmousedown="return encrypt_prop_ballot(true)">';
		echo '<input type="submit" class="vote_button" style="display: none" title="' 
		. _t("Click to stop supporting") . '" id="yellow_vote" value="' . _t("Supporting") 
		. '" onmousedown="return encrypt_prop_ballot(false)">';
		echo '</form>';
		echo '</div>';
		__($_SESSION['delegate_id'] ? "You vote as delegate." : "You vote as individual.");
	}

	echo '<script>';
	echo 'var support_hint = "' . _t("Click on") . " \\\"" . _t("Support") . "\\\" " 
		. _t("if you want to support this proposition") . '";';
	echo 'var delegate_supporting = "' . _t("You support this proposition through your delegate ") . '";';
	echo 'var supporting = "' . _t("You support this proposition.") . '";';
	echo 'var stop_supporting_hint = " ' . _t("Click on") . " \\\"" . _t("Supporting") . "\\\" " 
		. _t("to stop supporting this proposition.") . '";';
	echo 'var support_withdrawn = "' . _t("You have withdrawn your support for this proposition.") . '";';
	echo '</script>';
?>
<script>
document.getElementById("user_vote_box").innerHTML = support_hint;
list_of_votes.map(function (vote){
	if(vote.user_code == sessionStorage.active_user_code && !acting_as_delegate) {
		support = vote.support;
		document.getElementById("user_vote_box").innerHTML = support
			? (vote.delegate_id 
				? "<br>" + delegate_supporting + " <a href='index.php?type=vote&action=view_delegate&id=" + 
				vote.delegate_id + "'>" + vote.delegate_name + "</a>." 
				: supporting) 
				+ stop_supporting_hint
			: support_withdrawn;
	}
});
$("#green_vote").css('display', (support ? 'none' : 'inline'));
$("#yellow_vote").css('display', (support ? 'inline' : 'none'));
</script>