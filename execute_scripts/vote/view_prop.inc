<?php

if(isset($_POST['prop_id']) && isset($_POST['ballot'])){

	if($_POST['prop_id'] == $_GET['id']){

		$prop_info = db_prop::get_prop_info($_POST['prop_id']);

		if($_SESSION['acting_as_delegate'] && $prop_info['status'] == "pending"){

			// Handle vote as a delegate vote.

		}
		elseif($prop_info['status'] == "pending"){
			$check_user_access = db_constituency::check_user_constituency_access($_SESSION['id'], $prop_info['constituency_id']);

			if($check_user_access){
				$post_vars = Array("user_id" => $_SESSION['id'], "prop_id" => $_POST['prop_id'], "ballot" => $_POST['ballot']);
				$reply = crypt_helpers::curl_to_anon_server("anonymise_prop_ballot.php", $post_vars);
				if($reply == "success"){
					$_SESSION['report_message'] = "Din röst är registrerad.";
					}
				else{
					$_SESSION['report_message'] = "Något gick fel. Rösten registrerades inte.";
					$_SESSION['red_report_message'] = 1;
				}
				$redirect = $_SERVER['REQUEST_URI'];
			}
			else{
				die("ingen constituency access");
			}

		}

	}
	else{
		die("mismatch prop_id");
	}

}