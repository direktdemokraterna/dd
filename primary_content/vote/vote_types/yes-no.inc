<?php 
	if(!$_SESSION['delegate_id'] && in_array($voteinfo['status'], array("active", "continuous", "del_ended")))
	{
		__("Cast your vote:");
		_br();
		_open_form("yes-no");
		_hidden("vote_id", $voteinfo['vote_id']);
		_hidden("ballot");
		echo '<input type="submit" class="vote_button" id="green_vote" value="' . _t("Yes") . '"" onmousedown="return encrypt_yes_no_ballot(\'yes\')">';
		echo '<input type="submit" class="vote_button" id="red_vote" value="' . _t("No") . '" onmousedown="return encrypt_yes_no_ballot(\'no\')">';
		echo '<input type="submit" class="vote_button" id="yellow_vote" value="' . _t("Abstain") . '" onmousedown="return encrypt_yes_no_ballot(\'abstain\')">';
		echo '<input type="submit" class="vote_button" id="white_vote" value="' . _t("Revoke ballot") . '" style="display: ' . (empty($delegate_ballot) ? 'none' : 'inline-block') . '" onmousedown="return encrypt_yes_no_ballot(\'cancel\')">';
		echo '</form>';
	}
?>