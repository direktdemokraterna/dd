<?php
	try {
		\Logic\vote::admin_create_vote();
	}
	catch (Exception $ex) {
		\Logic\util::report_error($ex->getMessage());
	}
?>