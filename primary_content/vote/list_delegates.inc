<?php 
	_h1(_t("Delegates"));
	if(isset($_GET['page'])) $page = $_GET['page']; else $page = 1;
	if($_GET['sort'] == "alphabetic") $order_by = "title asc";
	elseif($_GET['sort'] == "age") $order_by = "timestamp_created asc";
	else $order_by = "title asc";
	$constituency_id = isset($_GET['county']) && $_GET['county'] 
		? $_GET['county'] 
		: (isset($_GET['region']) ? $_GET['region'] : 0);
	$where_filter = $constituency_id
		? "cd.constituency_id = '$constituency_id'"
		: "1=1";
	$result_counter = db_delegate::list_delegates_for_user_constituencies_count($_SESSION['id'], $where_filter);
	$sort_alternatives = Array("popularity" => _t("Popularity"), "age" => _t("Created", array('class' => 'adj')), "alphabetic" => _t("Alphabetic"));
	general_helpers::make_list_header_with_region_county_filter($page, $result_counter, $sort_alternatives); 
	echo '<div class="list_of_links">';
	$result = db_delegate::list_delegates_for_user_constituencies($_SESSION['id'], $page, LIST_ITEMS_PER_PAGE, $order_by, $where_filter);
	foreach($result as $row) {
		_link($row['title'], 'vote', 'view_delegate', 'id=' . $row['id']);
		_br();
	}
	echo '</div>';
?>
