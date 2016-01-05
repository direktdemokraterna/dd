<?php

require("./../../init.inc");
$data = crypt_helpers::get_signed_data_from_anon_server();
if(isset($data['user_code']) && isset($data['user_constituencies']) && isset($data['rsa']) && isset($data['aes'])){
	$ballot_decoded = crypt_helpers::decrypt_ballot($data['rsa'], $data['aes']);
	// Check that constituency_id from ballot is within user's constituency access (check that user don't delegate in constituency without access)
	if(in_array($ballot_decoded['constituency_id'], unserialize($data['user_constituencies']))){
		if(db_constituency::check_voter_constituency_access($ballot_decoded['delegate_id'], $ballot_decoded['constituency_id']) || $ballot_decoded['delegate_id'] == "null"){
			$ok = db_delegate::register_delegation_ballot($data['user_code'], null, $ballot_decoded['delegate_id'], $ballot_decoded['constituency_id']);
			echo $ok ? "success" : "database error";
		}
		else echo "fail - invalid ballot";
	}
	else echo "fail - constituency_id not in constituency_array";
}