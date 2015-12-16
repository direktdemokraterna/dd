<?php
	if(isset($_POST['send'])){
		$user_id = db_user::get_user_id($_POST['recipient']);
		if($user_id){
			if(!empty($_POST['title']) && !empty($_POST['message_text'])){
				$ok = db_message::create_message($_SESSION['id'], $user_id, general_helpers::clean($_POST['title']), general_helpers::clean($_POST['message_text']));
				if($ok){
					$_SESSION['report_message'] = _t("The message has been sent");
					$redirect = "index.php?type=message&action=inbox";
				}
				else{
					$_SESSION['report_message'] = _t("Something went wrong. No message sent.");
					$_SESSION['red_report_message'] = 1;
				}
			}
			else{
				$_SESSION['report_message'] = _t("Messages must have both caption and message-text.");
				$_SESSION['red_report_message'] = 1;
			}
		}
		else{
			$_SESSION['report_message'] = _t("Recipient not found.");
			$_SESSION['red_report_message'] = 1;
		}
	}
?>