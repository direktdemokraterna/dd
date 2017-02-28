<?php

require("./../../init.inc");
$data = crypt_helpers::get_signed_data_from_anon_server();

if(isset($data['user_code']) && isset($data['vote_id']) && isset($data['rsa']) && isset($data['aes'])){
	$ballot_decoded = crypt_helpers::decrypt_ballot($data['rsa'], $data['aes']);
	// Check that vote_id from anon server matches vote_id from client (check that anon server doesn't manipulate ballot info)
	if($ballot_decoded['vote_id'] == $data['vote_id']){
		$voteinfo = db_vote::get_vote_info($data['vote_id']);
		if($ballot_decoded['ballot'] == "cancel")
			$ok = db_vote::cancel_ballot($data['vote_id'], $data['user_code']);
		elseif($ballot_decoded['ballot'] == "abstain" || (($ballot_decoded['ballot'] == "yes" || $ballot_decoded['ballot'] == "no") && $voteinfo['type'] == "yes-no") || (is_numeric($ballot_decoded['ballot']) && $voteinfo['type'] == "median"))
			$ok = db_vote::insert_ballot($data['vote_id'], $ballot_decoded['ballot'], $data['user_code']);
		elseif(($voteinfo['type'] == "prio-vote" || $voteinfo['type'] == "candidate-election" || $voteinfo['type'] == "workgroup-election") && is_array($ballot_decoded['ballot'])){
			$ballot = json_encode($ballot_decoded['ballot']);
			$ok = db_vote::insert_ballot($data['vote_id'], $ballot, $data['user_code']);
		}
		echo isset($ok) 
			? ($ok ? "success" : "fail - could not register ballot")
			: "fail - invalid ballot";
	}
}