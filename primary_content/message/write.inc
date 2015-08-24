<?php
	if(isset($_GET['reply']) && !isset($_POST['recipient']) && !isset($_POST['title']) && !isset($_POST['message_text'])){
		$reply_info = db_message::get_reply_message($_GET['reply']);
		$recipient = $reply_info['username']; 
		if(substr($reply_info['title'], 0, 3) == "Sv:"){
			$title = $reply_info['title']; 
		}
		else{
			$title = "Sv:" . $reply_info['title']; 
		}
		$content = ""; 
	}
	elseif(isset($_POST['recipient']) && isset($_POST['title']) && isset($_POST['message_text'])){
		$recipient = $_POST['recipient']; 
		$title = $_POST['title']; 
		$content = $_POST['message_text']; 
	}
	elseif(isset($_GET['id'])){
		$recipient = db_user::get_username($_GET['id']); 
		$title = ""; 
		$content = ""; 
	}
	else{
		$recipient = ""; 
		$title = ""; 
		$content = ""; 
	}
?>

<h1>Skriv meddelande</h1>
<form method="post" action="" class="standard-form">
	<input type="hidden" name="send" value="1">
	<label for "recipient">Mottagare</label>
	<select name="recipient" id="recipient" tabindex="1">
		<option value="">Välj mottagare</option>
		<?php 
			$recipients = db_user::get_all_usernames_and_full_names();
			foreach($recipients as $row){
				echo "<option value=\"" . $row['username'] . "\"";
				if($recipient == $row['username']) echo " selected";
				echo ">" . $row['full_name'] . "</option>";
			}
		?>
	</select>

	<br>
	<label for "title">Rubrik</label>
	<input type="text" name="title" id="title" value="<?php echo $title; ?>" tabindex="2">
	<br>
	<label for "message_text">Meddelande</label>
	<textarea name="message_text" id="message_text" cols="60" rows="5" tabindex="3"><?php echo $content; ?></textarea>
	<br>
	<input type="submit" value="Skicka" tabindex="4">
</form>