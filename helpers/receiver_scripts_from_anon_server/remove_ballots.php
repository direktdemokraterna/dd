<?php

require("./../../init.inc");

if(isset($_POST['active_user_code'])){
	$ok = db_vote::remove_ballots($_POST['active_user_code']);
	if ($ok) {
		db_vote::remove_user_codes_from_closed_votes($_POST['passive_user_code1'],  $_POST['passive_user_code2'],  $_POST['passive_user_code3']);
		echo "success";
	}
	else echo "error when removing ballots for user_code: " . $_POST['user_code'] . ": " . $ok;
}