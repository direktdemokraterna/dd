<?php

require("/../init.inc");

if(isset($_POST['user_code']) && isset($_POST['vote_id']) && isset($_POST['rsa']) && isset($_POST['aes'])){

	$ballot_decoded = crypt_helpers::decrypt_ballot($_POST['rsa'], $_POST['aes']);

	// Check that vote_id from anon server matches vote_id from client (check that anon server doesn't manipulate ballot info)
	if($ballot_decoded['vote_id'] == $_POST['vote_id']){
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

}