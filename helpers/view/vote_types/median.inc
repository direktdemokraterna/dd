<?php 
	if (\Logic\vote::is_active_vote($voteinfo['status'])) {
		echo "Lägg din röst:";
		__open_form("yes-no");
		__hidden("vote_id", $voteinfo['id']);
		__hidden("ballot");
		echo '<div class="vote-buttons median-vote">';
		echo '<div class="median-vote-input-wrapper">';
		__label("Välj ett värde: ", "median_value");		
		echo '<input type="text" name="median_value" id="median_value" value="' . (!empty($delegate_ballot) && is_numeric($delegate_ballot['ballot']) ? $delegate_ballot['ballot'] : '') . '" oninput="validateMedianValue(\'median_value\', \'submit_vote\');" onpropertychange="this.oninput();">';
		echo '</div>';
		// echo '<input id="submit_vote" class="vote_button" id="green_vote" type="submit" value="Rösta" onmousedown="return encrypt_median_ballot()">';
		echo '<button id="submit_vote" class="vote_button blue_vote" id="green_vote" type="submit" value="Rösta" onmousedown="return encrypt_median_ballot()">Rösta</button>';
		// echo '<div class="median-vote-divider"></div>';
		// echo '<input type="submit" class="vote_button" id="yellow_vote" value="Avstår" onmousedown="return encrypt_median_ballot(\'abstain\')">';
		echo '<button type="submit" class="vote_button" id="yellow_vote" value="Avstår" onmousedown="return encrypt_median_ballot(\'abstain\')">Avstår</button>';
		// echo '<input type="submit" class="vote_button" id="white_vote" value="Ångra röst" style="display: ' . (!empty($delegate_ballot) ? "block" : "none") . '" onmousedown="return encrypt_median_ballot(\'cancel\')">';
		echo '<button type="submit" class="vote_button" id="white_vote" value="Ångra röst" style="display: ' . (!empty($delegate_ballot) ? "block" : "none") . '" onmousedown="return encrypt_median_ballot(\'cancel\')">Ångra röst</button>';		
		echo '</div></form>';
	}
