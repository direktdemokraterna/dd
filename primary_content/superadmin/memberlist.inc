<h1>Lista över medlemmar</h1>

<?php 
	if(isset($_GET['page'])) $page = $_GET['page']; else $page = 1;
	$result = db_user::get_all_users($page);
?>

<div class="list_of_links">

<?php foreach($result as $row) : ?>
	<a href="index.php?type=superadmin&action=edit_admin&id=<?php echo $row['id']; ?>"><?php echo $row['full_name']; ?></a><br>
<?php endforeach; ?>

</div>