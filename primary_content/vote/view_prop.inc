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
?>

<h1>Proposition: <?php echo $propinfo['title']; ?></h1>

<div class="vote_result_box">
	<?php if($propinfo['status'] == "pending") : ?>
		Det är <?php echo $propinfo['number_of_supporters']; ?> medlem<?php if($propinfo['number_of_supporters'] != 1) echo "mar"; ?> som stöder denna proposition.<br>
		Nödvändigt antal stödjare för att den ska godkännas och gå vidare till omröstning är <?php echo ceil($propinfo['number_of_voters'] * PROP_TO_VOTE_SUPPORT); ?>.
	<?php elseif($propinfo['status'] == "affirmed") : ?>
		<?php $vote_id = db_vote::get_vote_id_from_prop_id($propinfo['prop_id']); ?>
		Den här propositionen har uppnått tillräckligt stöd för att gå vidare och bli omröstning. Omröstningen finns <a href="index.php?type=vote&action=view_vote&id=<?php echo $vote_id; ?>">här</a>.
	<?php endif; ?>
</div>

<div class="vote_result_box" id="user_vote_box">
	<?php 
		if(isset($delegate_ballot) && $delegate_ballot['support']) {
			echo isset($delegate_ballot['delegate_id'])
				? 'Du som delegat stöder denna proposition genom din delegat.'
				: 'Du som delegat stöder själv denna proposition.';
		}
	?>
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
<strong>Antal lagda röster: </strong><?php echo $number_of_ballots['total_number_of_ballots']; ?><br>
<strong>Varav personligt lagda röster: </strong><?php echo $number_of_ballots['number_of_direct_ballots']; ?><br>
<strong>Antal delegater som röstat: </strong><?php echo $number_of_ballots['number_of_delegate_ballots']; ?><br>

<strong>Beskrivning:</strong><br>
<?php echo \View\general::make_html_from_wiki_text($propinfo['description']); ?>
</p>

<?php if($number_of_ballots['number_of_delegate_ballots'] > 0) : ?>
	<div class="" id="delegate_votes_box">
		<a href="javascript:void(0)" onclick="show_delegate_votes('prop')">Se delegaters stöd-röster för denna proposition</a>
	</div>
<?php endif; ?>

<p><a href="index.php?type=vote&action=view_prop_ballots&id=<?php echo $_GET['id']; ?>">Se alla stöd-röster för denna proposition</a></p>

<?php if($user_allowed_to_vote) : ?>

	<p><a href="index.php?type=forum&action=show_posts&topic_id=<?php echo $propinfo['forum_topic_id']; ?>">Länk till denna propositions forumdebatt</a></p>

	<div class="vote_box">

	<?php if($propinfo['status'] == "pending") : ?>

		<form method="post" action="" class="yes-no">
			<input type="hidden" name="prop_id" value="<?php echo $propinfo['prop_id']; ?>">
			<input type="hidden" name="ballot" id="ballot" value="">
			<input type="submit" class="vote_button" style="display: none" id="green_vote" value="Stöd" onmousedown="return encrypt_prop_ballot(true)">
			<input type="submit" class="vote_button" style="display: none" title="Klicka för att sluta stödja" id="yellow_vote" value="Stöder" onmousedown="return encrypt_prop_ballot(false)">
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
document.getElementById("user_vote_box").innerHTML = "Klicka på \"Stöd\" om du vill stöda denna proposition";
list_of_votes.map(function (vote){
	if(vote.user_code == sessionStorage.active_user_code && !acting_as_delegate) {
		support = vote.support;
		document.getElementById("user_vote_box").innerHTML = support
			? (vote.delegate_id 
				? "<br>Du stödjer denna proposition genom din delegat <a href='index.php?type=vote&action=view_delegate&id=" + 
				vote.delegate_id + "'>" + vote.delegate_name + "</a>." 
				: "Du stöder denna proposition.") 
				+ " Klicka på \"Stöder\" för att sluta stöda propositionen."
			: "Du har dragit tillbaka ditt stöd för denna proposition.";
	}
});
$("#green_vote").css('display', (support ? 'none' : 'inline'));
$("#yellow_vote").css('display', (support ? 'inline' : 'none'));
</script>