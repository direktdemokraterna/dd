<?php

require("./../../init.inc");
$data = crypt_helpers::get_signed_data_from_anon_server();
if(isset($data['active_user_code'])){
	$ok = db_vote::remove_ballots($data['active_user_code']);
	if ($ok) {
		db_vote::remove_user_codes_from_closed_votes($data['passive_user_code1'],  $data['passive_user_code2'],  $_POST['passive_user_code3']);
		echo "success";
	}
	else echo "error when removing ballots for user_code: " . $data['user_code'] . ": " . $ok;
}