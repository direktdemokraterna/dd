<?php
	db_message::mark_read($_GET['id'], $_SESSION['id']);
	$message = db_message::get_message($_GET['id']);
	if(isset($message)){
		if(($message['sender_id']==$_SESSION['id'] && $message['deleted_by_sender']==0)){
			$user_type = "sender";
		}
		elseif(($message['recipient_id']==$_SESSION['id'] && $message['deleted_by_recipient']==0)){
			$user_type = "receiver";
		}
		else{
			echo "Kan inte hitta meddelandet.";
		}
	}
	else{
		echo "Kan inte hitta meddelandet.";
	}
?>

<?php if(isset($user_type)) : ?>

	<h1><?php echo $message['title']; ?></h1>

	<p>
	<table class="message">
	<tr>
	<td class="message_box_left">
		<?php if($user_type == "sender") : ?>
			<strong>Mottagare: </strong><a href="index.php?type=member&action=view&id=<?php echo $message['recipient_id']; ?>"><?php echo $message['recipient_name']; ?></a><br>
			<strong>Skickat: </strong><?php echo general_helpers::show_date($message['sent_time']); ?><br>
			<strong>Läst: </strong><?php if($message['read_time'] == 0) echo "Oläst"; else echo general_helpers::show_date($message['read_time']); ?><br>
			<br>
			<?php if($message['read_time']==0) : ?>
				<a href="index.php?type=message&action=inbox&cancel=<?php echo $message['id']; ?>">Ångra skicka</a>
			<?php else : ?>
				<a href="index.php?type=message&action=inbox&sender_delete=<?php echo $message['id']; ?>">Radera</a>
			<?php endif; ?>
		<?php else : ?>
			<strong>Avsändare: </strong><a href="index.php?type=member&action=view&id=<?php echo $message['sender_id']; ?>"><?php echo $message['sender_name']; ?></a><br>
			<strong>Skickat: </strong><?php echo general_helpers::show_date($message['sent_time']); ?><br>
			<strong>Läst: </strong><?php echo general_helpers::show_date($message['read_time']); ?><br>
			<br>
			<a href="index.php?type=message&action=inbox&recipient_delete=<?php echo $message['id']; ?>">Radera</a><br>
			<a href="index.php?type=message&action=write&reply=<?php echo $message['id']; ?>">Svara</a>
		<?php endif; ?>
	</td>
	<td>
		<?php echo nl2br($message['content']); ?>
	</td>
	</tr>
	</table>

<?php endif; ?>