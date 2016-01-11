<?php
	$recipient = ""; 
	$title = ""; 
	$content = "";
	$reply_info = null;
	if(isset($_GET['reply']) && !isset($_POST['recipient']) && !isset($_POST['title']) && !isset($_POST['message_text'])){
		$reply_info = db_message::get_message($_GET['reply']);
		$recipient = $reply_info['sender_username'];
		$title = $reply_info['title'];
		$reply_short = _t("Re: ");
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
		\View\message::output_message($reply_info, false, false, _t("Reply to: "));
	}
	else 
		_h1(_t("Write message"));
	_open_form();
	_hidden("send", 1);
	$options = array("none" => _t("Select recipient"));
	$recipients = db_user::get_all_usernames_and_full_names();
	foreach($recipients as $row)
		$options[$row['username']] = $row['full_name'];
	\View\controls::output_labeled_selector("recipient", _t("Recipient"), $options, $recipient, 'tabindex="1"');
	\View\controls::output_textfield("title", _t("Caption"), 2, $title);
	\View\controls::output_textarea("message_text", _t("Message"), 3, $content);
	_submit_and_close(_t("Send"), null, null, 4);
?>
