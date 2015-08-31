<?php

if(isset($_POST['type'])){

	if($_POST['type']=="cancel_exclude"){
		$ok = db_workgroup::cancel_exclude($_POST['id'], $_POST['user'], $_SESSION['id']);
		if($ok){
			$_SESSION['report_message'] = "Ditt stöd för uteslutning har tagits tillbaka.";
		}
	}
	elseif($_POST['type']=="support_exclude"){
		$ok = db_workgroup::support_exclude($_POST['id'], $_POST['user'], $_SESSION['id']);
		$excluded = db_workgroup::calculate_exclusion($_POST['id'], $_POST['user']);
		if($excluded == "excluded"){
			$_SESSION['report_message'] = "Du har stött en uteslutning. Medlemmen i fråga är numera utesluten.";
		}
		elseif($excluded == "still member"){
			$_SESSION['report_message'] = "Du har stött en uteslutning. Medlemmen i fråga är fortfarande gruppmedlem.";
		}
	}
	elseif($_POST['type']=="cancel_support_candidate"){
		$ok = db_workgroup::cancel_support($_POST['id'], $_POST['user'], $_SESSION['id']);
		if($ok){
			$_SESSION['report_message'] = "Ditt stöd för medlemskap har tagits tillbaka.";
		}
	}
	elseif($_POST['type']=="support_candidate"){
		$ok = db_workgroup::support_membership($_POST['id'], $_POST['user'], $_SESSION['id']);
		$affirmed = db_workgroup::check_candidate_support($_POST['id'], $_POST['user']);
		if($affirmed == "new member"){
			$_SESSION['report_message'] = "Du har stött en kandidatur. Kandidaten är numera medlem.";
		}
		elseif($affirmed == "still candidate"){
			$_SESSION['report_message'] = "Du har stött en kandidatur. Kandidaten behöver fortfarande mer stöd.";
		}

	}
	elseif($_POST['type']=="submit_candidacy"){
		$ok = db_workgroup::submit_candidacy($_POST['id'], $_SESSION['id']);
		if($ok) $_SESSION['report_message'] = "Din medlemsansökan är registrerad.";
	}

	elseif($_POST['type']=="cancel_candidacy"){
		$ok = db_workgroup::cancel_candidacy($_POST['id'], $_SESSION['id']);
		if($ok) $_SESSION['report_message'] = "Din medlemsansökan är borttagen.";
	}

	elseif($_POST['type']=="support_workgroup"){
		$ok = db_workgroup::add_supporting_member($_POST['id'], $_SESSION['id']);
		if($ok){
			$created = db_workgroup::is_active($_POST['id']);
			if($created==1){
				$_SESSION['report_message'] = "Arbetsgruppen är nu aktiverad och du är upptagen som medlem.";
			}
			else{
				$_SESSION['report_message'] = "Din medlemsansökan har registrerats.";
			}
		} 
	}
	elseif($_POST['type']=="cancel_support_workgroup"){
		$ok = db_workgroup::remove_supporting_member($_POST['id'], $_SESSION['id']);
		if($ok) $_SESSION['report_message'] = "Du stödjer inte längre denna arbetsgrupps aktivering.";
	}

	elseif($_POST['type']=="cancel_membership"){
		$ok = db_workgroup::drop_member($_POST['id'], $_SESSION['id']);
		if($ok) $_SESSION['report_message'] = "Du är inte längre medlem i denna arbetsgrupp.";
	}

	if(!empty($_SESSION['report_message'])){
		$redirect = $_SERVER['REQUEST_URI'];
	}

}
	
?>