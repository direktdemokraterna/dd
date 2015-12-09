<?php 
	_h1(_t("Members"));
	if(isset($_GET['page'])) $page = $_GET['page']; else $page = 1;
	if($_GET['sort'] == "alphabetic") $order_by = "first_name asc";
	else $order_by = "last_activity_time desc";
	$where_filters = array();
	if((isset($_GET['filter']) ? $_GET['filter'] == 'county' : isset($_GET['county'])) && $_GET['county']) 
		$where_filters[] = "county = '" . $_GET['county'] . "'";
	else if(isset($_GET['region']) && $_GET['region']) 
		$where_filters[] = "region = '" . $_GET['region'] . "'";
	if (!(isset($_GET['show_deleted']) && $_GET['show_deleted']))
		$where_filters[] = "deletion_time is null";
	$result = db_user::get_all_users($page, LIST_ITEMS_PER_PAGE, $order_by, $where_filters);
	$result_counter = db_user::get_all_users_count($where_filters);
	$sort_alternatives = Array("last_login" => _t("Last login"), "alphabetic" => _t("Alphabetic"));
	\View\member::output_member_list_header($page, $result_counter, $sort_alternatives); 
	echo '<div class="list_of_links">';
	foreach($result as $row) {
		$deleted_style = $row['deletion_time'] ? ' style="color: grey; font-style: italic"' : '';
		echo '<a href="index.php?type=member&action=view&id=' . $row['id'] . '"' . $deleted_style . '>' . 
		$row['full_name'] . '</a><br>';
	}
	echo '</div>';
?>
