<?php 
	$categories = db_forum_admin::list_categories(); 
	_h1(_t("Categories"));
	echo '<div class="list_of_links">';
	foreach($categories as $row) {
		_link($row['title'], 'forum_admin', 'edit_category', 'id=' . $row['id']);
		_br();
	}
	echo '</div>';
?>
