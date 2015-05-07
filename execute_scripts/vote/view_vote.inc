<?php
	
	if(isset($_POST['vote_id'])){
		if($_POST['vote_id'] == $_GET['id']){

			$voteinfo = db_vote::get_vote_info($_GET['id']); 

			if($_SESSION['acting_as_delegate']){
				$delegate_id = db_delegate::get_delegate_id_from_user_id($_SESSION['id']);
				$check_delegate_constituency_access = db_constituency::check_delegate_constituency_access($delegate_id, $voteinfo['constituency_id']);
			}	

			if(!empty($check_delegate_constituency_access) && ($voteinfo['status'] == "active" || $voteinfo['status'] == "continuous")){

				$ok = vote_helpers::register_delegate_ballot($_POST['vote_id'], $delegate_id, $_POST['ballot']);
				if($ok){
					$message = "Din delegats röst är registrerad.";
					db_helpers::insert_error_message($_SESSION['id'], $message);
				}
				else{
					$message = "Något gick fel. Rösten registrerades inte.";
					db_helpers::insert_error_message($_SESSION['id'], $message, "red");
				}

			}
			elseif($voteinfo['status'] == "active" || $voteinfo['status'] == "del_ended" || $voteinfo['status'] == "continuous"){
				$check_user_access = db_constituency::check_user_constituency_access($_SESSION['id'], $voteinfo['constituency_id']);

				if($check_user_access){
					$post_vars = Array("user_id" => $_SESSION['id'], "vote_id" => $_POST['vote_id'], "ballot" => $_POST['ballot']);
					$reply = crypt_helpers::curl_to_anon_server("anonymise_ballot.php", $post_vars);
					if($reply == "success"){
						$message = "Din röst är registrerad.";
						db_helpers::insert_error_message($_SESSION['id'], $message);
					}
					else{
						$message = "Något gick fel. Rösten registrerades inte.";
						db_helpers::insert_error_message($_SESSION['id'], $message, "red");
					}
				}
				else{
					die("ingen constituency access");
				}

			}
			else{
				$message = "Något gick fel. Rösten registrerades inte.";
				db_helpers::insert_error_message($_SESSION['id'], $message, "red");
			}

			$redirect = $_SERVER['REQUEST_URI'];

		}

	}
?>