<?php
	__h1(_t("Create new category"));
	__open_form();
	__textfield("title", _t("Name"), 1);
	__textarea("description", _t("Description"), 2);
	__br();
	__submit_and_close(_t("Create"), null, null, 3);
?>
