<?php
require(dirname(__FILE__)."./../../init.inc");
db_vote_admin::delegate_end_votes();
$votes_past_end_time = db_vote_admin::get_votes_past_end_time();
foreach ($votes_past_end_time as $row) 
	db_vote_admin::end_vote($row['id']);
