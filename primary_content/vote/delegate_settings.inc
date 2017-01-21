<?php
	$is_delegate = db_delegate::is_user_delegate($_SESSION['id']);
	__h1("Delegatinställningar");
	if($is_delegate) {
		$delegate_settings = db_delegate::get_delegate_settings($_SESSION['id']);
		__open_form("standard-form");
		__h2("Rösta som delegat");
		__label("Agera som delegat", "acting_as_delegate");
		echo '<input type="checkbox" id="acting_as_delegate" name="acting_as_delegate"' 
			. ($_SESSION['delegate_id'] ? ' checked>' : '>');
		__br();
		__p("Om rutan ovan är markerad agerar du som delegat istället för som privatperson. Det innebär att du röstar för alla som har delegerat sin röst till dig i den frågan. Det innebär också att din röst är offentlig och kan ses av andra. Du kan bara rösta som delegat i de valkretsar som du angivit för din delegat nedan. I alla andra valkretsar röstar du som privatperson även om rutan ovan är markerad.");
		__submit_and_close("Ändra", "act_as_delegate");

		__h2("Presentation");
		\View\controls::output_text_editor(array(
			'name' => 'description'
			,'legend' => "Beskrivning av din delegat"
			,'target_id' => $delegate_settings['id']
			,'submit_text' => "Ändra"
			,'content' => $delegate_settings['description']));

		__h2("Valkretsar för din delegat");
		$constituencies = db_delegate::get_constituencies_for_user_and_delegate_activity($_SESSION['id'], $delegate_settings['id']);
		__p("Här kan du välja inom vilka valkretsar andra användare ska kunna delegera till dig.");
		__open_form("standard-form");
		echo '<ul class="checkbox-grid">';
		foreach($constituencies as $row) {
			echo '<li><input type="checkbox" name="constituencies[]" id="' . $row['constituency_title'] 
			. '" value="' . $row['constituency_id'] . '" ' . ($row['delegate_active'] ? ' checked>' : '>');
			__label($row['constituency_title'], $row['constituency_title']);
			echo '</li>';			
		}
		echo '</ul><div class="clear">';
		echo '</div><br>';
		__submit_and_close("Uppdatera", "change_constituencies");
		__open_form("standard-form");
		__br();
		__link("Visa delegat", "vote", "view_delegate", "id=" . $delegate_settings['id']);
		__h2("Ta bort delegat");
		__submit_and_close("Ta bort delegat", "delete", "Din delegat kommer att raderas fullständigt. Du kan också välja att tillfälligt avaktivera din delegat. Vill du fortsätta ändå?");
	}
	else {
		__open_form("standard-form");
		__p("Du är ännu inte registred som en delegat. Om du vill skapa en delegatprofil trycker du på knappen nedan. Även om du har skapat en delegatprofil behöver du inte rösta som delegat (så dina röster blir offentliga) eller låta andra användare delegera till dig.");
		__submit_and_close("Skapa delegat", "register_delegate");
	}
?>
