<?php 
	$propinfo = db_prop::get_prop_info($_GET['id']); 
	$user_allowed_to_vote = db_constituency::check_user_constituency_access($_SESSION['id'], $propinfo['constituency_id']);
	$list_of_votes_from_db = db_prop::get_prop_supporters($_GET['id']);
	$list_of_votes = Array();
	foreach($list_of_votes_from_db as $row){
		$list_of_votes[] = Array("user_code" => $row['user_code'], "support_type" => $row['support_type'], "delegate_id" => $row['delegate_id'], "delegate_name" => $row['delegate_name']);
	}
?>

<script>
	var user_id = <?php echo json_encode($_SESSION['id']); ?>;
	var prop_id = <?php echo json_encode($propinfo['prop_id']); ?>;
	var constituency_id = <?php echo json_encode($propinfo['constituency_id']); ?>;
	var list_of_votes = <?php echo json_encode($list_of_votes); ?>;
	<?php
		if($_SESSION['delegate_id']){
			$check_delegate_constituency_access = db_constituency::check_delegate_constituency_access($_SESSION['delegate_id'], $voteinfo['constituency_id']);
		}
	?>
	var acting_as_delegate = <?php if(!empty($check_delegate_constituency_access)) echo "true"; else echo "false"; ?>;
</script>


<h1>Proposition: <?php echo $propinfo['title']; ?></h1>

<div class="vote_result_box">
	<?php if($propinfo['status'] == "pending") : ?>
		Det är <?php echo $propinfo['number_of_supporters']; ?> medlem<?php if($propinfo['number_of_supporters'] != 1) echo "mar"; ?> som stöder denna proposition och <?php echo $propinfo['number_of_enemies']; ?> som förkastar den. <br>
		Nödvändigt antal för att den ska godkännas och gå vidare till omröstning är <?php echo ceil($propinfo['number_of_voters'] * PROP_TO_VOTE_SUPPORT); ?>.
	<?php elseif($propinfo['status'] == "rejected") : ?>
		Den här propositionen har förkastats av medlemmarna och är inte längre aktiv. 
	<?php elseif($propinfo['status'] == "affirmed") : ?>
		<?php $vote_id = db_vote::get_vote_id_from_prop_id($propinfo['prop_id']); ?>
		Den här propositionen har uppnått tillräckligt stöd för att gå vidare och bli omröstning. Omröstningen finns <a href="index.php?type=vote&action=view_vote&id=<?php echo $vote_id; ?>">här</a>.
	<?php endif; ?>
</div>

<div id="user_vote_box">
	Ingen röst är lagd i ditt namn angående denna proposition.
</div>

<p>
<strong>Typ av föreslagen omröstning: </strong>
<?php 
	if($propinfo['type'] == "yes-no") echo "Votering (ja/nej)";
	elseif($propinfo['type'] == "prio-vote") echo "Prioritetsomröstning";
	elseif($propinfo['type'] == "candidate-election") echo "Personval";
	elseif($propinfo['type'] == "median") echo "Medianomröstning";
	elseif($propinfo['type'] == "budget") echo "Budgetomröstning";
?>
<br>
<strong>Valkrets: </strong><?php echo $propinfo['constituency_name']; ?><br>
<strong>Skapad: </strong><?php echo general_helpers::show_date($propinfo['timestamp_created']); ?><br>
<strong>Upplagd av: </strong><a href="index.php?type=member&action=view&id=<?php echo $propinfo['user_id']; ?>"><?php echo $propinfo['user_full_name']; ?></a><br>

<strong>Beskrivning:</strong><br>
<?php echo nl2br($propinfo['description']); ?>
</p>

<?php if($user_allowed_to_vote) : ?>

	<p><a href="index.php?type=forum&action=show_posts&id=<?php echo $propinfo['forum_topic_id']; ?>">Länk till denna propositions forumdebatt</a></p>

	<div class="vote_box">

	<?php if($propinfo['status'] == "pending") : ?>

		Lägg din röst:<br>
	
		<form method="post" action="" class="yes-no">
			<input type="hidden" name="prop_id" value="<?php echo $propinfo['prop_id']; ?>">
			<input type="hidden" name="ballot" id="ballot" value="">


			<input type="submit" class="vote_button" id="green_vote" value="Stöder" onmousedown="return encrypt_prop_ballot('support')">
			<input type="submit" class="vote_button" id="red_vote" value="Förkastar" onmousedown="return encrypt_prop_ballot('reject')">
			<input type="submit" class="vote_button" id="yellow_vote" value="Avstår" onmousedown="return encrypt_prop_ballot('abstain')">
		</form>

	<?php endif; ?>

	</div>

	<?php if($_SESSION['delegate_id']) : ?>
		Du röstar som delegat.
	<?php else : ?>
		Du röstar som enskild användare.
	<?php endif; ?>

<?php endif; ?>


<script>
list_of_votes.map(function (vote){
	if(vote.user_code == sessionStorage.active_user_code){
		if(vote.support_type == "support"){
			document.getElementById("user_vote_box").innerHTML = "Du stödjer denna proposition.";
		}
		else if(vote.support_type == "reject"){
			document.getElementById("user_vote_box").innerHTML = "Du förkastar denna proposition.";
		}
		else if(vote.support_type == "abstain"){
			document.getElementById("user_vote_box").innerHTML = "Du avstår att ha en åsikt om denna proposition.";
		}
		
		if(vote.delegate_id == null){
			document.getElementById("user_vote_box").innerHTML += "<br>Du har själv lagt denna röst.";
		}
		else{
			document.getElementById("user_vote_box").innerHTML += "<br>Din delegat <a href='index.php?type=vote&action=view_delegate&id=" + vote.delegate_id + "'>" + vote.delegate_name + "</a> har röstat åt dig.";
		}
	}
});
</script>