<?php

	if(isset($_GET['page'])) $page = $_GET['page']; else $page = 1;

	if(isset($_GET['filter'])) $where_filter = "constituency_id = " . (int)$_GET['filter'];
	else $where_filter = "1=1";

	$vote_ballots = db_delegate::list_delegate_ballots($_GET['id'], $page, LIST_ITEMS_PER_PAGE_SHORT, $where_filter);
	$result_counter = db_delegate::list_delegate_ballots_count($_GET['id'], $where_filter);

	$constituencies = db_constituency::get_constituencies_for_user($_SESSION['id']);

	$list_of_delegations_from_db = db_delegate::get_delegations_for_multiple_constituencies($constituencies);
	$list_of_delegations = Array();
	foreach($list_of_delegations_from_db as $row){
		$list_of_delegations[] = Array("user_code" => $row['user_code'], "constituency_id" => $row['constituency_id'], "delegate_id" => $row['delegate_id'], "delegate_name" => $row['delegate_name']);
	}

?>


<h1>R�stnings�versikt</h1>

<h2>R�stningshistorik</h2>

<table class="responsive">
<tr><th>Omr�stning</th><th>Typ</th><th>R�st</th><th>Delegat</th></tr>

<?php foreach($vote_ballots as $row) : ?>
	<tr>
		<td><a href="index.php?type=vote&action=view_vote&id=<?php echo $row['vote_id']; ?>"><?php echo $row['title']; ?></a></td>
		<td><?php
			if($row['type'] == "yes-no") echo "Votering";
			elseif($row['type'] == "median") echo "Medianomr�stning";
			elseif($row['type'] == "prio-vote") echo "Prioritetsomr�stning";
			elseif($row['type'] == "candidate-election") echo "Personval";
			elseif($row['type'] == "budget") echo "Budgetomr�stning";
		?></td>
		<td><?php
			if($row['type'] == "yes-no"){
				if($row['ballot_alternative'] == "yes") echo "Ja";
				elseif($row['ballot_alternative'] == "no") echo "Nej";
				elseif($row['ballot_alternative'] == "abstain") echo "Avst�r";
			}
			elseif($row['type'] == "median") echo $row['median_value'];
			elseif($row['type'] == "prio-vote") vote_helpers::calculate_and_output_prio_vote_result(vote_helpers::make_result_array_of_json_prio_ranking($row['prio_ranking']));
			elseif($row['type'] == "candidate-election") vote_helpers::calculate_and_output_candidate_election_result(vote_helpers::make_result_array_of_json_prio_ranking($row['prio_ranking']));
			elseif($row['type'] == "budget") echo "";
		?></td>
	</tr>
<?php endforeach; ?>

</table>

<h2><?php echo general_helpers::make_genitive($delegate_info['title']); ?> delegeringar</h2>

<?php
	$delegate_delegations = db_delegate::get_delegate_delegates($_GET['id']);
?>

<?php if(empty($delegate_delegations)) : ?>
	Inga delegeringar<br>
<?php else : ?>
	<?php foreach($delegate_delegations as $row) : ?>
		Valkrets <?php echo $row['constituency_title']; ?>: <?php echo $delegate_info['title']; ?> har delegerat till <a href="index.php?type=vote&action=view_delegate&id=<?php echo $row['delegate_id']; ?>"><?php echo $row['delegate_title']; ?></a><br>
	<?php endforeach; ?>
<?php endif; ?>

<h2>Delegera din r�st till <?php echo $delegate_info['title']; ?></h2>

<form method="post" action="" class="prio-vote">
	<input type="hidden" name="ballot" id="ballot" value="">

<?php foreach($constituencies as $row) : ?>

	<div class="delegation_box">
		Valkrets: <strong><?php echo $row['name']; ?></strong><br>
		<?php if($_SESSION['delegate_id']) : ?>
			<?php
				$delegates_delegate = db_delegate::get_delegates_delegate_for_constituency($_SESSION['delegate_id'], $row['id']);
			?>
		<?php else : ?>
			<span id="constituency<?php echo $row['id']; ?>">Du har ingen delegat i denna valkrets</span><br>
		<?php endif; ?>
		<br>
		<input type="submit" value="Delegera din r�st i valkretsen <?php echo $row['name']; ?> till <?php echo $delegate_info['title']; ?>" onmousedown="return encrypt_single_delegation(<?php echo $row['id']; ?>)">
	</div>

<?php endforeach; ?>

</form>




<script>
list_of_delegations.map(function (vote){
	if(vote.user_code == sessionStorage.active_user_code){
		var constituency_element = "constituency" + vote.constituency_id;
		document.getElementById(constituency_element).innerHTML = "Du har delegerat din r�st i denna valkrets till <a href='index.php?type=vote&action=view_delegate&id=" + vote.delegate_id + "'>" + vote.delegate_name + "</a>";
	}
});
</script>