<?php
	db_message::mark_read($_GET['id'], $_SESSION['id']);
	$message = db_message::get_message($_GET['id']);
	$user_is_sender = false;
	$user_is_recipient = false;
	if(isset($message)){
		if(($message['sender_id']==$_SESSION['id'] && $message['deleted_by_sender']==0))
			$user_is_sender = true;
		if(($message['recipient_id']==$_SESSION['id'] && $message['deleted_by_recipient']==0))
			$user_is_recipient = true;
	}
	if ($user_is_sender || $user_is_recipient) {
		\View\message::output_message($message, $user_is_sender, $user_is_recipient, "", true);
		if ($user_is_recipient) {
			_link(_t("Remove from received"), 'message', 'inbox', 'recipient_delete=' . $message['id']);
			_br();
		}
		if($user_is_sender) {
			if($message['read_time'])
				_link(_t("Delete from sent"), 'message', 'inbox', 'sender_delete=' . $message['id']);
			else
				_link(_t("Undo send"), 'message', 'inbox', 'cancel=' . $message['id']);
		}
	}
	else
		__("Message not found");
?>