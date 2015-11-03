<?php 
	$userdata = db_user::get_user_data($_GET['id']);
	\View\general_helper::make_internal_link("<- Tillbaka till " . $userdata['first_name'], "member", "view", "id=" . $_GET['id']);
?>
<h1><?php echo $userdata['first_name'] . " " . $userdata['last_name']; ?></h1>

<strong>Forumbehörigheter för denna användare</strong><br>
<form method="post" action=""><ul class="checkbox-grid">

<?php $forum_access = db_forum_admin::get_all_forums_and_if_user_belongs($_GET['id']); ?>

<?php foreach($forum_access as $row) : ?>
	<li><input type="checkbox" name="check_list[]" id="<?php echo $row['forum_name']; ?>" value="<?php echo $row['forum_id']; ?>" <?php if($row['user_access']==1) echo " checked"; ?>>
	<label for "<?php echo $row['forum_name']; ?>"><?php echo $row['forum_name']; ?></label></li>
<?php endforeach; ?>

</ul><div class="clear"></div><br><input type="submit" style="margin-left: 10%;" id="submit" value="Ändra">
</form>
