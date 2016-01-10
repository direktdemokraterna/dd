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
		if ($user_is_recipient)
			_action('recipient_delete', array('message_id' => $message['id']))
		if($user_is_sender) {
			if($message['read_time'])
				_action('sender_delete', array('message_id' => $message['id']))
			else
				_action('cancel', array('message_id' => $message['id']))
		}
		echo '</form>';
	}
	else
		__("Message not found");
?>