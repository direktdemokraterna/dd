<?php 
	$voteinfo = db_vote::get_vote_info($_GET['id']); 
	$votes_alternatives = $voteinfo['type'] == "prio-vote" 
		? db_vote::get_alternatives_for_vote($voteinfo['id'])
		: db_vote::get_candidates_for_vote($voteinfo['id']);
	_h1(_t("Edit vote alternatives for the vote: " . $voteinfo['title']));

	_open_form();
	_hidden("delete", 1);
	_hidden("vote_id", $_GET['id']);
	foreach($votes_alternatives as $row) {
		echo '<input type="checkbox" name="check_list[]" class="delete_checkbox" value="' . $row['id'] . '">';
		echo $row['title'];
		_space(1);
		echo '[';
		_link(_t("Edit"), 'vote_admin', 'edit_alternative', 'id=' . $row['id']);
		echo ']';
		_br();
	}
	_br();
	echo '<input type="checkbox" name="checkall" onclick="checkAll(this, \'delete_checkbox\')">';
	__("Check all");
	_br();
	_submit_and_close(_t("Delete selected", array("form" => "plural")));

	_h2(_t("Add alternative to this vote"));

	_open_form();
	_hidden("new_alternative", 1);
	_hidden("vote_id", $_GET['id']);
	if($voteinfo['type'] == "prio-vote")
		\View\controls::make_textfield("title", _t("Title"));
	else 
		\View\controls::make_textfield("username", _t("Username"));
	\View\controls::make_textarea("description", _t("Description"));
	_submit_and_close(_t("Add"));
?>
