<h1>Administratörer</h1>
<?php 
	$admin_roles = db_admin::get_all_admin_roles();
?>

<?php foreach($admin_roles as $admin_role) : ?>
	<h2><?php echo $admin_role['title']; ?></h2>
	<?php 
		$admins_for_this_role = db_admin::get_admin_role_users($admin_role['id']);
	?>
	<?php foreach($admins_for_this_role as $admin) : ?>
		<a href="index.php?type=member&action=view&id=<?php echo $admin['id']; ?>"><?php echo $admin['full_name']; ?></a><br>
	<?php endforeach; ?>
<?php endforeach; ?>