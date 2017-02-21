<?php
	__h1("Skapa ny medlem");
	__open_form();
	$tab_index = 1;
	\View\member::output_edit_fields($_POST, true, $tab_index);
	__br();
	__submit_and_close("Skapa", null, null, $tab_index++);
?>
