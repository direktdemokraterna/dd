<?php

	if(!empty($_POST['amount']) && !empty($_POST['accounting_day'])){
		$comment_from_admin = general_helpers::clean($_POST['comment_from_admin']);
		$accounting_day = strtotime($_POST['accounting_day']);
		if(!$accounting_day){
			$_SESSION['report_message'] = "Bokföringsdatumet är inte rätt formaterat."; 
			$_SESSION['red_report_message'] = 1;
		}

		if(!is_numeric($_POST['amount'])){
			$_SESSION['report_message'] = "Felaktigt talformat i summan."; 
			$_SESSION['red_report_message'] = 1;
		}

		if($_POST['type_of_transaction'] !== "utbetalning"){
			$_SESSION['report_message'] = "Felaktig typ av utbetalning."; 
			$_SESSION['red_report_message'] = 1;
		}

		if(!$_SESSION['report_message']){
			$ok = db_treasurer::add_entry($_POST['type_of_transaction'], $_POST['amount'], $accounting_day, null, null, $comment_from_admin);
		}

		if($ok){
			$_SESSION['report_message'] = "Utbetalningen är bokförd"; 
		}
		else{
			$_SESSION['report_message'] = "Något gick fel, utbetalningen kunde inte bokföras"; 
			$_SESSION['red_report_message'] = 1;
		}
	}
	else{
		$_SESSION['report_message'] = "Ett eller flera obligatoriska fält är inte ifyllda"; 
		$_SESSION['red_report_message'] = 1;
	}