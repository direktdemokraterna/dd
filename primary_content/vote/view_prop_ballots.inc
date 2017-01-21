<?php
	$propinfo = db_prop::get_prop_info($_GET['id']); 
	$ballots = db_prop::get_prop_supporters($_GET['id']);
	__h1("Alla stöd till propositionen " . $propinfo['title']);
	\View\vote::list_ballots('proposition', $ballots, 'support');
?>
