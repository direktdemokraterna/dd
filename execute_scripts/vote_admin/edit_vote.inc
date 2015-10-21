<?php
	try {
		if(isset($_POST['update']))
			\Logic\vote::change_vote();
		elseif(isset($_POST['action']))
			\Logic\vote::change_vote_property();
	}
	catch (Exception $ex) {
		$_SESSION['report_message'] = $ex->getMessage();
		$_SESSION['red_report_message'] = 1;		
	}
?>