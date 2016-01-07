<?php
	$is_delegate = db_delegate::is_user_delegate($_SESSION['id']);
	if($is_delegate)
		$delegate_settings = db_delegate::get_delegate_settings($_SESSION['id']);
	_h1(_t("Delegate settings"));
	_open_form();
	if($is_delegate) {
		_h2(_t("Vote as delegate"));
		_label(_t("Act as delegate"), "acting_as_delegate");
		echo '<input type="checkbox" id="acting_as_delegate" name="acting_as_delegate"' 
			. ($_SESSION['delegate_id'] ? ' checked>' : '>');
		_br();
		_p(_t("If the box above is checked you act as delegate instead of as individual. This means that you vote for all those who have delegated their vote to you for the particular issue. It also means that your ballot is public and can be seen by others. You can only vote as delegate in those constituencies for which you have registerered your delegacy below. In all other constituencies you vote as individual even if the box above is checked."));
		_h2(_t("constituencies for your delegate"));
		$constituencies = db_delegate::get_constituencies_for_user_and_delegate_activity($_SESSION['id'], $delegate_settings['delegate_id']);
		_p(_t("Here you can choose in which constituencies other users shall be able to delegate to you."));
		echo '<ul class="checkbox-grid">';
		foreach($constituencies as $row) {
			echo '<li><input type="checkbox" name="constituencies[]" id="' . $row['constituency_title'] 
			. '" value="' . $row['constituency_id'] . '" ' . ($row['delegate_active'] ? ' checked>' : '>');
			_label($row['constituency_title'], $row['constituency_title']);
			echo '</li>';			
		}
		echo '</ul><div class="clear">';
		echo '</div><br><input type="submit" name="change_delegate" value="' 
			. _t("Update") . '">';
		echo '</form>';
		echo '<form method="post" action="" class="standard-form" onsubmit="return confirm(\''
			. _t("Your delegate will be completely deleted. You may also choose to temporarily deactivate your delegate. Do you still want to continue?") . '">';
		_h2(_t("Remove delegate"));
		echo '<input type="submit" name="delete" value="' . _t("Remove delegate") . '">';
	}
	else {
		_p(_t("You are not yet registred as a delegate. If you want to create a delegate profile you press the button below. Even if you have created a delegate profile you don't have to vote as delegate (so your ballots become public) or let other users delegate to you."));
		echo '<input type="submit" name="register_delegate" value="' . _t("Create delegate") . '">';
	}
	echo '</form>';
?>
