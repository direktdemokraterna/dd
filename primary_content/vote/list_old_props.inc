<h1>Före detta propositioner</h1>
<?php 
	$statuses = array('rejected', 'affirmed');
	vote_helpers::make_prop_list_header($statuses);
	$prop_groups = vote_helpers::get_prop_groups($statuses);
?>
<div class="list_of_links">
	<?php foreach($prop_groups as $prop_group) : ?>
		<h2><?php echo $prop_group->constituency; ?></h2>
		<?php foreach($prop_group->votes as $row) : ?>
			<a href="index.php?type=vote&action=view_prop&id=<?php echo $row['id']; ?>"><?php echo $row['title']; ?></a><br>
		<?php endforeach; ?>
	<?php endforeach; ?>
</div>
