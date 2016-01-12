<?php
	if(isset($_POST['delete']) && isset($_POST['check_list'])){
		$deleted = db_message::delete_inbox($_POST['check_list'], $_SESSION['id']);
		if($deleted)
			$_SESSION['report_message'] = _t($deleted . " message deleted.");
	}
?>