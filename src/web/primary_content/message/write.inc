<?php
	$recipient = ""; 
	$title = ""; 
	$content = "";
	$reply_info = null;
	if(isset($_GET['reply']) && !isset($_POST['recipient']) && !isset($_POST['title']) && !isset($_POST['message_text'])){
		$reply_info = db_message::get_message($_GET['reply']);
		$recipient = $reply_info['sender_username'];
		$title = $reply_info['title'];
		$reply_short = "Sv: ";
		$title = (starts_with($title, $reply_short) ? '' : $reply_short) . $title; 
	}
	elseif(isset($_POST['recipient']) && isset($_POST['title']) && isset($_POST['message_text'])){
		$recipient = $_POST['recipient']; 
		$title = $_POST['title']; 
		$content = $_POST['message_text']; 
	}
	elseif(isset($_GET['id'])){
		$recipient = db_user::get_username($_GET['id']); 
	}
	if ($reply_info) {
		\View\message::output_message($reply_info, false, false, "Svara till: ");
	}
	else 
		__h1("Skriv meddelande");
	__open_form();
	__hidden("send", 1);
	$options = array("none" => "Välj mottagare");
	$recipients = db_user::get_all_usernames_and_full_names();
	foreach($recipients as $row)
		$options[$row['username']] = $row['full_name'];
	\View\controls::output_labeled_selector("recipient", "Mottagare", $options, $recipient, 'tabindex="1"');
	__textfield("title", "Rubrik", 2, $title);
	__textarea("message_text", "Meddelande", 3, $content);
	__submit_and_close("Skicka", null, null, 4);
?>
