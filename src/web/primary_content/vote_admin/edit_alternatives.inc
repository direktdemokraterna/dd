<?php 
	$voteinfo = db_vote::get_vote_info($_GET['id']); 
	$votes_alternatives = $voteinfo['type'] == "prio-vote" 
		? db_vote::get_alternatives_for_vote($voteinfo['id'])
		: db_vote::get_candidates_for_vote($voteinfo['id']);
	__h1("Ändra alternativ för omröstningen: " . $voteinfo['title']);

	__open_form();
	__hidden("delete", 1);
	__hidden("vote_id", $_GET['id']);
	foreach($votes_alternatives as $row) {
		echo '<input type="checkbox" name="check_list[]" class="delete_checkbox" value="' . $row['id'] . '">';
		echo $row['title'];
		__space(1);
		echo '[';
		__link("Ändra", 'vote_admin', 'edit_alternative', 'id=' . $row['id']);
		echo ']';
		__br();
	}
	__br();
	echo '<input type="checkbox" name="checkall" onclick="checkAll(this, \'delete_checkbox\')">';
	echo "Markera alla";
	__br();
	__submit_and_close("Radera markerade");

	__h2("Lägg till alternativ till den här omröstningen");

	__open_form();
	__hidden("new_alternative", 1);
	__hidden("vote_id", $_GET['id']);
	if($voteinfo['type'] == "prio-vote")
		__textfield("title", "Titel");
	else 
		__textfield("username", "Användarnamn");
	__textarea("description", "Beskrivning");
	__submit_and_close("Lägg till");
?>
