<?php
	try {
		if(isset($_POST['action']))
			\Logic\vote::change_vote_property();
		else
			\Logic\vote::change_vote();
	}
	catch (Exception $ex) {
		$_SESSION['report_message'] = $ex->getMessage();
		$_SESSION['red_report_message'] = 1;		
	}
?>