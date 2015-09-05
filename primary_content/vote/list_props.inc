<h1>Lagda propositioner</h1>

<?php 
	if(isset($_GET['page'])) $page = $_GET['page']; else $page = 1;
	if(isset($_GET['sort']) && $_GET['sort'] == "alphabetic"){
		$result = db_prop::list_active_props($page, LIST_ITEMS_PER_PAGE, "title asc");
	}
	else{
		$result = db_prop::list_active_props($page);
	}
	$result_counter = db_prop::list_active_props_count();
?>

<?php 
	$sort_alternatives = Array("Skapad" => "created", "Alfabetisk" => "alphabetic");
general_helpers::make_list_of_links_header($page, $result_counter, $sort_alternatives); 
?>



<div class="list_of_links">

<?php foreach($result as $row) : ?>
	<a href="index.php?type=vote&action=view_prop&id=<?php echo $row['id']; ?>"><?php echo $row['title']; ?></a><br>
<?php endforeach; ?>

</div>