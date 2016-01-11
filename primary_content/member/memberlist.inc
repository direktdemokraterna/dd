<?php 
	__h1(_t("Members"));
	if(isset($_GET['page'])) $page = $_GET['page']; else $page = 1;
	$order_by = $_GET['sort'] == "alphabetic"
		? "u.first_name asc"
		: "u.last_activity_time desc";
	$where_filters = array();
	$region_id = isset($_GET['region']) ? $_GET['region'] : 0;
	$county_id = isset($_GET['county']) ? $_GET['county'] : 0;
	if ($region_id)
		$where_filters[] = "u.region_id = '$region_id'";
	if ($county_id)
		$where_filters[] = "u.county_id = '$county_id'";
	if (!(isset($_GET['show_deleted']) && $_GET['show_deleted']))
		$where_filters[] = "u.deletion_time is null";
	$members = db_user::get_all_users($page, LIST_ITEMS_PER_PAGE, $order_by, $where_filters);
	$result_counter = db_user::get_all_users_count($where_filters);
	$sort_alternatives = Array("last_login" => _t("Last login"), "alphabetic" => _t("Alphabetic"));
	\View\member::output_member_list_header($page, $result_counter, $sort_alternatives);
	\View\member::output_member_list($members);
?>
