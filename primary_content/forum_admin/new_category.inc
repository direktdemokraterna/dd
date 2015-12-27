<?php
	_h1(_t("Create new category"));
	_open_form();
	\View\general::make_textfield("title", _t("Name"), 1);
	\View\general::make_textarea("description", _t("Description"), 2);
	_br();
	_submit_and_close(_t("Create"), null, 3);
?>
