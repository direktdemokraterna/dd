<?php
	_h1(_t("Create new vote"));
	_open_form();
	\View\vote::make_vote_type_selector(null, 1);
	\View\vote::make_vote_time_type_selector(null, 2);
	\View\vote::make_constituency_selector(null, $_SESSION['id'], 3);
	\View\controls::output_textfield("title", _t("Title"), 4);
	\View\controls::output_textarea("description", _t("Description"), 5);
	_label(_t("The vote finishes"), "year");
	\View\vote::make_vote_end_time_select(time() + STANDARD_VOTE_LENGTH); 
	_br();
	_p(_t("The vote closes for delegates after half the vote time. In case this is not appropriate it is possible to change the delegate vote time after the vote has been created."));
	_submit_and_close(_t("Create"), null, null, 6);
?>