<h1>Föreslagna arbetsgrupper</h1>

<?php 
	if(isset($_GET['page'])) $page = $_GET['page']; else $page = 1;
	$workgroups = db_workgroup::list_proposed($page);
?>

<div class="list_of_links">

<?php foreach($workgroups as $row) : ?>
	<a href="index.php?type=workgroup&action=view&id=<?php echo $row['id']; ?>"><?php echo $row['title']; ?></a><br>
<?php endforeach; ?>

</div>