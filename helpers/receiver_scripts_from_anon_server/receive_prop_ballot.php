<?php

require("./../init.inc");

if(isset($_POST['user_code']) && isset($_POST['prop_id']) && isset($_POST['rsa']) && isset($_POST['aes'])){

	$ballot_decoded = crypt_helpers::decrypt_ballot($_POST['rsa'], $_POST['aes']);

	// Check that prop_id from anon server matches prop_id from client (check that anon server doesn't manipulate ballot info)
	if($ballot_decoded['prop_id'] == $_POST['prop_id']){
		// Check that ballot is valid
		if($ballot_decoded['support_type'] == "support" || $ballot_decoded['support_type'] == "reject" || $ballot_decoded['support_type'] == "abstain"){
			$ok = db_prop::register_prop_ballot($_POST['prop_id'], $_POST['user_code'], $ballot_decoded['support_type']);
			if($ok){
				echo "success";
			}
		}
		elseif($ballot_decoded['support_type'] == "cancel"){
			$ok = db_prop::cancel_ballot($_POST['prop_id'], $_POST['user_code']);
		}
		else{
			echo "fail - invalid ballot";
		}
	}

}