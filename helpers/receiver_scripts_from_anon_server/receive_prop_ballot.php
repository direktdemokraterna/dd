<?php

require("./../../init.inc");
$data = crypt_helpers::get_signed_data_from_anon_server();
if(isset($data['user_code']) && isset($data['prop_id']) && isset($data['rsa']) && isset($data['aes'])){
	$ballot_decoded = crypt_helpers::decrypt_ballot($data['rsa'], $data['aes']);
	// Check that prop_id from anon server matches prop_id from client (check that anon server doesn't manipulate ballot info)
	if($ballot_decoded['prop_id'] == $data['prop_id']){
		// Check that ballot is valid
		if($ballot_decoded['support'] === true || $ballot_decoded['support'] === false){
			$ok = db_prop::register_prop_ballot($data['prop_id'], $data['user_code'], $ballot_decoded['support']);
			echo $ok
				? "success"
				: "fail - something went wrong when registering the vote";
		}
		else echo "fail - invalid ballot: " . $ballot_decoded['support'];
	}
}