<?php 
	$voteinfo = db_vote::get_vote_info($_GET['id']); 
	$user_allowed_to_vote = db_constituency::check_user_constituency_access($_SESSION['id'], $voteinfo['constituency_id']);

	$list_of_votes_from_db = db_vote::get_ballots($_GET['id']);
	$list_of_votes = Array();
	foreach($list_of_votes_from_db as $row){
		$list_of_votes[] = Array("user_code" => $row['user_code'], "alternative" => $row['alternative'], "value" => $row['value'], "prio_ranking" => $row['prio_ranking'], "delegate_id" => $row['delegate_id'], "delegate_name" => $row['delegate_name']);
	}
	$ballot_counter = vote_helpers::ballot_count_yes_no_abstain($list_of_votes);
?>

<script>
	var user_id = <?php echo json_encode($_SESSION['id']); ?>;
	var vote_id = <?php echo json_encode($voteinfo['vote_id']); ?>;
	var constituency_id = <?php echo json_encode($voteinfo['constituency_id']); ?>;
	var list_of_votes = <?php echo json_encode($list_of_votes); ?>;
	<?php
		if($_SESSION['delegate_id']){
			$check_delegate_constituency_access = db_constituency::check_delegate_constituency_access($_SESSION['delegate_id'], $voteinfo['constituency_id']);
		}
	?>
	var acting_as_delegate = <?php if(!empty($check_delegate_constituency_access)) echo "true"; else echo "false"; ?>;
</script>

<?php if($voteinfo['type'] == "yes-no") : ?>
	<h1>Votering: <?php echo $voteinfo['title']; ?></h1>
<?php elseif($voteinfo['type'] == "prio-vote") : ?>
	<h1>Prioritetsomröstning: <?php echo $voteinfo['title']; ?></h1>
<?php elseif($voteinfo['type'] == "candidate-election") : ?>
	<h1>Personval: <?php echo $voteinfo['title']; ?></h1>
<?php elseif($voteinfo['type'] == "median") : ?>
	<h1>Medianomröstning: <?php echo $voteinfo['title']; ?></h1>
<?php elseif($voteinfo['type'] == "workgroup-election") : ?>
	<h1><?php echo $voteinfo['title']; ?></h1>
	<?php
		$workgroup_id = $voteinfo['from_proposition_id']; // workgroup_id is stored in db column from_proposition_id
		$workgroup_title = db_workgroup::get_name_from_id($workgroup_id);
	?>
	<p>Den här omröstningen utser medlemmarna till arbetsgruppen <a href="index.php?type=workgroup&action=view&id=<?php echo $workgroup_id; ?>"><?php echo $workgroup_title; ?></a></p>
<?php endif; ?>

<div class="vote_result_box">

	<?php if($voteinfo['type'] == "yes-no") : ?>
		<?php vote_helpers::output_yes_no_result($list_of_votes); ?>
	<?php elseif($voteinfo['type'] == "prio-vote") : ?>
		<?php vote_helpers::output_prio_vote_result($_GET['id']); ?>
	<?php elseif($voteinfo['type'] == "candidate-election") : ?>
		<?php vote_helpers::output_candidate_election_result($_GET['id']); ?>
	<?php elseif($voteinfo['type'] == "workgroup-election") : ?>
		<?php vote_helpers::output_workgroup_election_result($_GET['id'], $workgroup_id); ?>
	<?php elseif($voteinfo['type'] == "median") : ?>
		<?php vote_helpers::output_median_result($list_of_votes); ?>
	<?php endif; ?>


	<?php if($voteinfo['status'] == "ended" || $voteinfo['status'] == "finished") : ?>
		Omröstningen är avslutad. Den avslutades <?php echo general_helpers::show_date($voteinfo['timestamp_ended']); ?>.
	<?php elseif($voteinfo['status'] == "del_ended") : ?>
		Omröstningen avslutas <?php echo general_helpers::show_date($voteinfo['timestamp_ended']); ?>. För delegater stängdes röstningsmöjligheten <?php echo general_helpers::show_date($voteinfo['timestamp_delegate_ended']); ?>.
	<?php elseif($voteinfo['status'] == "continuous") : ?>
		Det här är en kontinuerlig omröstning och fortsätter tills en votering bestämmer att den ska avslutas.
	<?php else : ?>
		Omröstningen avslutas <?php echo general_helpers::show_date($voteinfo['timestamp_ended']); ?>. För delegater stänger röstningsmöjligheten <?php echo general_helpers::show_date($voteinfo['timestamp_delegate_ended']); ?>.
	<?php endif; ?>

