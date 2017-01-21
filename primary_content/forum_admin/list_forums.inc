<?php 
	$forums = db_forum_admin::list_forums(); 
	__h1("Forum");
	echo '<div class="list_of_links">';
	foreach($forums as $row) {
		__link($row['title'], 'forum_admin', 'edit_forum', 'id=' . $row['id']);
		__br();
	}
	echo '</div>';
?>