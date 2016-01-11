<?php 
	$voteinfo = db_vote::get_vote_info($_GET['id']); 
	_h1(_t("Edit vote: ") . $voteinfo['title']);
	_open_form();
	_hidden("vote_id", $voteinfo['id']);
	\View\vote::make_vote_type_selector($voteinfo['type']);
	\View\vote::make_constituency_selector($voteinfo['constituency_id'], $_SESSION['id'], 2); 
	\View\controls::output_textfield("title", _t("Title"), 3, $voteinfo); 
	\View\controls::output_textarea("description", _t("Description"), 4, $voteinfo);
	\View\vote::output_vote_status($voteinfo['status']); 
	\View\controls::output_textfield("forum_topic_id", _t("Forum topic-ID"), 5, $voteinfo); 
	_br();
	_label(_t("The vote finishes"), "year");
	\View\vote::make_vote_end_time_select($voteinfo['timestamp_ended']); 
	_br();
	_label(_t("The delegate vote finishes", array('class' => 'noun')), "delegate_year");
	\View\vote::make_vote_end_time_select($voteinfo['timestamp_delegate_ended'], 'delegate_');
	_br();
	_submit_and_close(_t("Update"));
?>
