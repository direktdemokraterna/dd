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
	\View\general::open_div(null, "vote_wrapper");		
		\View\general::open_div("vote-container float-left");
			
			if($propinfo['status'] == "pending") {
				echo '<div class="vote_result_box">';
				echo "Det är " . $propinfo['number_of_supporters'] . " användare som stöder denna proposition.";
				__br();
				echo "Nödvändigt antal stöd för att den ska bli en omröstning är " . (ceil($propinfo['number_of_voters'] * PROP_TO_VOTE_SUPPORT)) . ".";
				echo '</div>';
			}
			elseif($propinfo['status'] == "affirmed"){
				echo '<div class="vote_result_box">';
				$vote_id = db_vote::get_vote_id_from_prop_id($prop_id);
				echo "Den här propositionen har uppnått tillräckligt stöd och har blivit en omröstning. Omröstningen kan ses ";
				__link("här", 'vote', 'view_vote', 'id=' . $vote_id);
				echo '</div>';
			}
			
			if($voter_allowed_to_vote && $propinfo['status'] == "pending") {
				echo '<div class="vote_result_box" id="user_vote_box">';
					if(isset($delegate_ballot) && $delegate_ballot['support']) {
						echo (isset($delegate_ballot['delegate_id'])
							? 'Du som delegat stöder denna proposition genom din delegat.'
							: 'Du som delegat stöder denna proposition själv.');
					}
				echo '</div>';
			}
		__info("<div class='vote-description'><h2>Beskrivning</h2>", \Logic\text::make_html_from_wiki_text($propinfo['description'] . '</div>'));
		
		if($voter_allowed_to_vote) {
			if($propinfo['status'] == "pending") {
				echo '<div class="vote_box">';
				__open_form("yes-no");
				__hidden("prop_id", $prop_id);
				__hidden("ballot", "");
				echo '<div class="vote-buttons">';
				echo '<button type="submit" class="vote_button" style="display: none" id="green_vote" value="Stöd" onmousedown="return encrypt_prop_ballot(true)">Stöd</button>';
				echo '<button type="submit" class="vote_button" style="display: none" title="Tryck för att sluta stödja" id="yellow_vote" value="Stödjer" onmousedown="return encrypt_prop_ballot(false)">Sluta stödja</button>';
				echo '</div></form>';
				echo '</div>';
				echo ($is_voting_as_delegate ? "Du röstar som delegat." : "Du röstar som individ.");
			}
		}		
		
		\View\general::close_div(); /* Close vote_container float-left */		
		\View\general::open_div("vote-container float-right");
		
			\View\general::open_div(null, "vote_container_grey_box");
				echo '<a class="no-line"><h2 class="h2-information">Information</h2></a>';
				echo '<table cellpadding="0"><tr>';
				__td(_info("Föreslagen omröstning", '</td><td>' . \View\vote::get_vote_type_description($propinfo['type'])));
				echo '</tr><tr>';
				__td(_info("Skapad", '</td><td>' . general_helpers::show_date($propinfo['timestamp_created'])));
				echo '</tr><tr>';
				__td(_info("Föreslagen av", '</td><td>' . _link($propinfo['user_full_name'],
					'member', 'view', 'id=' . $propinfo['user_id'])));
				echo '</tr><tr>';
				__td(_info("Stöd", '</td><td>' . $number_of_ballots['total_number_of_ballots']));
				echo '</tr><tr>';
				__td(_info("Personligt stöd", '</td><td>' . $number_of_ballots['number_of_direct_ballots']));
				echo '</tr><tr>';
				__td(_info("Delegatstöd", '</td><td>' . $number_of_ballots['number_of_delegate_ballots']));
				echo '</tr></table>';							
				echo '<a class="no-line"><h2 class="h2-tools">Verktyg</h2></a>';
				echo '<table cellpadding="0"><tr><td>';
				if($number_of_ballots['number_of_delegate_ballots']){
					echo '<a href="javascript:void(0)" onclick="show_delegate_votes(\'support\')" class="link-icon">Se delegatstöd</a>';
				}	
				echo '</td></tr><tr><td>';
				__link("Se allt stöd", 'vote', 'view_prop_ballots', 'id=' . $_GET['id'], 'link-icon');
				echo '</td></tr>';
				echo '</table>';
				
			\View\general::close_div();	/* Close vote_container_grey_box */	
			\View\vote::output_proposition_debate_link($propinfo); /* Discussion button */
		\View\general::close_div();	/* Close vote-container float-right */
	\View\general::close_div();	/* Close vote-wrapper */
				
				
	

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
