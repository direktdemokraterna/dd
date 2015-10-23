<?php
	try {
		\Logic\vote::admin_create_vote();
	}
	catch (Exception $ex) {
		die($ex);
		$_SESSION['report_message'] = $ex->getMessage();
		$_SESSION['red_report_message'] = 1;		
	}
?>