<?php
	__h1("Skapa nytt forum");
	__open_form();
	__textfield("title", "Namn", 1);
	__textarea("description", "Beskrivning", 2, null
		, array('cols'=>60, 'rows'=>5));
	\View\forum::output_category_selector();
	$access_options = array(1 => "Tillgängligt för alla", 2 => "Begränsad behörighet");
	\View\controls::output_labeled_selector("access_type", "Forumbehörighet", $access_options);
	__br();
	__submit_and_close("Skapa");
?>
