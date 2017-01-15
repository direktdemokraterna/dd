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
	$delegate_ballot = null;
	$delegate_constituency_access = null;
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
	\View\controls::output_search_back_link();
	\View\vote::output_vote_header($voteinfo);

	\View\general::open_div("vote_result_box");
	\View\vote::output_vote_result_with_header($voteinfo, $ballots_to_count);
	__br();
	\View\vote::output_vote_finish_status($voteinfo);
	\View\general::close_div();

	\View\general::open_div("vote_result_box", "user_vote_box");
	\View\vote::output_ballot_info($voteinfo, $delegate_ballot);
	\View\general::close_div();

	echo '<p>';
	__strong(_t("Constituency: ") . $voteinfo['constituency_name']);
	__br();
	\View\vote::output_proposition_creation_info($voteinfo);
	__br();
	\View\vote::output_vote_started_info($voteinfo);
	__br();	
	\View\vote::output_number_of_cast_ballots_info($voteinfo, $number_of_delegate_ballots);
	\View\vote::output_vote_description($voteinfo);
	echo '</p>';

	\View\vote::output_view_cast_ballots($voteinfo);
	\View\vote::output_vote_debate_link($voteinfo);
	\View\vote::output_vote_buttons($voteinfo, $user_allowed_to_vote);
	\View\vote::output_javascript_vote_localized_texts();
	\View\vote::output_javascript_vote_handlers($voteinfo);
?>
