<?php

require("./../../init.inc");

if(isset($_POST['user_code'])){
	$ok = db_prop::remove_prop_ballots($_POST['user_code']);
	echo $ok
		? "success"
		: "error when removing prop ballots for user_code: " . $_POST['user_code'] . ": " . $ok;
}