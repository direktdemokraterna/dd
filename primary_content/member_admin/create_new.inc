<?php
	__h1(_t("Create new member"));
	__open_form();
	\View\member::output_edit_fields($_POST);
	__br();
	__submit_and_close(_t("Create"));
?>
