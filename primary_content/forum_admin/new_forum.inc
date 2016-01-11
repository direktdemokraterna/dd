<?php
	_h1(_t("Create new forum"));
	_open_form();
	\View\controls::output_textfield("title", _t("Name"), 1);
	\View\controls::output_textarea("description", _t("Description"), 2, null
		, array('cols'=>60, 'rows'=>5));
	\View\forum::output_category_selector();
	$access_options = array(1 => _t("Available for all"), 2 => _t("Limited access"));
	\View\controls::output_labeled_selector("access_type", _t("Forum access"), $access_options);
	_br();
	_submit_and_close(_t("Create"));
?>
