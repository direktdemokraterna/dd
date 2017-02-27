<?php 
	__h1("Delegater");
	$show_all_delegates = isset($_GET['show_all']) && $_GET['show_all'];
	$where_filter = array();
	$filter_values = array();
	$constituency_id = isset($_GET['county']) && $_GET['county'] 
		? $_GET['county'] 
		: (isset($_GET['region']) ? $_GET['region'] : 0);
	if ($constituency_id)
		$where_filter[] = "cd.constituency_id = '$constituency_id'";
	if (!$show_all_delegates) {
		$where_filter[] = "cv.voter_id = ?";
		$filter_values[] = $_SESSION['id'];
	}
	$delegate_count = db_delegate::get_delegates_for_user_constituencies_count($where_filter, $filter_values);
	\View\delegate::output_delegate_list_header();
	if ($delegate_count) {
		$page = isset($_GET['page']) ? $_GET['page'] : 1;
		$sort = isset($_GET['sort']) ? $_GET['sort'] : 1;
		$rows = \db_delegate::get_delegates_for_user_constituencies($_SESSION['id'], $page, $sort, $where_filter, $filter_values);
		\View\delegate::output_delegate_list($rows, $page, $delegate_count);		
	}
	else
		echo "Det finns inga " . ($show_all_delegates ? "" : "tillgängliga ") 
			. "delegater i de valda valkretsarna.";
?>
