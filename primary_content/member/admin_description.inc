<?php 
	$admin_role_info = db_admin::get_admin_role_info($_GET['id']);
?>

<h1><?php echo $admin_role_info['title']; ?></h1>

<p>
<strong>Beskrivning:</strong><br>
<?php if(!empty($admin_role_info['description'])) : ?>
	<?php echo $admin_role_info['description']; ?>
<?php else : ?>
	Ingen beskrivning
<?php endif; ?>
</p>

<?php 
	$list_of_admins = db_admin::get_admin_role_users($_GET['id']);
?>
<p>
<strong>Medlemmar som innehar denna befattning:</strong><br>
<?php foreach($list_of_admins as $row) : ?>
	<a href="index.php?type=member&action=view&id=<?php echo $row['id']; ?>"><?php echo $row['full_name']; ?></a><br>
<?php endforeach; ?>