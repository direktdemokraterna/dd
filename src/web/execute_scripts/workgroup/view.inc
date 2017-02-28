<?php
if(isset($_POST['cancel_exclude'])){
	$ok = db_workgroup::cancel_exclude($_POST['id'], $_POST['user'], $_SESSION['id']);
	if($ok){
		$_SESSION['report_message'] = "Ditt stöd för uteslutning har tagits tillbaka.";
	}
}
else if(isset($_POST['support_exclude'])){
	$ok = db_workgroup::support_exclude($_POST['id'], $_POST['user'], $_SESSION['id']);
	$excluded = db_workgroup::calculate_exclusion($_POST['id'], $_POST['user']);
	if($excluded == "excluded"){
		$_SESSION['report_message'] = "Du har stött en uteslutning. Medlemmen är nu utesluten.";
	}
	elseif($excluded == "still member"){
		$_SESSION['report_message'] = "Du har stött en uteslutning. Medlemmen är fortfarande medlem i gruppen.";
	}
}
else if(isset($_POST['cancel_support_candidate'])){
	$ok = db_workgroup::cancel_support($_POST['id'], $_POST['user'], $_SESSION['id']);
	if($ok){
		$_SESSION['report_message'] = "Ditt stöd för medlemskap har tagits tillbaka.";
	}
}
else if(isset($_POST['support_candidate'])){
	$ok = db_workgroup::support_membership($_POST['id'], $_POST['user'], $_SESSION['id']);
	$affirmed = db_workgroup::check_candidate_support($_POST['id'], $_POST['user']);
	if($affirmed == "new member"){
		$_SESSION['report_message'] = "Du har stött en kandidat. Kandidaten är nu medlem i gruppen.";
	}
	elseif($affirmed == "still candidate"){
		$_SESSION['report_message'] = "Du har stött en kandidat. Kandidaten behöver fortfarande mer stöd för att bli medlem i gruppen.";
	}

}
else if(isset($_POST['submit_candidacy'])){
	$ok = db_workgroup::submit_candidacy($_POST['id'], $_SESSION['id']);
	if($ok) $_SESSION['report_message'] = "Din ansökan är registrerad.";
}
else if(isset($_POST['cancel_candidacy'])){
	$ok = db_workgroup::cancel_candidacy($_POST['id'], $_SESSION['id']);
	if($ok) $_SESSION['report_message'] = "Din ansökan har tagits bort.";
}
else if(isset($_POST['support_workgroup'])){
	$ok = db_workgroup::add_supporting_member($_POST['id'], $_SESSION['id']);
	if($ok){
		$created = db_workgroup::is_active($_POST['id']);
		if($created==1){
			$_SESSION['report_message'] = "Arbetsgruppen är nu aktiverad och du är medlem i den.";
		}
		else{
			$_SESSION['report_message'] = "Din ansökan om medlemskap är registrerad.";
		}
	} 
}
else if(isset($_POST['cancel_support_workgroup'])){
	$ok = db_workgroup::remove_supporting_member($_POST['id'], $_SESSION['id']);
	if($ok) $_SESSION['report_message'] = "Du stödjer inte längre att denna arbetsgrupp bildas.";
}
else if(isset($_POST['cancel_membership'])){
	$ok = db_workgroup::drop_member($_POST['id'], $_SESSION['id']);
	if($ok) $_SESSION['report_message'] = "Du är inte längre medlem i denna arbetsgrupp";
}	
?>