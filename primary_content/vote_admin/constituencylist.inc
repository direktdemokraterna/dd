<?php
	__h1("Valkretsar");
	if(isset($_GET['page'])) $page = $_GET['page']; else $page = 1;
	if(isset($_GET['sort']) && $_GET['sort'] == "alphabetic")
		$result = db_constituency::get_all_constituencies($page, LIST_ITEMS_PER_PAGE, "title asc");
	else
		$result = db_constituency::get_all_constituencies($page);
	$result_counter = db_constituency::get_all_constituencies_count();
	$sort_alternatives = Array("created" => "Skapad", "alphabetic" => "Alfabetisk");
	general_helpers::make_list_of_links_header($page, $result_counter, $sort_alternatives);
	echo '<div class="list_of_links">';
	foreach($result as $row) {
		__link($row['name'], 'vote_admin', 'edit_constituency', 'id=' . $row['id']);
		__br();
	}
	echo '</div>';
?>
