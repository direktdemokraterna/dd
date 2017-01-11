<?php

	if(!empty($_POST['amount']) && !empty($_POST['accounting_day'])){
		$comment_from_admin = general_helpers::clean($_POST['comment_from_admin']);
		$comment_from_bank = general_helpers::clean($_POST['comment_from_bank']);
		$accounting_day = strtotime($_POST['accounting_day']);
		if(!$accounting_day){
			$_SESSION['report_message'] = "Bokföringsdatumet är inte rätt formaterat."; 
			$_SESSION['red_report_message'] = 1;
		}

		if(empty($_POST['user_id'])){
			$user_id = null;
		}
		elseif(empty(db_user::get_username($_POST['user_id']))){
			$_SESSION['report_message'] = "Användaren finns inte."; 
			$_SESSION['red_report_message'] = 1;
		}
		else{
			$user_id = $_POST['user_id'];
		}

		if(!is_numeric($_POST['amount'])){
			$_SESSION['report_message'] = "Felaktigt talformat i summan."; 
			$_SESSION['red_report_message'] = 1;
		}

		if(!isset($_SESSION['report_message'])){
			if(!$user_id){
				$ok = db_treasurer::add_entry("inbetalning", $_POST['amount'], $accounting_day, $user_id, $comment_from_bank, $comment_from_admin);
			}
			else{
				$days_since_last_memebership_payed = db_treasurer::days_since_last_memebership_payed_for_user($user_id);
				if($_POST['amount']>=MEMBERSHIP_FEE && $days_since_last_memebership_payed>180){
					$ok = db_treasurer::add_membership_fee($accounting_day, $user_id, $comment_from_bank, $comment_from_admin);
					$remaining_amount = $_POST['amount']-MEMBERSHIP_FEE;
				}
				else{
					$ok = db_treasurer::add_entry("donation", $remaining_amount, $accounting_day, $user_id, $comment_from_bank, $comment_from_admin);
				}

				if(isset($remaining_amount) && $remaining_amount>0){
					db_treasurer::add_entry("donation", $remaining_amount, $accounting_day, $user_id, $comment_from_bank, $comment_from_admin);
				}
			}
		}

		if($ok){
			$_SESSION['report_message'] = "Inbetalningen är bokförd"; 
		}
		else{
			$_SESSION['report_message'] = "Något gick fel, inbetalningen kunde inte bokföras"; 
			$_SESSION['red_report_message'] = 1;
		}
	}
	else{
		$_SESSION['report_message'] = _t("One or more mandatory fields are not filled in."); 
		$_SESSION['red_report_message'] = 1;
	}