<?php
	
	if(isset($_POST['vote_id'])){
		if($_POST['vote_id'] == $_GET['id']){

			$voteinfo = db_vote::get_vote_info($_GET['id']); 

			if($_SESSION['delegate_id']){
				$check_delegate_constituency_access = db_constituency::check_delegate_constituency_access($_SESSION['delegate_id'], $voteinfo['constituency_id']);
			}	

			if(!empty($check_delegate_constituency_access) && ($voteinfo['status'] == "active" || $voteinfo['status'] == "continuous")){

				$ballot_decoded = json_decode($_POST['ballot'], true);

				if($ballot_decoded['ballot'] == "cancel"){
					$ok = db_delegate::cancel_ballot($_POST['vote_id'], $_SESSION['delegate_id']);
				}
				elseif($ballot_decoded['ballot'] == "abstain" || (($ballot_decoded['ballot'] == "yes" || $ballot_decoded['ballot'] == "no") && $voteinfo['type'] == "yes-no") || (is_numeric($ballot_decoded['ballot']) && $voteinfo['type'] == "median")){
					$ok = db_delegate::register_ballot($_POST['vote_id'], $_SESSION['delegate_id'], $ballot_decoded['ballot']);
				}
				elseif(($voteinfo['type'] == "prio-vote" || $voteinfo['type'] == "candidate-election" || $voteinfo['type'] == "workgroup-election") && is_array($ballot_decoded['ballot'])){
					$ballot = json_encode($ballot_decoded['ballot']);
					$ok = db_delegate::register_ballot($_POST['vote_id'], $_SESSION['delegate_id'], $ballot);
				}
				else{
					$ok = false;
				}
			
				if($ok){
					$_SESSION['report_message'] = _t("Your delegate's ballot is registered.");
				}
				else{
					$_SESSION['report_message'] = _t("Something went wrong. The ballot was not registered.");
					$_SESSION['red_report_message'] = 1;
				}

			}
			elseif($voteinfo['status'] == "active" || $voteinfo['status'] == "del_ended" || $voteinfo['status'] == "continuous"){
				$check_user_access = db_constituency::check_user_constituency_access($_SESSION['id'], $voteinfo['constituency_id']);

				if($check_user_access){
					$post_vars = Array("user_id" => $_SESSION['id'], "vote_id" => $_POST['vote_id'], "ballot" => $_POST['ballot']);
					$reply = crypt_helpers::curl_to_anon_server("anonymise_ballot.php", $post_vars);
					if($reply == "success")
						$_SESSION['report_message'] = _t("Your ballot is registered.");
					else{
						$_SESSION['report_message'] = _t("Something went wrong. The ballot was not registered.");
						$_SESSION['red_report_message'] = 1;
					}
				}
				else
					die("No constituency access");
			}
			else{
				$_SESSION['report_message'] = _t("Something went wrong. The ballot was not registered.");
				$_SESSION['red_report_message'] = 1;
			}
			$redirect = $_SERVER['REQUEST_URI'];
		}
	}
?>