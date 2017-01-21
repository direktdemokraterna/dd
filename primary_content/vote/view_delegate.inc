<?php
	$acting_as_delegate = $_SESSION['delegate_id'] ? true : false;
	$voter_id = $acting_as_delegate ? $_SESSION['delegate_id'] : $_SESSION['id'];
	$delegate_id = $_GET['id'];

	$delegate_info = db_delegate::get_delegate_info($_GET['id']);
	$is_own_delegate = $delegate_info['user_id'] == $_SESSION['id'];
	if(empty($delegate_info['description'])) 
		$delegate_info['description'] = "Ingen beskrivning";
	$page = isset($_GET['page']) ? $_GET['page'] : 1;
	$where_filter = isset($_GET['filter']) 
		? "constituency_id = " . (int)$_GET['filter'] 
		: "1=1";
	$delegate_ballots = db_delegate::list_delegate_ballots($delegate_id, $page
		, LIST_ITEMS_PER_PAGE_SHORT, $where_filter);
	$result_counter = db_delegate::list_delegate_ballots_count($delegate_id, $where_filter);
	$shared_constituencies = vote_helpers::find_shared_constituencies($voter_id, $delegate_id);
	$list_of_delegations = db_delegate::get_delegations_for_multiple_constituencies($shared_constituencies
		, $_SESSION['delegate_id']);
?>

<script>
	var user_id = <?php echo json_encode($_SESSION['id']); ?>;
	var delegate_id = <?php echo json_encode($_GET['id']); ?>;
	var list_of_delegations = <?php echo json_encode($list_of_delegations); ?>;
	var acting_as_delegate = <?php echo $acting_as_delegate ? "true" : "false"; ?>;
</script>
<?php
	__h1(($is_own_delegate ? "Din delegat" : "Delegat") . ": " . $delegate_info['title']);
	__h2("Beskrivning");
	echo \Logic\text::make_html_from_wiki_text($delegate_info['description']);
	__h2("Omröstningshistorik");
?>

<?php if(empty($delegate_ballots)) : ?>
	Inga röster lagda
<?php else : ?>
	<table class="responsive">
	<tr><th>Omröstning</th><th>Typ</th><th>Röst</th></tr>
	<?php foreach($delegate_ballots as $row) : ?>
		<tr>
			<td><a href="index.php?type=vote&action=view_vote&id=<?php echo $row['vote_id']; ?>">
				<?php echo $row['title']; ?></a></td>
			<td><?php echo \View\vote::get_vote_type_description($row['type']); ?></td>
			<td><?php echo \View\vote::get_ballot_content($row['type'], $row['ballot']); ?></td>
		</tr>
	<?php endforeach; ?>
	</table>
<?php endif; ?>

<?php
	__h2(general_helpers::make_genitive($delegate_info['title']) . " delegeringar");
	$delegate_delegations = db_delegate::get_delegate_delegates($_GET['id']);
	if(empty($delegate_delegations)) {
		echo "Inga delegeringar";
		__br();		
	}
	else {
		echo $delegate_info['title'] . " har delegerat till:" . '<br>'; 
		foreach($delegate_delegations as $row)
		{
			__link($row['delegate_title'], 'vote', 'view_delegate', 'id=' . $row['delegate_id']); 
			echo " i valkretsen " . $row['constituency_title'] . '<br>'; 
		}		
	}
	if ($is_own_delegate) {
		__br();
		__link("Hantera delegat", "vote", "delegate_settings");		
	}
?>
<?php if ($shared_constituencies && $_SESSION['delegate_id'] != $delegate_id) : ?>
	<?php
		__br(2);
		echo '<hr>';
		echo '<script>';
		echo 'var dynamic_delegation_info_text = "Du har delegerat din rösträtt i denna valkrets till";';
		echo '</script>';
		__h2("Delegera din rösträtt" . ($acting_as_delegate ? " som delegat" : "") . " till " 
			. $delegate_info['title']);
		__open_form("prio-vote");
		__hidden("ballot");
		foreach($shared_constituencies as $row) {
			$constituency_id = $row['id'];
			echo '<div class="delegation_box">';
			echo "Valkrets: ";
			__strong($row['name']);
			__br();
			echo '<span id="constituency' . $constituency_id . '">Du har ingen delegat i denna valkrets</span>';
			__br(2);
			echo '<input id="delegate_in_' . $constituency_id . '" style="display: inline" type="submit" value="Delegera till ' . $delegate_info['title'] 
				. '" onmousedown="return encrypt_single_delegation(' . $constituency_id
					. ', ' . $_GET['id'] . ')">';
			echo '<input id="undelegate_in_' . $constituency_id . '" style="display: none" type="submit" value="Ta bort delegat" onmousedown="return encrypt_single_delegation(' . $constituency_id . ', 0)">';
			echo '</div>';
		}
		echo '</form>';
		echo '<script>';
		echo 'var dynamic_delegation_info_text = "Du har delegerat din röst i denna valkrets till";';
		echo '</script>';		
	?>
	<script>
	list_of_delegations.map(function (vote){
		if(acting_as_delegate || vote.user_code == sessionStorage.user_code) {
			var constituency_element = "constituency" + vote.constituency_id;
			document.getElementById(constituency_element).innerHTML = dynamic_delegation_info_text + " <a href='index.php?type=vote&action=view_delegate&id=" + vote.delegate_id + "'>" + vote.delegate_name + "</a>";
			var delegate_button = document.getElementById("delegate_in_" + vote.constituency_id);
			delegate_button.style.display = "none";
			var undelegate_button = document.getElementById("undelegate_in_" + vote.constituency_id);
			undelegate_button.style.display = "inline";
		}
	});
	</script>
<?php endif ?>
