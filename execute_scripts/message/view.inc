<?php
	$message_array = Array($_POST['message_id']);
	switch ($_POST['action']) {
		case 'recipient_delete':
			$deleted = db_message::delete_inbox($message_array, $_SESSION['id']);
			if($deleted)
				$_SESSION['report_message'] = _t($deleted . " message removed.");
			$redirect = "index.php?type=message&action=inbox";
			break;
		case 'sender_delete':
			$deleted = db_message::delete_outbox($message_array, $_SESSION['id']);
			if($deleted)
				$_SESSION['report_message'] = _t($deleted . " message removed.");
			$redirect = "index.php?type=message&action=outbox";
			break;
		case 'cancel':
			$cancelled = db_message::cancel($_GET['cancel'], $_SESSION['id']);
			if($cancelled>0)
				$_SESSION['report_message'] = _t("The message has been revoked and the recipient did never read it.");
			$redirect = "index.php?type=message&action=outbox";
			break;
	}
?>