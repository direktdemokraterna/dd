<?php

require("./../../init.inc");
$data = crypt_helpers::get_signed_data_from_anon_server();
if(isset($data['active_user_code'])){
	$user_code = $data['active_user_code'];
	$constituency_id = $data['constituency_id'];
	$ok = db_vote::remove_ballots($user_code, $constituency_id);
	if ($ok) {
		db_vote::remove_user_codes_from_closed_votes($data['passive_user_code1']
			, $data['passive_user_code2'], $data['passive_user_code3'], $constituency_id);
		echo "success";
	}
	else echo "failed to remove ballots for user_code: " . $user_code . " and constituency: " . $constituency_id;
}