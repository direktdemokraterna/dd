<?php
	if(isset($_POST['send'])){
		$user_id = db_user::get_user_id($_POST['recipient']);
		if(isset($user_id)){
			if(!empty($_POST['title']) && !empty($_POST['message_text'])){
				$ok = db_message::create_message($_SESSION['id'], $user_id, htmlspecialchars($_POST['title']), htmlspecialchars($_POST['message_text']));
				if($ok){
					$message = "Meddelandet har skickats";
					db_helpers::insert_error_message($_SESSION['id'], $message);
					$redirect = "index.php?type=message&action=inbox";
				}
				else{
					$message = "Något gick fel, inget meddelande skickat.";
					db_helpers::insert_error_message($_SESSION['id'], $message, "red");
				}
			}
			else{
				$message = "Meddelanden måste ha både rubrik och meddelande-text.";
				db_helpers::insert_error_message($_SESSION['id'], $message, "red");
			}
		}
		else{
			$message = "Användarnamnet kunde inte hittas.";
			db_helpers::insert_error_message($_SESSION['id'], $message, "red");
		}
	}
?>