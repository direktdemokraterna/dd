<h1>Valkretsar</h1>

<?php 
	if(isset($_GET['page'])) $page = $_GET['page']; else $page = 1;
	if(isset($_GET['sort']) && $_GET['sort'] == "alphabetic"){
		$result = db_constituency::get_all_constituencies($page, LIST_ITEMS_PER_PAGE, "title asc");
	}
	else{
		$result = db_constituency::get_all_constituencies($page);
	}
	$result_counter = db_constituency::get_all_constituencies_count();
?>

<?php 
	$sort_alternatives = Array("Skapad" => "created", "Alfabetisk" => "alphabetic");
	general_helpers::make_list_of_link_menu($page, $result_counter); 
?>



<div class="list_of_links">

<?php foreach($result as $row) : ?>
	<a href="index.php?type=vote_admin&action=edit_constituency&id=<?php echo $row['id']; ?>"><?php echo $row['name']; ?></a><br>
<?php endforeach; ?>

</div>