<?php
	$delegate_info = db_delegate::get_delegate_info($_GET['id']);

	if(empty($delegate_info['description'])) $delegate_info['description'] = "Ingen beskrivning";

	if(isset($_GET['page'])) $page = $_GET['page']; else $page = 1;

	if(isset($_GET['filter'])) $where_filter = "constituency_id = " . (int)$_GET['filter'];
	else $where_filter = "1=1";

	$delegate_ballots = db_delegate::list_delegate_ballots($_GET['id'], $page, LIST_ITEMS_PER_PAGE_SHORT, $where_filter);
	$result_counter = db_delegate::list_delegate_ballots_count($_GET['id'], $where_filter);

?>

<h1>Delegat: <?php echo $delegate_info['title']; ?></h1>

<h2>Beskrivning</h2>

<p><?php echo $delegate_info['description']; ?></p>

<h2>Röstningsstatistik</h2>

<?php 
//	$sort_alternatives = Array("Skapad" => "created", "Alfabetisk" => "alphabetic");
//	general_helpers::make_list_of_link_menu($page, $result_counter, $sort_alternatives); 
?>

<table class="responsive">
<tr><th>Omröstning</th><th>Typ</th><th>Röst</th></tr>

<?php foreach($delegate_ballots as $row) : ?>
	<tr>
		<td><a href="index.php?type=vote&action=view_vote&id=<?php echo $row['vote_id']; ?>"><?php echo $row['title']; ?></a></td>
		<td><?php
			if($row['type'] == "yes-no") echo "Votering";
			elseif($row['type'] == "median") echo "Medianomröstning";
			elseif($row['type'] == "prio-vote") echo "Prioritetsomröstning";
			elseif($row['type'] == "candidate-election") echo "Personval";
			elseif($row['type'] == "budget") echo "Budgetomröstning";
		?></td>
		<td><?php
			if($row['type'] == "yes-no"){
				if($row['ballot_alternative'] == "yes") echo "Ja";
				elseif($row['ballot_alternative'] == "no") echo "Nej";
				elseif($row['ballot_alternative'] == "abstain") echo "Avstår";
			}
			elseif($row['type'] == "median") echo $row['median_value'];
			elseif($row['type'] == "prio-vote") vote_helpers::output_prio_vote_result(vote_helpers::make_result_array_of_json_prio_ranking($row['prio_ranking']));
			elseif($row['type'] == "candidate-election") vote_helpers::output_candidate_election_result(vote_helpers::make_result_array_of_json_prio_ranking($row['prio_ranking']));
			elseif($row['type'] == "budget") echo "";
		?></td>
	</tr>
<?php endforeach; ?>

</table>

<h2>Delegera din röst till <?php echo $delegate_info['title']; ?></h2>

<?php
	$user_constituencies = db_constituency::get_constituencies_for_user($_SESSION['id']);
?>

<?php foreach($user_constituencies as $row) : ?>

	<?php if(db_constituency::check_delegate_constituency_access($_GET['id'], $row['id'])) : ?>

		<strong><?php echo $row['name']; ?></strong><br>
		<span id="constituency<?php echo $row['id']; ?>">Du har ingen delegat i denna valkrets</span>

	<?php endif; ?>

<?php endforeach; ?>