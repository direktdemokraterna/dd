<?php

require(dirname(__FILE__)."./../init.inc");

$old_props = db_prop::get_old_props();


foreach ($old_props as $row) {

	db_prop::reject_prop($row['id']);

}