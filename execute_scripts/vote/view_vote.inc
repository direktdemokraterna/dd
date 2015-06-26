<?php
	
	if(isset($_POST['vote_id'])){
		if($_POST['vote_id'] == $_GET['id']){

			$voteinfo = db_vote::get_vote_info($_GET['id']); 

			if($_SESSION['delegate_id']){
				$check_delegate_constituency_access = db_constituency::check_delegate_constituency_access($_SESSION['delegate_id'], $voteinfo['constituency_id']);
			}	

			if(!empty($check_delegate_constituency_access) && ($voteinfo['status'] == "active" || $voteinfo['status'] == "continuous")){

				$ok = vote_helpers::register_delegate_ballot($_POST['vote_id'], $_SESSION['delegate_id'], $_POST['ballot']);
				if($ok){
					$_SESSION['report_message'] = "Din delegats röst är registrerad.";
				}
				else{
					$_SESSION['report_message'] = "Något gick fel. Rösten registrerades inte.";
					$_SESSION['red_report_message'] = 1;
				}

			}
			elseif($voteinfo['status'] == "active" || $voteinfo['status'] == "del_ended" || $voteinfo['status'] == "continuous"){
				$check_user_access = db_constituency::check_user_constituency_access($_SESSION['id'], $voteinfo['constituency_id']);

				if($check_user_access){
					$post_vars = Array("user_id" => $_SESSION['id'], "vote_id" => $_POST['vote_id'], "ballot" => $_POST['ballot']);
					$reply = crypt_helpers::curl_to_anon_server("anonymise_ballot.php", $post_vars);
					if($reply == "success"){
						$_SESSION['report_message'] = "Din röst är registrerad.";
						}
					else{
						$_SESSION['report_message'] = "Något gick fel. Rösten registrerades inte.";
						$_SESSION['red_report_message'] = 1;
					}
				}
				else{
					die("ingen constituency access");
				}

			}
			else{
				$_SESSION['report_message'] = "Något gick fel. Rösten registrerades inte.";
				$_SESSION['red_report_message'] = 1;
			}

			$redirect = $_SERVER['REQUEST_URI'];

		}

	}
?>