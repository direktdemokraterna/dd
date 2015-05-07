<?php

		if($_SESSION['acting_as_delegate']){
			$delegate_id = db_delegate::get_delegate_id_from_user_id($_SESSION['id']);
			$check_delegate_constituency_access = db_constituency::check_delegate_constituency_access($delegate_id, $voteinfo['constituency_id']);
		}	

		if($check_delegate_constituency_access && ($voteinfo['status'] == "active" || $voteinfo['status'] == "continuous")){

			if(isset($_POST['yes'])) $ballot = "yes";
			elseif(isset($_POST['no'])) $ballot = "no";
			elseif(isset($_POST['abstain'])) $ballot = "abstain";

			$ok = db_delegate::register_yes_no_ballot($_POST['vote_id'], $delegate_id, $ballot);
			if($ok){
				$message = "Din delegats röst är registrerad.";
				db_helpers::insert_error_message($_SESSION['id'], $message);
				$redirect = $_SERVER['REQUEST_URI'];
			}

		}
		elseif($voteinfo['status'] == "active" || $voteinfo['status'] == "del_ended" || $voteinfo['status'] == "continuous"){
			$check_user_access = db_constituency::check_user_constituency_access($_SESSION['id'], $voteinfo['constituency_id']);

			if($check_user_access){
				$post_vars = Array("user_id" => $_SESSION['id'], "vote_id" => $_POST['vote_id'], "ballot" => $_POST['ballot']);
				$reply = crypt_helpers::curl_to_anon_server("anonymise_yes_no_ballot.php", $post_vars);
			}
			else{
				die("ingen constituency access");
			}

		}

?>