<?php

require(dirname(__FILE__)."./../../init.inc");

$changes_to_execute = db_workgroup::get_workgroup_election_changes_to_execute();

foreach($changes_to_execute as $row){
	if(isset($row['user_id_out'])){
		db_workgroup::drop_member($row['workgroup_id'], $row['user_id_out']);
	}
	if(isset($row['user_id_in'])){
		db_workgroup::add_member($row['workgroup_id'], $row['user_id_in']);
	}
	db_workgroup::delete_workgroup_election_changes($row['id']);
}

