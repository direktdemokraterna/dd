<?php
	if(isset($_POST['send'])){
		$user_id = db_user::get_user_id($_POST['recipient']);
		if(isset($user_id)){
			if(!empty($_POST['title']) && !empty($_POST['message_text'])){
				$ok = db_message::create_message($_SESSION['id'], $user_id, htmlspecialchars($_POST['title'], ENT_COMPAT,'ISO-8859-1', true), htmlspecialchars($_POST['message_text'], ENT_COMPAT,'ISO-8859-1', true));
				if($ok){
					$_SESSION['report_message'] = "Meddelandet har skickats";
					$redirect = "index.php?type=message&action=inbox";
				}
				else{
					$_SESSION['report_message'] = "Något gick fel, inget meddelande skickat.";
					$_SESSION['red_report_message'] = 1;
				}
			}
			else{
				$_SESSION['report_message'] = "Meddelanden måste ha både rubrik och meddelande-text.";
				$_SESSION['red_report_message'] = 1;
			}
		}
		else{
			$_SESSION['report_message'] = "Användarnamnet kunde inte hittas.";
			$_SESSION['red_report_message'] = 1;
		}
	}
?>