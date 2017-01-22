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
	__h1("Proposition: " . $propinfo['title']);
	echo '<div class="vote_result_box">';
	if($propinfo['status'] == "pending") {
		echo "Det är " . $propinfo['number_of_supporters'] . " användare som stöder denna proposition.";
		__br();
		echo "Nödvändigt antal stöd för att den ska bli en omröstning är " . (ceil($propinfo['number_of_voters'] * PROP_TO_VOTE_SUPPORT)) . ".";
	}
	elseif($propinfo['status'] == "affirmed"){
		$vote_id = db_vote::get_vote_id_from_prop_id($prop_id);
		echo "Den här propositionen har uppnått tillräckligt stöd och har blivit en omröstning. Omröstningen kan ses ";
		__link("här", 'vote', 'view_vote', 'id=' . $vote_id);
	}
	echo '</div>';
	if($voter_allowed_to_vote && $propinfo['status'] == "pending") {
		echo '<div class="vote_result_box" id="user_vote_box">';
			if(isset($delegate_ballot) && $delegate_ballot['support']) {
				echo (isset($delegate_ballot['delegate_id'])
					? 'Du som delegat stöder denna proposition genom din delegat.'
					: 'Du som delegat stöder denna proposition själv.');
			}
		echo '</div>';
	}
	echo '<p>';
	__info("Föreslagen omröstning", \View\vote::get_vote_type_description($propinfo['type']));
	__info("Valkrets", $propinfo['constituency_name']);
	__info("Skapad", general_helpers::show_date($propinfo['timestamp_created']));
	__info("Föreslagen av", _link($propinfo['user_full_name'],
		'member', 'view', 'id=' . $propinfo['user_id']));
	__info("Antal stöd", $number_of_ballots['total_number_of_ballots']);
	__info("Antal personligt lagda stöd", $number_of_ballots['number_of_direct_ballots']);
	__info("Antal delegatstöd", $number_of_ballots['number_of_delegate_ballots']);
	__info("Beskrivning", '<br>' . \Logic\text::make_html_from_wiki_text($propinfo['description']));
	echo '</p>';
	if($number_of_ballots['number_of_delegate_ballots']){
		echo '<div class="" id="delegate_votes_box">';
		echo '<a href="javascript:void(0)" onclick="show_delegate_votes(\'support\')">Se delegatstöd för denna proposition</a>';
		echo '</div>';
	}
	echo '<p>';
	__link("Se alla stöd för denna proposition", 'vote', 'view_prop_ballots', 'id=' . $_GET['id']);
	echo '</p>';
	if($voter_allowed_to_vote) {
		echo '<p>';
		__link("Länk till denna propositions diskussionstråd", 'forum', 'show_posts', 'topic_id=' . $propinfo['forum_topic_id']);
		echo '</p>';
		if($propinfo['status'] == "pending") {
			echo '<div class="vote_box">';
			__open_form("yes-no");
			__hidden("prop_id", $prop_id);
			__hidden("ballot", "");
			echo '<div class="vote-buttons">';
			echo '<input type="submit" class="vote_button" style="display: none" id="green_vote" value="Stöd" onmousedown="return encrypt_prop_ballot(true)">';
			echo '<input type="submit" class="vote_button" style="display: none" title="Tryck för att sluta stödja" id="yellow_vote" value="Stödjer" onmousedown="return encrypt_prop_ballot(false)">';
			echo '</div></form>';
			echo '</div>';
			echo ($is_voting_as_delegate ? "Du röstar som delegat." : "Du röstar som individ.");
		}
	}

	echo '<script>';
	echo 'var support_hint = "Klicka på \\"Stöd\\" Om du vill stödja den här propositionen";';
	echo 'var delegate_supporting = "Du stödjer den här propositionen genom din delegat ";';
	echo 'var supporting = "Du stödjer den här propositionen.";';
	echo 'var stop_supporting_hint = "Klicka på \\"Stödjer\\" för att sluta stödja denna proposition.";';
	echo 'var support_withdrawn = "Du har tagit tillbaka ditt stöd för denna proposition";';
	echo 'var support_text = "Stöd";';
	echo 'var not_support_text = "Stöd inte";';
	\View\vote::output_common_delegate_vote_box_translations_for_js();
	echo '</script>';
	if($voter_allowed_to_vote && $propinfo['status'] == "pending")
		include(dirname(__FILE__) . "/view_prop_user_vote_box_js.inc");

?>
