<?php

require("./../init.inc");

if(isset($_POST['user_code']) && isset($_POST['user_constituencies']) && isset($_POST['rsa']) && isset($_POST['aes'])){

	$ballot_decoded = crypt_helpers::decrypt_ballot($_POST['rsa'], $_POST['aes']);

	// Check that constituency_id from ballot is within user's constituency access (check that user don't delegate in constituency without access)
	if(in_array($ballot_decoded['constituency_id'], unserialize($_POST['user_constituencies']))){

		if(db_constituency::check_delegate_constituency_access($ballot_decoded['delegate_id'], $ballot_decoded['constituency_id']) || $ballot_decoded['delegate_id'] == "null"){
			$ok = db_delegate::register_delegation_ballot($_POST['user_code'], null, $ballot_decoded['delegate_id'], $ballot_decoded['constituency_id']);
			if($ok){
				echo "success";
			}
			else{
				echo "database error";
			}
		}
		else{
			echo "fail - invalid ballot";
		}
	}
	else{
		die($_POST['user_constituencies']);
		echo "fail - constituency_id not in constituency_array";
	}

}