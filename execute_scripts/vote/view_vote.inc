<?php
	if(isset($_POST['vote_id']) && $_POST['vote_id'] == $_GET['id']){
		$voteinfo = db_vote::get_vote_info($_GET['id']); 
		if($_SESSION['delegate_id'])
			$delegate_constituency_access = db_constituency::check_voter_constituency_access($_SESSION['delegate_id'], $voteinfo['constituency_id']);
		if(!empty($delegate_constituency_access) 
			&& in_array($voteinfo['status'], array("active", "continuous"))){
			$ballot_decoded = json_decode($_POST['ballot'], true);
			if($ballot_decoded['ballot'] == "cancel")
				$ok = db_delegate::cancel_ballot($_POST['vote_id'], $_SESSION['delegate_id']);
			elseif(($voteinfo['type'] == "yes-no" && in_array($ballot_decoded['ballot'], array("abstain", "yes", "no"))) 
				|| ($voteinfo['type'] == "median" && is_numeric($ballot_decoded['ballot'])))
				$ok = db_delegate::register_ballot($_POST['vote_id'], $_SESSION['delegate_id'], $ballot_decoded['ballot']);
			elseif(in_array($voteinfo['type'], array("prio-vote", "candidate-election", "workgroup-election")) && is_array($ballot_decoded['ballot'])){
				$ballot = json_encode($ballot_decoded['ballot']);
				$ok = db_delegate::register_ballot($_POST['vote_id'], $_SESSION['delegate_id'], $ballot);
			}
			else
				$ok = false;
			if($ok)
				$_SESSION['report_message'] = _t("Your delegate's ballot is registered.");
			else
				\Logic\util::report_error(_t("Something went wrong. The ballot was not registered."));
		}
		elseif(in_array($voteinfo['status'], array("active", "del_ended", "continuous"))){
			$check_user_access = db_constituency::check_voter_constituency_access($_SESSION['id'], $voteinfo['constituency_id']);
			if($check_user_access){
				$post_vars = Array("user_id" => $_SESSION['id'], "vote_id" => $_POST['vote_id'], "ballot" => $_POST['ballot']);
				$reply = crypt_helpers::curl_to_anon_server("anonymise_ballot.php", $post_vars);
				if($reply == "success")
					$_SESSION['report_message'] = _t("Your ballot is registered.");
				else
					\Logic\util::report_error(_t("Something went wrong. The ballot was not registered."));
			}
			else
				die("No constituency access");
		}
		else
			\Logic\util::report_error(_t("Something went wrong. The ballot was not registered."));
	}
?>