<?php
	if(isset($_POST['delete'])){
		if($_POST['vote_id'] == $_GET['id']){
			$deleted = db_vote_admin::delete_alternatives($_POST['check_list'], $_POST['vote_id']);
			$message = _t($deleted . " vote alternative deleted.");
		}
	}

	elseif(isset($_POST['new_alternative'])){
		if($_POST['vote_id'] == $_GET['id']){

			if(isset($_POST['username'])){

				$user_id = db_user::get_user_data_from_username($_POST['username']);
				if($user_id['id']){
					$constituency_id = db_constituency::get_vote_constituency_id($_POST['vote_id']);
					if(db_constituency::check_voter_constituency_access($user_id['id'], $constituency_id)){
						$ok = db_vote::add_candidate($_POST['vote_id'], $user_id['id'], $_POST['description']);
					}
					else{
						$_SESSION['report_message'] = _t("The user does not have access to this constituency. No vote alternative created.");
						$_SESSION['red_report_message'] = 1;
					}
				}
				else
					\Logic\util::report_error(_t("Wrong username. No vote alternative created.");
			}

			elseif(isset($_POST['title']))
				$ok = db_vote_admin::add_alternative_by_admin($_POST['vote_id'], $_POST['title'], $_POST['description']);
			if($ok)
				$_SESSION['report_message'] = _t("Vote alternative created.");
			else
				\Logic\util::report_error("Something went wrong. No vote alternative created.");
		}
	}