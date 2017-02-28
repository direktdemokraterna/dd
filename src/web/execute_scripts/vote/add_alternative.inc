<?php
if(isset($_POST['vote_id'])){
	if($_GET['id'] == $_POST['vote_id']){
		$voteinfo = db_vote::get_vote_info($_POST['vote_id']);
		if($voteinfo['type'] == "prio-vote"){
			if(isset($_POST['alternative_title'])){
				$ok = db_vote::add_alternative_by_voter($_POST['vote_id']
					, $_POST['alternative_title'], $_POST['alternative_description']
					, $_SESSION['delegate_id'] ? $_SESSION['delegate_id'] : $_SESSION['id']);
				if($ok)
					$_SESSION['report_message'] = "Alternativet har skapats.";
				else
					\Logic\util::report_error("Något gick fel. Inget alternativ skapat.");
			}
		}
		elseif(db_vote::is_user_candidate_in_vote($_SESSION['id'], $_GET['id'])){
			$ok = db_vote::remove_candidate($_GET['id'], $_SESSION['id']);
			if($ok)
				$_SESSION['report_message'] = "Din kandidatur har dragits tillbaka.";
		}
		else{
			$ok = db_vote::add_candidate($_GET['id'], $_SESSION['id'], $_POST['alternative_description']);
			if($ok)
				$_SESSION['report_message'] = "Du är nu en kandidat i omröstningen: " . $voteinfo['title'] . ".";
		}
		if($ok)
			$redirect = "index.php?type=vote&action=view_vote&id=" . $_POST['vote_id'];
	}
}
?>