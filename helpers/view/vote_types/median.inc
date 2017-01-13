<?php 
	if (\Logic\vote::is_active_vote($voteinfo['status'])) {
		__t("Cast your vote:");
		__br();
		__open_form("yes-no");
		__hidden("vote_id", $voteinfo['id']);
		__hidden("ballot");
		echo '<div class="vote-buttons median-vote">';
		echo '<div class="median-vote-input-wrapper">';
		__label(_t("Your choosen value: "), "median_value");		
		echo '<input type="text" name="median_value" id="median_value" value="' . (!empty($delegate_ballot) && is_numeric($delegate_ballot['ballot']) ? $delegate_ballot['ballot'] : '') . '" oninput="validateMedianValue(\'median_value\', \'submit_vote\');" onpropertychange="this.oninput();">';
		echo '</div>';
		// echo '<input id="submit_vote" class="vote_button" id="green_vote" type="submit" value="' . _t("Vote") . '" onmousedown="return encrypt_median_ballot()">';
		echo '<button id="submit_vote" class="vote_button blue_vote" id="green_vote" type="submit" value="' . _t("Vote") . '" onmousedown="return encrypt_median_ballot()">' . _t("Vote") . '</button>';
		// echo '<div class="median-vote-divider"></div>';
		// echo '<input type="submit" class="vote_button" id="yellow_vote" value="' . _t("Abstain") . '" onmousedown="return encrypt_median_ballot(\'abstain\')">';
		echo '<button type="submit" class="vote_button" id="yellow_vote" value="' . _t("Abstain") . '" onmousedown="return encrypt_median_ballot(\'abstain\')">' . _t("Abstain") . '</button>';
		// echo '<input type="submit" class="vote_button" id="white_vote" value="' . _t("Revoke ballot") . '" style="display: ' . (!empty($delegate_ballot) ? "block" : "none") . '" onmousedown="return encrypt_median_ballot(\'cancel\')">';
		echo '<button type="submit" class="vote_button" id="white_vote" value="' . _t("Revoke ballot") . '" style="display: ' . (!empty($delegate_ballot) ? "block" : "none") . '" onmousedown="return encrypt_median_ballot(\'cancel\')">' . _t("Revoke ballot") . '</button>';		
		echo '</div></form>';
	}
