<?php

require("./../../init.inc");

if(isset($_POST['user_code'])){
	$ok = db_vote::remove_ballots($_POST['user_code']);
	echo $ok
		? "success"
		: "error when removing ballots for user_code: " . $_POST['user_code'] . ": " . $ok;
}