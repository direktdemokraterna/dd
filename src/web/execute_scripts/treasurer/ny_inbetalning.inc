<?php

	if(!empty($_POST['amount']) && !empty($_POST['accounting_day'])){
		$comment_from_admin = general_helpers::clean($_POST['comment_from_admin']);
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

		if($_POST['type_of_transaction'] != "medlemsavgift" && $_POST['type_of_transaction'] != "donation" && $_POST['type_of_transaction'] != "annan inkomst"){
			$_SESSION['report_message'] = "Felaktig typ av inbetalning."; 
			$_SESSION['red_report_message'] = 1;
		}

		if(!isset($_SESSION['report_message'])){
			if($_POST['type_of_transaction'] == "medlemsavgift" && $user_id && $_POST['amount'] > MEMBERSHIP_FEE){
				$donation = $_POST['amount'] - MEMBERSHIP_FEE;
				$ok = db_treasurer::add_membership_fee($accounting_day, $comment_from_admin, $user_id);
				db_treasurer::add_entry("donation", $donation, $accounting_day, $comment_from_admin, $user_id);
			}
			elseif($_POST['type_of_transaction'] == "medlemsavgift" && $user_id && $_POST['amount'] < MEMBERSHIP_FEE){
				$ok = db_treasurer::add_entry("donation", $donation, $accounting_day, $comment_from_admin, $user_id);
			}
			elseif($_POST['type_of_transaction'] == "medlemsavgift" && $user_id && $_POST['amount'] == MEMBERSHIP_FEE){
				$ok = db_treasurer::add_membership_fee($accounting_day, $comment_from_admin, $user_id);
			}
			else{
				$ok = db_treasurer::add_entry($_POST['type_of_transaction'], $_POST['amount'], $accounting_day, $comment_from_admin, $user_id);
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
		$_SESSION['report_message'] = "Ett eller flera obligatoriska fält är inte ifyllda"; 
		$_SESSION['red_report_message'] = 1;
	}