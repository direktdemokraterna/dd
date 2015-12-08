<?php
	db_message::mark_read($_GET['id'], $_SESSION['id']);
	$message = db_message::get_message($_GET['id']);
	if(isset($message)){
		if(($message['sender_id']==$_SESSION['id'] && $message['deleted_by_sender']==0))
			$user_type = "sender";
		elseif(($message['recipient_id']==$_SESSION['id'] && $message['deleted_by_recipient']==0))
			$user_type = "receiver";
		else
			__("Message not found");
	}
	else
		__("Message not found");
?>

<?php if(isset($user_type)) : ?>
	<h1><?php echo $message['title']; ?></h1>
	<p>
	<table class="message">
	<tr>
	<td class="message_box_left">
	<?php 
		if($user_type == "sender") {
			_strong(_t("Recipient: "));
			_link($message['recipient_name'], 'member', 'view', 'id=' . $message['recipient_id']);
			_br();
			_strong(_t("Sent: "));
			echo general_helpers::show_date($message['sent_time']);
			_br();
			_strong(_t("Read: ", array('class' => 'adj')));
			if($message['read_time'] == 0) 
				__("Unread"); 
			else echo general_helpers::show_date($message['read_time']);
			_br(2);
			if($message['read_time']==0)
				_link(_t("Undo send"), 'message', 'inbox', 'cancel=' . $message['id']);
			else
				_link(_t("Delete"), 'message', 'inbox', 'sender_delete=' . $message['id']);
		}
		else {
			_strong(_t("Sender: "));
			_link($message['sender_name'], 'member', 'view', 'id=' . $message['sender_id']);
			_br();
			_strong(_t("Sent: "));
			echo general_helpers::show_date($message['sent_time']);
			_br();
			_strong(_t("Read: ", array('class' => 'adj')));
			echo general_helpers::show_date($message['read_time']);
			_br(2);
			_link(_t("Remove"), 'message', 'inbox', 'recipient_delete=' . $message['id']);
			_br();
			_link(_t("Reply"), 'message', 'write', 'reply=' . $message['id']);
		}
	?>
	</td>
	<td>
		<?php echo \View\general::make_html_from_wiki_text($message['content']); ?>
	</td>
	</tr>
	</table>

<?php endif; ?>