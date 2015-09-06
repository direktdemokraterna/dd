<h1>Medlemslista</h1>

<?php 
	if(isset($_GET['page'])) $page = $_GET['page']; else $page = 1;

	if($_GET['sort'] == "alphabetic") $order_by = "first_name asc";
	else $order_by = "last_activity_time desc";

	if($_GET['filter'] == "county") $where_filter = "county = '" . $_GET['county'] . "'";
	elseif($_GET['filter'] == "region") $where_filter = "region = '" . $_GET['region'] . "'";
	else $where_filter = "1=1";

	$result = db_user::get_all_users($page, LIST_ITEMS_PER_PAGE, $order_by, $where_filter);
	$result_counter = db_user::get_all_users_count($where_filter);
?>

<?php 
	$sort_alternatives = Array("Senast inloggad" => "last_login", "Alfabetisk" => "alphabetic");
general_helpers::make_list_header_with_region_county_filter($page, $result_counter, $sort_alternatives); 
?>



<div class="list_of_links">

<?php foreach($result as $row) : ?>
	<a href="index.php?type=member&action=view&id=<?php echo $row['id']; ?>"><?php echo $row['full_name']; ?></a><br>
<?php endforeach; ?>

</div>