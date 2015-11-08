<?php
	if(isset($_POST['delete'])){
		$deleted = db_message::delete_outbox($_POST['check_list'], $_SESSION['id']);
		if($deleted>0){
			if($deleted>1)
				$message = $deleted . " meddelanden raderade.";
			else
				$_SESSION['report_message'] = "1 meddelande raderat.";
		}
	}
?>