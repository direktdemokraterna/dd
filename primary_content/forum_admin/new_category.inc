<?php
	__h1(_t("Create new category"));
	__open_form();
	\View\controls::output_textfield("title", _t("Name"), 1);
	\View\controls::output_textarea("description", _t("Description"), 2);
	__br();
	__submit_and_close(_t("Create"), null, null, 3);
?>
