<?php
	$propinfo = db_prop::get_prop_info($_GET['id']); 
	$ballots = db_prop::get_prop_supporters($_GET['id']);
	_h1(_t("All support-ballots on proposition ") . $propinfo['title']);
	\View\vote::list_ballots('proposition', $ballots, 'support');
?>
