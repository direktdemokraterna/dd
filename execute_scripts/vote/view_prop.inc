<?php
if(isset($_POST['prop_id']) && isset($_POST['ballot'])){
	if($_POST['prop_id'] == $_GET['id']){
		$prop_info = db_prop::get_prop_info($_POST['prop_id']);
		if($_SESSION['delegate_id'])
			$check_delegate_constituency_access = db_constituency::check_delegate_constituency_access($_SESSION['delegate_id'], $prop_info['constituency_id']);
		if(!empty($check_delegate_constituency_access) && $prop_info['status'] == "pending"){
			$ballot_decoded = json_decode($_POST['ballot'], true);
			$ok = db_delegate::register_prop_ballot($_POST['prop_id'], $_SESSION['delegate_id'], $ballot_decoded['support']);
			if($ok)
				$_SESSION['report_message'] = "Din delegats röst är registrerad.";
			else
				\Logic\util::report_error("Något gick fel. Rösten registrerades inte.");
		}
		elseif($prop_info['status'] == "pending"){
			$check_user_access = db_constituency::check_user_constituency_access($_SESSION['id'], $prop_info['constituency_id']);
			if($check_user_access){
				$post_vars = Array("user_id" => $_SESSION['id'], "prop_id" => $_POST['prop_id'], "ballot" => $_POST['ballot']);
				$reply = crypt_helpers::curl_to_anon_server("anonymise_prop_ballot.php", $post_vars);
				if($reply == "success")
					$_SESSION['report_message'] = "Din röst är registrerad.";
				else
					\Logic\util::report_error("Något gick fel. Rösten registrerades inte.");
			}
			else
				die("ingen constituency access");
		}
	}
	else
		die("mismatch prop_id");
}