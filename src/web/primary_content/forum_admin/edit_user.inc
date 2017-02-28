<?php 
	$userdata = db_user::get_user_data($_GET['id']);
	__h1(\View\member::link($userdata));
	__strong("Forumbehörigheter för denna användare");
	__br();
	__open_form("");
	echo '<ul class="checkbox-grid">';
	$forum_access = db_forum_admin::get_all_forums_and_if_user_belongs($_GET['id']);
	foreach($forum_access as $row) {
		echo '<li><input type="checkbox" name="check_list[]" id="' . $row['forum_name'] 
			. '" value="' . $row['forum_id'] . '"' . ($row['user_access'] ? " checked>" : '>');
		__label($row['forum_name'], $row['forum_name']);
		echo '</li>';
	}
	echo '</ul><div class="clear"></div>';
	__br();
	__submit_and_close("Ändra");
?>
