<?php 
	__h1(_t("Delegates"));
	if(isset($_GET['page'])) $page = $_GET['page']; else $page = 1;
	if($_GET['sort'] == "alphabetic") $order_by = "title asc";
	elseif($_GET['sort'] == "age") $order_by = "timestamp_created asc";
	else $order_by = "title asc";

	$where_filter = array();
	$filter_values = array();
	$constituency_id = isset($_GET['county']) && $_GET['county'] 
		? $_GET['county'] 
		: (isset($_GET['region']) ? $_GET['region'] : 0);
	if ($constituency_id)
		$where_filter[] = "cd.constituency_id = '$constituency_id'";
	if (!(isset($_GET['show_outside']) && $_GET['show_outside'])) {
		$where_filter[] = "cv.voter_id = ?";
		$filter_values[] = $_SESSION['id'];
	}
	$result_counter = db_delegate::list_delegates_for_user_constituencies_count($where_filter, $filter_values);
	$sort_alternatives = Array("popularity" => _t("Popularity"), "age" => _t("Created", array('class' => 'adj')), "alphabetic" => _t("Alphabetic"));
	$rows = \db_delegate::list_delegates_for_user_constituencies($_SESSION['id'], $page, LIST_ITEMS_PER_PAGE, $order_by, $where_filter, $filter_values);
	\View\delegate::output_delegate_list_header($page, $result_counter, $sort_alternatives);
	\View\delegate::output_delegate_list($rows);
?>
