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
		_h1($message['title']);
		echo '<p>';
		echo '<table class="message">';
		echo '<tr>';
		echo '<td class="message_box_left">';
		if($user_is_sender) {
			_strong(_t("Recipient: "));
			_link($message['recipient_name'], 'member', 'view', 'id=' . $message['recipient_id']);
			_br();
		}
		if($user_is_recipient) {
			_strong(_t("Sender: "));
			_link($message['sender_name'], 'member', 'view', 'id=' . $message['sender_id']);
			_br();
		}
		_strong(_t("Sent: "));
		echo general_helpers::show_date($message['sent_time']);
		_br();
		_strong(_t("Read: ", array('class' => 'adj')));
		if($message['read_time']) 
			echo general_helpers::show_date($message['read_time']);
		else 
			__("Unread"); 
		_br(2);
		if ($user_is_recipient) {
			_br(2);
			_link(_t("Reply"), 'message', 'write', 'reply=' . $message['id']);
			_br();
			echo _span('right', \View\general::generate_internal_link(_t("Remove from received"), 'message', 'inbox', 'recipient_delete=' . $message['id']));
		}
		if($user_is_sender) {
			_br();
			if($message['read_time'])
				echo _span('right', \View\general::generate_internal_link(_t("Delete from sent"), 'message', 'inbox', 'sender_delete=' . $message['id']));
			else
				echo _span('right', \View\general::generate_internal_link(_t("Undo send"), 'message', 'inbox', 'cancel=' . $message['id']));
		}
		echo '</td>';
		echo '<td>';
		echo \View\general::make_html_from_wiki_text($message['content']);
		echo '</td>';
		echo '</tr>';
		echo '</table>';
	}
	else
		__("Message not found");
?>