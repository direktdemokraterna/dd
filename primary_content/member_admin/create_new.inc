<?php
	_h1(_t("Create new member"));
	_open_form();
	\View\member::output_edit_fields($_POST);
	_br();
	_submit_and_close(_t("Create"));
?>
