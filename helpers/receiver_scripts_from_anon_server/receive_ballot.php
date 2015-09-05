<?php

require("./../init.inc");

if(isset($_POST['user_code']) && isset($_POST['vote_id']) && isset($_POST['rsa']) && isset($_POST['aes'])){

	$ballot_decoded = crypt_helpers::decrypt_ballot($_POST['rsa'], $_POST['aes']);

	// Check that vote_id from anon server matches vote_id from client (check that anon server doesn't manipulate ballot info)
	if($ballot_decoded['vote_id'] == $_POST['vote_id']){

		$voteinfo = db_vote::get_vote_info($_POST['vote_id']);

		if($voteinfo['type'] == "yes-no"){
			// Check that ballot is valid
			if($ballot_decoded['alternative'] == "yes" || $ballot_decoded['alternative'] == "no" || $ballot_decoded['alternative'] == "abstain"){
				$ok = db_vote::register_yes_no_ballot($_POST['vote_id'], $_POST['user_code'], $ballot_decoded['alternative']);
				if($ok){
					echo "success";
				}
			}
			else{
				echo "fail - invalid ballot";
			}
		}

		elseif($voteinfo['type'] == "median"){
			// Check that ballot is valid
			if(is_numeric($ballot_decoded['value'])){
				$ok = db_vote::register_median_ballot($_POST['vote_id'], $_POST['user_code'], $ballot_decoded['value']);
				if($ok){
					echo "success";
				}
			}
			else{
				echo "fail - invalid ballot";
			}
		}

		elseif($voteinfo['type'] == "prio-vote" || $voteinfo['type'] == "candidate-election" || $voteinfo['type'] == "workgroup-election"){
			// Check that ballot is valid
			if(is_array($ballot_decoded['prio_ranking'])){
				$prio_ranking = json_encode($ballot_decoded['prio_ranking']);
				$ok = db_vote::register_prio_vote_ballot($_POST['vote_id'], $_POST['user_code'], $prio_ranking);
				if($voteinfo['type'] == "workgroup-election"){
					vote_helpers::workgroup_election_compare_result($_POST['vote_id']);
				}
				if($ok){
					echo "success";
				}
			}
			else{
				echo "fail - invalid ballot";
			}
		}

	}

}