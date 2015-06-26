<?php

if(isset($_POST['ballot'])){

	if($_SESSION['delegate_id']){

		$delegand_id = $_SESSION['delegate_id'];
		$ballot = json_decode($_POST['ballot'], true);
		$constituency_id = $ballot['constituency_id'];
		$delegate_id = $ballot['delegate_id'];

		$check_delegate_constituency_access = db_constituency::check_delegate_constituency_access($delegand_id, $constituency_id);

		$ok = db_delegate::register_delegation_ballot(null, $delegand_id, $delegate_id, $constituency_id);

		if($ok){
			$_SESSION['report_message'] = "Din delegats delegering är registrerad.";
			$redirect = $_SERVER['REQUEST_URI'];
		}
		else{
			$_SESSION['report_message'] = "Något gick fel. Ingen delegering registrerad.";
			$_SESSION['red_report_message'] = 1;
		}
	}

	else{
		$user_constituencies = db_constituency::get_constituencies_for_user($_SESSION['id']);
		$user_constituencies_array = Array();
		foreach($user_constituencies as $row){
			$user_constituencies_array[] = $row['id'];
		}
		$user_constituencies_serialized = serialize($user_constituencies_array);

		$post_vars = Array("user_id" => $_SESSION['id'], "user_constituencies" => $user_constituencies_serialized, "ballot" => $_POST['ballot']);
		$reply = crypt_helpers::curl_to_anon_server("anonymise_delegation_ballot.php", $post_vars);

		if($reply == "success"){
			$_SESSION['report_message'] = "Din delegering är registrerad.";
			$redirect = $_SERVER['REQUEST_URI'];
		}
		else{
			$_SESSION['report_message'] = "Något gick fel. Ingen delegering registrerad.";
			$_SESSION['red_report_message'] = 1;
		}

	}

}