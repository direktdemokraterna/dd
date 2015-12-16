<?php
	if(isset($_POST['register_delegate'])){
		$ok = db_delegate::create_delegate($_SESSION['id']);
		if($ok)
			$_SESSION['report_message'] = _t("Your user is now a delegate.");
		else
			\Logic\util::report_error(_t("Something went wrong."));
	}
	elseif(isset($_POST['delete'])){
		$ok = db_delegate::delete_delegate($_SESSION['id']);
		if($ok)
			$_SESSION['report_message'] = _t("Your delegate is removed.");
		else
			\Logic\util::report_error(_t("Something went wrong."));
	}
	elseif(isset($_POST['change_delegate'])){
		$report_messages = array();
		if(isset($_POST['acting_as_delegate'])){
			$delegate_activated = db_delegate::change_acting_as_delegate($_SESSION['id'], true);
			if ($delegate_activated){
				$_SESSION['delegate_id'] = db_delegate::get_delegate_id_from_user_id($_SESSION['id']);
				$report_messages[] = _t("You now vote as delegate.");
			}
		}
		else if ($_SESSION['delegate_id']){
			$delegate_unactivated = db_delegate::change_acting_as_delegate($_SESSION['id'], false);
			if ($delegate_unactivated){
				$_SESSION['delegate_id'] = 0;
				$report_messages[] = _t("You now vote as individual.");
			}
		}
		$constituencies_changed = empty($_POST['constituencies'])
			? db_delegate::remove_all_delegate_constituencies($_SESSION['id'])
			: db_delegate::update_delegate_constituencies($_POST['constituencies'], $_SESSION['id']);
		if($constituencies_changed)
			$report_messages[] = _t("constituency activity updated.");
		if ($report_messages)
			$_SESSION['report_message'] = implode(" ", $report_messages);
		else 
			$_SESSION['report_message'] = _t("No changes made.");
	}
?>