<?php
	try {
		\Logic\vote::admin_create_vote();
		$redirect = "index.php?type=vote_admin&action=votelist";
	}
	catch (Exception $ex) {
		\Logic\util::report_error($ex->getMessage());
	}
?>