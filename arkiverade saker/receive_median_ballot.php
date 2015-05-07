<?php

require("/../init.inc");

if(isset($_POST['user_code']) && isset($_POST['vote_id']) && isset($_POST['rsa']) && isset($_POST['aes'])){

	$ballot_decoded = crypt_helpers::decrypt_ballot($_POST['rsa'], $_POST['aes']);

	// Check that vote_id from anon server matches prop_id from client (check that anon server doesn't manipulate ballot info)
	if($ballot_decoded['vote_id'] == $_POST['vote_id']){
		// Check that ballot is valid
		$ballot_decoded['value'] = str_replace(",", ".", $ballot_decoded['value']);
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

}