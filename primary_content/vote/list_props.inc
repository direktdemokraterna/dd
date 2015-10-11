<h1>Lagda propositioner</h1>
<?php 
	vote_helpers::make_prop_list_header();
	$prop_groups = vote_helpers::get_prop_groups();
?>
<div class="list_of_links">
	<?php foreach($prop_groups as $prop_group) : ?>
		<h2><?php echo $prop_group->constituency; ?></h2>
		<?php foreach($prop_group->votes as $row) : ?>
			<a href="index.php?type=vote&action=view_prop&id=<?php echo $row['id']; ?>"><?php echo $row['title']; ?></a><br>
		<?php endforeach; ?>
	<?php endforeach; ?>
</div>
