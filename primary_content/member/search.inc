<h1>Medlemssök</h1>
<?php 
	if(isset($_GET['page'])) $page = $_GET['page']; else $page = 1;
	$search_query = \Logic\util::update_search_query("member");	
	$result = db_user::search_users($search_query, $page);
?>
<?php if(empty($result)) : ?>
	Sökningen gav inga träffar
<?php else : ?>
	<div class="list_of_links">
	<?php foreach($result as $row) : ?>
		<a href="index.php?type=member&action=view&id=<?php echo $row['id']; ?>"><?php echo $row['full_name']; ?></a><br>
	<?php endforeach; ?>
	</div>
<?php endif; ?>