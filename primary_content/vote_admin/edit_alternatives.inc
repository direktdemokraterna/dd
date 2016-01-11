<?php 
	$voteinfo = db_vote::get_vote_info($_GET['id']); 
	$votes_alternatives = $voteinfo['type'] == "prio-vote" 
		? db_vote::get_alternatives_for_vote($voteinfo['id'])
		: db_vote::get_candidates_for_vote($voteinfo['id']);
	__h1(_t("Edit vote alternatives for the vote: " . $voteinfo['title']));

	__open_form();
	__hidden("delete", 1);
	__hidden("vote_id", $_GET['id']);
	foreach($votes_alternatives as $row) {
		echo '<input type="checkbox" name="check_list[]" class="delete_checkbox" value="' . $row['id'] . '">';
		echo $row['title'];
		__space(1);
		echo '[';
		__link(_t("Edit"), 'vote_admin', 'edit_alternative', 'id=' . $row['id']);
		echo ']';
		__br();
	}
	__br();
	echo '<input type="checkbox" name="checkall" onclick="checkAll(this, \'delete_checkbox\')">';
	__t("Check all");
	__br();
	__submit_and_close(_t("Delete selected", array("form" => "plural")));

	__h2(_t("Add alternative to this vote"));

	__open_form();
	__hidden("new_alternative", 1);
	__hidden("vote_id", $_GET['id']);
	if($voteinfo['type'] == "prio-vote")
		\View\controls::output_textfield("title", _t("Title"));
	else 
		\View\controls::output_textfield("username", _t("Username"));
	\View\controls::output_textarea("description", _t("Description"));
	__submit_and_close(_t("Add"));
?>
