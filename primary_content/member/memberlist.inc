<?php 
	__h1(_t("Members"));
	$page = isset($_GET['page']) ? $_GET['page'] : 1;
	$sort = isset($_GET['sort']) ? $_GET['sort'] : 0;
	$where_filters = array();
	$region_id = isset($_GET['region']) ? $_GET['region'] : 0;
	$county_id = isset($_GET['county']) ? $_GET['county'] : 0;
	if ($region_id)
		$where_filters[] = "u.region_id = '$region_id'";
	if ($county_id)
		$where_filters[] = "u.county_id = '$county_id'";
	if (!(isset($_GET['show_deleted']) && $_GET['show_deleted']))
		$where_filters[] = "u.deletion_time is null";
	if (!isset($_SESSION['is_member_admin']) || !isset($_SESSION['is_superadmin']))
		$where_filters[] = "u.activation_code is null";
	$members = db_user::get_all_users($page, LIST_ITEMS_PER_PAGE, $sort, $where_filters);
	$member_count = db_user::get_all_users_count($where_filters);
	$sort_alternatives = Array("last_login" => _t("Last login"), "alphabetic" => _t("Alphabetic"));
	\View\member::output_member_list_filter();
	\View\member::output_member_list($members, $page, $member_count);
?>
