<?php
require("./../../init.inc");
$data = crypt_helpers::get_signed_data_from_anon_server();
if(isset($data['active_user_code'])){
	$ok = db_prop::remove_prop_ballots($data['active_user_code']);
	echo $ok
		? "success"
		: "error when removing prop ballots for user_code: " . $data['active_user_code'] . ": " . $ok;
}