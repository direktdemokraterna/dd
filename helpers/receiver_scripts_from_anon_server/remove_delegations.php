<?php
require("./../../init.inc");
$data = crypt_helpers::get_signed_data_from_anon_server();
if(isset($data['active_user_code'])){
	$user_code = $data['active_user_code'];
	$constituency_id = $data['constituency_id'];
	$ok = db_delegate::remove_delegations_for($user_code, null, null, $constituency_id);
	echo $ok
		? "success"
		: "failed to remove delegations for user_code: " . $user_code . " and constituency: " . $constituency_id;
}