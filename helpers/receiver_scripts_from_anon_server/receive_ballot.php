<?php

require("./../init.inc");

if(isset($_POST['user_code']) && isset($_POST['vote_id']) && isset($_POST['rsa']) && isset($_POST['aes'])){

	$ballot_decoded = crypt_helpers::decrypt_ballot($_POST['rsa'], $_POST['aes']);

	// Check that vote_id from anon server matches vote_id from client (check that anon server doesn't manipulate ballot info)
	if($ballot_decoded['vote_id'] == $_POST['vote_id']){

		$voteinfo = db_vote::get_vote_info($_POST['vote_id']);

		if($ballot_decoded['ballot'] == "cancel"){
			$ok = db_vote::cancel_ballot($_POST['vote_id'], $_POST['user_code']);
		}
		elseif($ballot_decoded['ballot'] == "abstain" || (($ballot_decoded['ballot'] == "yes" || $ballot_decoded['ballot'] == "no") && $voteinfo['type'] == "yes-no") || (is_numeric($ballot_decoded['ballot']) && $voteinfo['type'] == "median")){
			$ok = db_vote::insert_ballot($_POST['vote_id'], $ballot_decoded['ballot'], $_POST['user_code']);
		}
		elseif(($voteinfo['type'] == "prio-vote" || $voteinfo['type'] == "candidate-election" || $voteinfo['type'] == "workgroup-election") && is_array($ballot_decoded['ballot'])){
			$ballot = json_encode($ballot_decoded['ballot']);
			$ok = db_vote::insert_ballot($_POST['vote_id'], $ballot, $_POST['user_code']);
		}
		else{
			echo "fail - invalid ballot";
		}

		if($ok){
			echo "success";
		}

	}

}