<?php
	if(isset($_POST['register_delegate'])){
		$ok = db_delegate::create_delegate($_SESSION['id']);
		if($ok) {
			$_SESSION['delegate_id'] = db_delegate::get_delegate_id_from_user_id($_SESSION['id']);
			$_SESSION['report_message'] = "Din användare är nu delegat.";
		}
		else
			\Logic\util::report_error("Något gick fel.");
	}
	elseif(isset($_POST['delete'])){
		$ok = \Logic\delegate::delete_delegate_for_user($_SESSION['id']);
		if($ok) {
			$_SESSION['delegate_id'] = 0;
			$_SESSION['report_message'] = "Din delegat har tagits bort.";
		}
		else
			\Logic\util::report_error("Något gick fel.");
	}
	elseif(isset($_POST['act_as_delegate'])){
		if(isset($_POST['acting_as_delegate'])){
			$delegate_activated = \Logic\delegate::act_as_delegate();
			if ($delegate_activated)
				$_SESSION['report_message'] = "Du röstar nu som delegat.";
		}
		else if ($_SESSION['delegate_id']){
			$delegate_deactivated = \Logic\delegate::act_as_individual();
			if ($delegate_deactivated)
				$_SESSION['report_message'] = "Du röstar nu som enskild individ.";
		}
	}
	elseif(isset($_POST['change_constituencies'])){
		$constituencies = isset($_POST['constituencies']) ? $_POST['constituencies'] : array();
		$constituencies_changed = \Logic\constituency::update_constituencies_for_delegate($constituencies, $_SESSION['id']);
		if($constituencies_changed)
			$_SESSION['report_message'] = "Valkretsar uppdaterade för din delegat.";
		else 
			$_SESSION['report_message'] = "Inga ändringar utförda.";
	}
	elseif(isset($_POST['description_content'])){
		$ok = db_delegate::update_delegate_description($_SESSION['id'], $_POST['description_content']);
		if($ok)
			$_SESSION['report_message'] = "Din delegats beskrivning har uppdaterats.";
		else
			\Logic\util::report_error("Något gick fel. Beskrivningen kunde inte uppdateras.");
	}
?>