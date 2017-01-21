<?php
	__h1("Skapa ny medlem");
	__open_form();
	\View\member::output_edit_fields($_POST);
	__br();
	__submit_and_close("Skapa");
?>
