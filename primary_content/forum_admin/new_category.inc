<?php
	__h1("Skapa ny kategori");
	__open_form();
	__textfield("title", "Namn", 1);
	__textarea("description", "Beskrivning", 2);
	__br();
	__submit_and_close("Skapa", null, null, 3);
?>
