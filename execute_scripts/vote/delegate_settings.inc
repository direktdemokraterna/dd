<?php
	if(isset($_POST['register_delegate'])){
		$ok = db_delegate::create_delegate($_SESSION['id']);
		if($ok) {
			$_SESSION['delegate_id'] = db_delegate::get_delegate_id_from_user_id($_SESSION['id']);
			$_SESSION['report_message'] = _t("Your user is now a delegate.");
		}
		else
			\Logic\util::report_error(_t("Something went wrong."));
	}
	elseif(isset($_POST['delete'])){
		$ok = \Logic\delegate::delete_delegate_for_user($_SESSION['id']);
		if($ok) {
			$_SESSION['delegate_id'] = 0;
			$_SESSION['report_message'] = _t("Your delegate is removed.");			
		}
		else
			\Logic\util::report_error(_t("Something went wrong."));
	}
	elseif(isset($_POST['change_delegate'])){
		$report_messages = array();
		if(isset($_POST['acting_as_delegate'])){
			$delegate_activated = \Logic\delegate::act_as_delegate();
			if ($delegate_activated)
				$report_messages[] = _t("You now vote as delegate.");
		}
		else if ($_SESSION['delegate_id']){
			$delegate_deactivated = \Logic\delegate::act_as_individual();
			if ($delegate_deactivated)
				$report_messages[] = _t("You now vote as individual.");
		}
		$constituencies = isset($_POST['constituencies']) ? $_POST['constituencies'] : array();
		$constituencies_changed = \Logic\constituency::update_constituencies_for_delegate($constituencies, $_SESSION['id']);
		if($constituencies_changed)
			$report_messages[] = _t("Constituency activity updated.");
		if ($report_messages)
			$_SESSION['report_message'] = implode(" ", $report_messages);
		else 
			$_SESSION['report_message'] = _t("No changes made.");
	}
?>