<?php
if (\Logic\vote::is_active_vote($voteinfo['status'])) {
    __t("Cast your vote:");
    __open_form("yes-no");
    __hidden("vote_id", $voteinfo['id']);
    __hidden("ballot");
	echo '<div class="vote-buttons">';
    echo '<input type="submit" class="vote_button" id="green_vote" value="' . _t("Yes") . '"" onmousedown="return encrypt_yes_no_ballot(\'yes\')">';
    echo '<input type="submit" class="vote_button" id="red_vote" value="' . _t("No") . '" onmousedown="return encrypt_yes_no_ballot(\'no\')">';
    echo '<input type="submit" class="vote_button" id="yellow_vote" value="' . _t("Abstain") . '" onmousedown="return encrypt_yes_no_ballot(\'abstain\')">';
    echo '<input type="submit" class="vote_button" id="white_vote" value="' . _t("Revoke ballot") . '" style="display: ' . (empty($delegate_ballot) ? 'none' : 'inline-block') . '" onmousedown="return encrypt_yes_no_ballot(\'cancel\')">';
    echo '</div></form>';
}
