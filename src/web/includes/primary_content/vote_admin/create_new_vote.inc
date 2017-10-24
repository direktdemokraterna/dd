<?php
	__h1("Skapa ny omröstning");
	__open_form();
	\View\vote::make_vote_type_selector(null, 1);
	\View\vote::make_vote_time_type_selector(null, 2);
	\View\vote::make_constituency_selector(null, $_SESSION['id'], 3);
	__textfield("title", "Titel", 4);
	__textarea("description", "Beskrivning", 5);
	__label("Omröstningen avslutas", "year");
	\View\vote::make_vote_end_time_select(time() + STANDARD_VOTE_LENGTH); 
	__br();
	__p("Omröstningen avslutas för delegater efter halva omröstningstiden. I fall detta inte är lämpligt går det att ändra efter att omröstningen har skapats.");
	__submit_and_close("Skapa", null, null, 6);
?>