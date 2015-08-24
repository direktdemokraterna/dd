<h1>Inskickade medlemsansökningar</h1>

<?php 
	$result = db_user::get_all_user_applications();
?>

<div class="list_of_links">

<?php foreach($result as $row) : ?>
	<a href="index.php?type=member_admin&action=process_application&id=<?php echo $row['id']; ?>"><?php echo $row['full_name']; ?></a> (Inkom <?php echo strtolower(general_helpers::show_date($row['application_filed_time'])); ?>)<br>
<?php endforeach; ?>

</div>