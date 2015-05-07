<?php $userdata = db_user::get_user_data($_GET['id']); ?>

<h1><?php echo $userdata['first_name'] . " " . $userdata['last_name']; ?></h1>

<strong>Administratörsrättigheter för denna användare</strong><br>
<form method="post" action=""><ul class="checkbox-grid">

<?php $admin_roles = db_admin::get_all_admin_roles_and_if_user_belongs($_GET['id']); ?>

<?php foreach($admin_roles as $row) : ?>
	<li><input type="checkbox" name="check_list[]" id="<?php echo $row['title']; ?>" value="<?php echo $row['id']; ?>" <?php if($row['user_role']==1) echo " checked"; ?>>
	<label for "<?php echo $row['title']; ?>"><?php echo $row['title']; ?></label></li>
<?php endforeach; ?>

</ul><div class="clear"></div><br><input type="submit" style="margin-left: 10%;" id="submit" value="Ändra">
</form>
