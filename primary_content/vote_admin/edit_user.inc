<?php 
	$userdata = db_user::get_user_data($_GET['id']);
	__h1(_link($userdata['first_name'] . " " . $userdata['last_name'], "member", "view", "id=" . $_GET['id']));
	__strong(_t("Constituency authorisations for this user"));
	echo '<form method="post" action=""><ul class="checkbox-grid">';
	$constituency_access = db_constituency::get_all_constituencies_and_if_voter_belongs($_GET['id']);
	foreach($constituency_access as $row) {
		$constituency_name = $row['constituency_name'];
		echo '<li>';
		echo '<input type="checkbox" name="check_list[]" id="' . $constituency_name . '" value="' 
			. $row['constituency_id'] . '"' . ($row['voter_access'] ? ' checked' : '') . '>';
		__label($constituency_name, $constituency_name);
		echo '</li>';
	}
	echo '</ul><div class="clear"></div><br>';
	__submit_and_close(_t('Change'));
?>
