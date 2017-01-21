<?php
	if(!empty($_POST['type']) && !empty($_POST['id'])){
		$check_event = db_calendar::get_event($_POST['id']);
		if(!empty($check_event['timestamp']) && $check_event['timestamp'] > time()){
			if($_POST['type'] == "participate"){
				$ok = db_calendar::participate($_POST['id'], $_SESSION['id']);
				if($ok)
					$_SESSION['report_message'] = "Du är anmäld till denna aktivitet";
			}
			elseif($_POST['type'] == "cancel_participate"){
				$ok = db_calendar::cancel_participate($_POST['id'], $_SESSION['id']);
				if($ok)
					$_SESSION['report_message'] = "Du är inte längre anmäld till denna aktivitet";
			}
		}
		else
			\Logic\util::report_error("Anmälningar är inte längre möjliga för denna aktivitet");
	}
?>	