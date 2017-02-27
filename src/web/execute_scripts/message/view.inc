<?php
	$message_array = Array($_POST['message_id']);
	if (isset($_POST['recipient_delete'])) {
		$deleted = db_message::delete_inbox($message_array, $_SESSION['id']);
		if($deleted) {
			$_SESSION['report_message'] = $deleted . " meddelanden raderade.";
			$redirect = "index.php?type=message&action=inbox";
		}
		else \Logic\util::report_error("Kunde inte radera meddelandet.");
	}
	else if (isset($_POST['sender_delete'])) {
		$deleted = db_message::delete_outbox($message_array, $_SESSION['id']);
		if($deleted) {
			$_SESSION['report_message'] = $deleted . " meddelanden raderade.";
			$redirect = "index.php?type=message&action=outbox";
		}
		else \Logic\util::report_error("Kunde inte radera meddelandet.");
	}
	else if (isset($_POST['cancel'])) {
		$cancelled = db_message::cancel($_POST['message_id'], $_SESSION['id']);
		if($cancelled>0) {
			$_SESSION['report_message'] = "Meddelandet har raderats och mottagaren hann aldrig läsa det";
			$redirect = "index.php?type=message&action=outbox";
		}
		else \Logic\util::report_error("Kunde inte radera meddelandet.");
	}
?>