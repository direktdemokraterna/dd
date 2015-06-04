<?php
	$list_of_votes_from_db = db_vote::get_median_ballots($_GET['id']);
	$list_of_votes = Array();
	foreach($list_of_votes_from_db as $row){
		$list_of_votes[] = Array("user_code" => $row['user_code'], "value" => $row['value'], "delegate_id" => $row['delegate_id'], "delegate_name" => $row['delegate_name']);
	}
	$ballot_counter = vote_helpers::ballot_count_median($list_of_votes);
?>

<script>
	var user_id = <?php echo json_encode($_SESSION['id']); ?>;
	var vote_id = <?php echo json_encode($voteinfo['vote_id']); ?>;
	var constituency_id = <?php echo json_encode($voteinfo['constituency_id']); ?>;
	var list_of_votes = <?php echo json_encode($list_of_votes); ?>;
	var acting_as_delegate = <?php if($_SESSION['acting_as_delegate']) echo "true"; else echo "false"; ?>;
</script>


<h1>Medianomröstning: <?php echo $voteinfo['title']; ?></h1>

<div class="vote_result_box">
	Ställningen i denna omröstning är: <br>
	Medianvärde: <?php echo $ballot_counter; ?><br><br>

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

<div id="user_vote_box">
	Ingen röst är lagd i ditt namn i denna omröstning.
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

<?php if($user_allowed_to_vote) : ?>

	<p><a href="index.php?type=forum&action=show_posts&id=<?php echo $voteinfo['forum_topic_id']; ?>">Länk till denna omröstnings forumdebatt</a></p>

	<div class="vote_box">

	<?php if($voteinfo['status'] == "active" || $voteinfo['status'] == "continouos" || ($voteinfo['status'] == "del_ended" && !$_SESSION['acting_as_delegate'])) : ?>

		Lägg din röst:<br>
	
		<form method="post" action="" class="yes-no">
			<input type="hidden" name="vote_id" value="<?php echo $voteinfo['vote_id']; ?>">
			<input type="hidden" name="ballot" id="ballot" value="">

			<label for "median_value">Ditt önskade värde</label>
			<input type="text" name="median_value" id="median_value">
			<input type="submit" value="Rösta" onmousedown="return encrypt_median_ballot()">
		</form>

	<?php endif; ?>

	</div>

<?php endif; ?>


<script>
list_of_votes.map(function (vote){
	if(vote.user_code == sessionStorage.active_user_code){
		document.getElementById("user_vote_box").innerHTML = "Du har röstat " + vote.value;
		document.getElementById("median_value").value = vote.value;
		
		if(vote.delegate_id == null){
			document.getElementById("user_vote_box").innerHTML += "<br>Du har själv lagt denna röst.";
		}
		else{
			document.getElementById("user_vote_box").innerHTML += "<br>Din delegat <a href='index.php?type=vote&action=view_delegate&id=" + vote.delegate_id + "'>" + vote.delegate_name + "</a> har röstat åt dig.";
		}
	}
});
</script>