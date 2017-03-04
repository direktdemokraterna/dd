<?php
	__h1("Skapa ny arbetsgrupp");
	__open_form();
	__textfield("title", "Namn", 1);
	__textfield("number_of_members", "Antal medlemmar", 2);
	__textarea("description", "Beskrivning", 3);
	__submit_and_close("Skapa", null, null, 4);
	__p("Här skapar du stängda arbetsgrupper, grupper vars medlemskap inte är öppna för alla. Samtidigt som du skapar en stängd arbetsgrupp skapas också en kontinuerlig omröstning genom vilken medlemmarna i denna grupp tillsätts.");
?>