</div>

<div class="vote_result_box" id="user_vote_box">
	<?php if($_SESSION['delegate_id']) : ?>
		<?php if($delegate_vote = db_delegate::get_delegate_ballot_for_vote($_GET['id'], $_SESSION['delegate_id'])) : ?>
			Du som delegat har röstat i denna omröstning.
		<?php else : ?>
			Du som delegat har inte röstat i denna omröstning.
		<?php endif; ?>
	<?php else : ?>
		Ingen röst är lagd i ditt namn i denna omröstning.
	<?php endif; ?>
</div>


<p>
<strong>Valkrets: </strong><?php echo $voteinfo['constituency_name']; ?><br>
<?php if($voteinfo['proposition_created']) : ?>
  <strong>Propositionen skapad: </strong><?php echo general_helpers::show_date($voteinfo['proposition_created']); ?><br>
  <strong>Propositionen skapad av: </strong><a href="index.php?type=member&action=view&id=<?php echo $voteinfo['user_id']; ?>"><?php echo $voteinfo['user_full_name']; ?></a><br>
<?php else : ?>
  <strong>Omröstningen skapad av administratör</strong><br>
<?php endif; ?>
<strong>Omröstningen startad: </strong><?php echo general_helpers::show_date($voteinfo['timestamp_created']); ?><br>
<?php if($voteinfo['status'] == "continuous") : ?>
  <strong>Omröstningen är kontinuerlig.</strong><br>
<?php else : ?>
  <strong>Delegatröstning avslutas: </strong><?php echo general_helpers::show_date($voteinfo['timestamp_delegate_ended']); ?><br>
  <strong>Personlig röstning avslutas: </strong><?php echo general_helpers::show_date($voteinfo['timestamp_ended']); ?><br>
<?php endif; ?>
<strong>Antal lagda röster: </strong><?php echo $voteinfo['number_of_ballots']; ?><br>
<strong>Varav personligt lagda röster: </strong><?php echo $voteinfo['number_of_direct_ballots']; ?><br>

<strong>Beskrivning:</strong><br>
<?php echo nl2br($voteinfo['description']); ?>
</p>


<?php if($voteinfo['number_of_ballots'] > $voteinfo['number_of_direct_ballots']) : ?>
	<p><a href="index.php?type=vote&action=delegate_votes&id=<?php echo $_GET['id']; ?>">Se delegatröster för denna omröstning</a></p>
<?php endif; ?>


<?php if($user_allowed_to_vote) : ?>

	<p><a href="index.php?type=forum&action=show_posts&id=<?php echo $voteinfo['forum_topic_id']; ?>">Länk till denna omröstnings forumdebatt</a></p>

	<div class="vote_box">

		<?php if($voteinfo['type'] == "yes-no") : ?>
			<?php include(dirname(__FILE__)."/vote_types/yes-no.inc"); ?>
		<?php elseif($voteinfo['type'] == "prio-vote") : ?>
			<?php include(dirname(__FILE__)."/vote_types/prio-vote.inc"); ?>
		<?php elseif($voteinfo['type'] == "candidate-election" || $voteinfo['type'] == "workgroup-election") : ?>
			<?php include(dirname(__FILE__)."/vote_types/candidate-election.inc"); ?>
		<?php elseif($voteinfo['type'] == "median") : ?>
			<?php include(dirname(__FILE__)."/vote_types/median.inc"); ?>
		<?php endif; ?>

	</div>

	<?php if(isset($_SESSION['delegate_id'])) : ?>
		Du röstar som delegat.
	<?php else : ?>
		Du röstar som enskild användare.
	<?php endif; ?>

<?php endif; ?>


<?php if($voteinfo['type'] == "yes-no") : ?>
	<?php include(dirname(__FILE__)."/vote_types/yes-no_js.inc"); ?>
<?php elseif($voteinfo['type'] == "prio-vote" || $voteinfo['type'] == "candidate-election" || $voteinfo['type'] == "workgroup-election") : ?>
	<?php include(dirname(__FILE__)."/vote_types/prio-vote_js.inc"); ?>
<?php elseif($voteinfo['type'] == "median") : ?>
	<?php include(dirname(__FILE__)."/vote_types/median_js.inc"); ?>
<?php endif; ?>

