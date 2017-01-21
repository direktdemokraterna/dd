<?php 
	$categories = db_forum_admin::list_categories(); 
	__h1("Kategorier");
	echo '<div class="list_of_links">';
	foreach($categories as $row) {
		__link($row['title'], 'forum_admin', 'edit_category', 'id=' . $row['id']);
		__br();
	}
	echo '</div>';
?>
