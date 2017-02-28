<?php

require("./../../init.inc");
$data = crypt_helpers::get_signed_data_from_anon_server();
if(isset($data['user_code'])){
	$user_code = $data['user_code'];
	$constituency_id = $data['constituency_id'];
	$ok = db_vote::remove_ballots($user_code, null, null, $constituency_id);
	echo $ok 
		? "success"
		: "failed to remove ballots for user_code: " . $user_code . " and constituency: " . $constituency_id;
}