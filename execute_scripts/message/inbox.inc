<?php
	if(isset($_POST['delete'])){
		$deleted = db_message::delete_inbox($_POST['check_list'], $_SESSION['id']);
		if($deleted)
			$_SESSION['report_message'] = _t($deleted . " message deleted.");
	}

	if(isset($_GET['recipient_delete'])){
		$message_array = Array($_GET['recipient_delete']);
		$deleted = db_message::delete_inbox($message_array, $_SESSION['id']);
		if($deleted)
			$_SESSION['report_message'] = _t($deleted . " message deleted.");
	}

	if(isset($_GET['sender_delete'])){
		$message_array = Array($_GET['sender_delete']);
		$deleted = db_message::delete_outbox($message_array, $_SESSION['id']);
		if($deleted)
			$_SESSION['report_message'] = _t($deleted . " message deleted.");
	}

	if(isset($_GET['cancel'])){
		$cancelled = db_message::cancel($_GET['cancel'], $_SESSION['id']);
		if($cancelled>0)
			$_SESSION['report_message'] = _t("The message has been revoked and the recipient did never read it.");
	}
?>