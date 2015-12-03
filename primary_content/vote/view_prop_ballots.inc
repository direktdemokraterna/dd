<?php
	$propinfo = db_prop::get_prop_info($_GET['id']); 
	$ballots = db_prop::get_prop_supporters($_GET['id']);
	_h1(_t("All support-ballots on proposition ") . $propinfo['title']);
	if(empty($ballots))
		__("No ballots cast");
	else {
		echo '<table class="responsive">';
		echo '<tr><th>' . _t("Voter") . '</th><th>' . _t("Ballot") 
		. '</th><th>' . _t("Delegate") . '</th><th>' . _t("Time of vote") . '</th></tr>';
		foreach ($ballots as $ballot){
			echo '<tr><td>';
			if($ballot['user_code'])
				__("User");
			else 
				_link($ballot['voter_is_delegate_name'], 'vote', 'view_delegate', 'id=' . $ballot['voter_is_delegate_id']);
			echo '</td><td>';
			echo ($ballot['support'] ? _t('Supports') : _t("Doesn't support"));
			echo '</td><td>';
			if($ballot['delegate_id'])
				_link($ballot['delegate_name'], 'vote', 'view_delegate', 'id=' . $ballot['delegate_id']);
			echo '</td><td>';
			echo general_helpers::show_date($ballot['time_ballot_placed']);
			echo '</td></tr>';
		}
		echo '</table>';
	}
?>
