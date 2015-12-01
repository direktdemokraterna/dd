<?php 
	$userdata = db_user::get_user_data($_GET['id']);
	_h1(\View\general::generate_internal_link($userdata['first_name'] . " " . $userdata['last_name'], "member", "view", "id=" . $_GET['id']));
	_strong(_t("Constituency authorisations for this user"));
?>
<form method="post" action=""><ul class="checkbox-grid">

<?php $constituency_access = db_constituency::get_all_constituencies_and_if_user_belongs($_GET['id']); ?>

<?php foreach($constituency_access as $row) : ?>
	<li><input type="checkbox" name="check_list[]" id="<?php echo $row['constituency_name']; ?>" value="<?php echo $row['constituency_id']; ?>" <?php if($row['user_access']==1) echo " checked"; ?>>
	<label for "<?php echo $row['constituency_name']; ?>"><?php echo $row['constituency_name']; ?></label></li>
<?php endforeach; ?>

</ul><div class="clear"></div><br><input type="submit" style="margin-left: 10%;" id="submit" value="<?php __('Change'); ?>">
</form>
