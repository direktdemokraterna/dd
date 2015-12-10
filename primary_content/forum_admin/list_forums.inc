<?php 
	$forums = db_forum_admin::list_forums(); 
	_h1(_t("Forums"));
	echo '<div class="list_of_links">';
	foreach($forums as $row) {
		_link($row['title'], 'forum_admin', 'edit_forum', 'id=' . $row['id']);
		_br();
	}
	echo '</div>';
?>