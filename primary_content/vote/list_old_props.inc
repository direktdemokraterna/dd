<h1>Före detta propositioner</h1>

<?php 
	if(isset($_GET['page'])) $page = $_GET['page']; else $page = 1;

	if($_GET['sort'] == "alphabetic") $sort_query = "title asc";
	else $sort_query = "created_by_user desc";

	if($_GET['filter'] == "yes-no") $filter_query = "type = 'yes-no'";
	elseif($_GET['filter'] == "prio-vote") $filter_query = "type = 'prio-vote'";
	elseif($_GET['filter'] == "candidate-election") $filter_query = "type = 'candidate-election'";
	elseif($_GET['filter'] == "median") $filter_query = "type = 'median'";
	elseif($_GET['filter'] == "budget") $filter_query = "type = 'budget'";
	else $filter_query = "1=1";

	$result = db_prop::list_old_props($page, LIST_ITEMS_PER_PAGE, $sort_query, $filter_query);
	$result_counter = db_prop::list_old_props_count($filter_query);
?>

<?php 
	$sort_alternatives = Array("Skapad" => "created", "Alfabetisk" => "alphabetic");
	$filter_title = "Omröstningstyp:";
	$filter_alternatives = Array("Votering" => "yes-no", "Prioritetsomröstning" => "prio-vote", "Personval" => "candidate-election", "Medianomröstning" => "median", "Budgetomröstning" => "budget");
	general_helpers::make_list_of_link_menu($page, $result_counter, $sort_alternatives, $filter_title, $filter_alternatives); 
?>



<div class="list_of_links">

<?php foreach($result as $row) : ?>
	<a href="index.php?type=vote&action=view_prop&id=<?php echo $row['id']; ?>"><?php echo $row['title']; ?></a> 
	(<?php 
			if($row['status'] == "rejected") echo "förkastad";
			else echo "blivit omröstning";
		?>)
	<br>
<?php endforeach; ?>

</div>