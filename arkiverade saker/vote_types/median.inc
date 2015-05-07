<?php

		if($_SESSION['acting_as_delegate']){

			// Handle vote as a delegate vote.

		}
		else{
			$check_user_access = db_constituency::check_user_constituency_access($_SESSION['id'], $voteinfo['constituency_id']);

			if($check_user_access && $voteinfo['status'] != "ended" && $voteinfo['status'] != "finished"){
				$post_vars = Array("user_id" => $_SESSION['id'], "vote_id" => $_POST['vote_id'], "ballot" => $_POST['ballot']);
				$reply = crypt_helpers::curl_to_anon_server("anonymise_median_ballot.php", $post_vars);
			}
			else{
				die("ingen constituency access");
			}

		}

?>