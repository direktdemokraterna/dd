<?php

if(isset($_POST['ballot'])){

	if($_SESSION['acting_as_delegate']){

		// Handle vote as a delegate vote.

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