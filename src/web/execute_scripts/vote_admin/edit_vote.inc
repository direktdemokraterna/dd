<?php
	try {
		if(isset($_POST['action']))
			\Logic\vote::change_vote_property();
		else
			\Logic\vote::change_vote();
	}
	catch (Exception $ex) {
		\Logic\util::report_error($ex->getMessage());
	}
?>