<?php
	if(isset($_POST['send'])){
		$user_id = db_user::get_user_id($_POST['recipient']);
		if($user_id){
			if(!empty($_POST['title']) && !empty($_POST['message_text'])){
				$ok = db_message::create_message($_SESSION['id'], $user_id, general_helpers::clean($_POST['title']), general_helpers::clean($_POST['message_text']));
				if($ok){
					$_SESSION['report_message'] = "Meddelandet har skickats";
					$redirect = "index.php?type=message&action=inbox";
				}
				else{
					$_SESSION['report_message'] = "Något gick fel. Inget meddelande skickat";
					$_SESSION['red_report_message'] = 1;
				}
			}
			else{
				$_SESSION['report_message'] = "Meddelanden måste ha både rubrik och text";
				$_SESSION['red_report_message'] = 1;
			}
		}
		else{
			$_SESSION['report_message'] = "Mottagaren kunde inte hittas";
			$_SESSION['red_report_message'] = 1;
		}
	}
?>