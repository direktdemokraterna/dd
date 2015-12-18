<?php
if(isset($_POST['vote_id'])){
	if($_GET['id'] == $_POST['vote_id']){
		$voteinfo = db_vote::get_vote_info($_POST['vote_id']);
		if($voteinfo['type'] == "prio-vote"){
			if(isset($_POST['alternative_title'])){
				if($_SESSION['delegate_id'])
					$check_delegate_constituency_access = db_constituency::check_delegate_constituency_access($_SESSION['delegate_id'], $voteinfo['constituency_id']);
				$ok = empty($check_delegate_constituency_access)
					? db_vote::add_alternative_by_user($_POST['vote_id'], $_POST['alternative_title'], $_POST['alternative_description'], $_SESSION['id'])
					: db_vote::add_alternative_by_delegate($_POST['vote_id'], $_POST['alternative_title'], $_POST['alternative_description'], $_SESSION['delegate_id']);
				if($ok)
					$_SESSION['report_message'] = _t("The alternative has been created.");
				else
					\Logic\util::report_error(_t("Soething went wrong. No alternative created."));
			}
		}
		elseif(db_vote::is_user_candidate_in_vote($_SESSION['id'], $_GET['id'])){
			$ok = db_vote::remove_candidate($_GET['id'], $_SESSION['id']);
			if($ok)
				$_SESSION['report_message'] = _t("Your candidacy has been withdrawn.");
		}
		else{
			$ok = db_vote::add_candidate($_GET['id'], $_SESSION['id'], $_POST['alternative_description']);
			if($ok)
				$_SESSION['report_message'] = _t("you are now a candidate in the election: ") . $voteinfo['title'] . ".";
		}
		if($ok)
			$redirect = "index.php?type=vote&action=view_vote&id=" . $_POST['vote_id'];
	}
}
?>