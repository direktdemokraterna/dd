<h1>Delegater</h1>

<?php 
	if(isset($_GET['page'])) $page = $_GET['page']; else $page = 1;

	if($_GET['sort'] == "alphabetic") $order_by = "title asc";
	elseif($_GET['sort'] == "age") $order_by = "timestamp_created asc";
	else $order_by = "title asc";

	if($_GET['filter'] == "constituency") $where_filter = "cu.constituency_id = '" . (int)$_GET['constituency'] . "'";
	elseif($_GET['filter'] == "region") $where_filter = "region = '" . $_GET['region'] . "'";
	else $where_filter = "1=1";

	$result = db_delegate::list_delegates_for_user_constituencies($_SESSION['id'], $page, LIST_ITEMS_PER_PAGE, $order_by, $where_filter);
	$result_counter = db_delegate::list_delegates_for_user_constituencies_count($_SESSION['id'], $where_filter);
?>

<?php 
	$sort_alternatives = Array("Popularitet" => "popularity", "Skapad" => "age", "Alfabetisk" => "alphabetic");
	general_helpers::make_list_of_link_menu($page, $result_counter, $sort_alternatives, "county_tegions"); 
?>



<div class="list_of_links">

<?php foreach($result as $row) : ?>
	<a href="index.php?type=vote&action=view_delegate&id=<?php echo $row['id']; ?>"><?php echo $row['title']; ?></a><br>
<?php endforeach; ?>

</div>