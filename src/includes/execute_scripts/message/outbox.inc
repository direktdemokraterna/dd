<?php
	if(isset($_POST['delete']) && isset($_POST['check_list'])){
		$deleted = db_message::delete_outbox($_POST['check_list'], $_SESSION['id']);
		if($deleted)
			$_SESSION['report_message'] = $deleted . " meddelanden raderade.";
	}
?>