<?php

require("init.inc");

if(isset($_POST['user_id']) && isset($_POST['vote_id']) && isset($_POST['ballot'])){

	$active_user_code = db_anon::get_active_user_code($_POST['user_id']);

	if($active_user_code){

		$ballot_decoded = crypt_helpers::decrypt_ballot($_POST['ballot']);

		if($ballot_decoded['user_id'] == $_POST['user_id']){
			$post_vars = Array("user_code" => $active_user_code, "vote_id" => $_POST['vote_id'], "rsa" => $ballot_decoded['rsa'], "aes" => $ballot_decoded['aes']);

			$reply = curl_to_main_server("receive_yes_no_ballot.php", $post_vars);

			if($reply == "success"){
				echo "success";
			}
			else{
				echo "failed - reply from receive_ballot: " . $reply;
			}
		}
		else{
			echo "failed - user_id mismatch";
		}

	}
	else{
		echo "failed - no user code";
	}

}