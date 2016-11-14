<?php 
	if (\Logic\vote::is_active_vote($voteinfo['status'])) {
		__t("Cast your vote:");
		__br();
		__open_form("yes-no");
		__hidden("vote_id", $voteinfo['id']);
		__hidden("ballot");
		__label(_t("Your choosen value: "), "median_value");
		echo '<input type="text" name="median_value" id="median_value" value="' . (!empty($delegate_ballot) && is_numeric($delegate_ballot['ballot']) ? $delegate_ballot['ballot'] : '') . '" oninput="validateMedianValue(\'median_value\', \'submit_vote\');" onpropertychange="this.oninput();">';
		echo '<input id="submit_vote" class="vote_button" id="green_vote" type="submit" value="' . _t("Vote") . '" onmousedown="return encrypt_median_ballot()">';
		echo '<input type="submit" class="vote_button" id="yellow_vote" value="' . _t("Abstain") . '" onmousedown="return encrypt_median_ballot(\'abstain\')">';
		echo '<input type="submit" class="vote_button" id="white_vote" value="' . _t("Revoke ballot") . '" style="display: ' . (!empty($delegate_ballot) ? "inline-block" : "none") . '" onmousedown="return encrypt_median_ballot(\'cancel\')">';		
		echo '</form>';
	}
