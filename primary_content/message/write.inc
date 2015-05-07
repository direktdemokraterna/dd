<?php
	if(isset($_GET['id'])){
		$recipient_info = db_user::get_user_data($_GET['id']);
	}
?>

<form method="post" action="" class="send_message_form">
	<fieldset>
		<legend class="write_message">Skriv meddelande</legend>
		<input type="hidden" name="send" value="1">
		<label for "recipient">Mottagare</label>
		<input type="text" name="recipient" id="recipient" value="<?php if(isset($recipient_info['username'])) echo $recipient_info['username']; ?>" tabindex="1"> <?php if(isset($recipient_info['full_name'])) echo $recipient_info['full_name']; ?>
		<br>
		<label for "title">Rubrik</label>
		<input type="text" name="title" id="title" value="<?php if(isset($_POST['title'])) echo $_POST['title']; ?>" tabindex="2">
		<br>
		<label for "message_text">Meddelande</label>
		<textarea name="message_text" id="message_text" cols="60" rows="5" tabindex="3"><?php if(isset($_POST['message_text'])) echo $_POST['message_text']; ?></textarea>
		<br>
		<input type="submit" value="Skicka" tabindex="4">
	</fieldset>
</form>