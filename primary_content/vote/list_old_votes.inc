<h1>Avslutade omröstningar</h1>
<?php 
	$statuses = array('ended', 'finished');
	vote_helpers::make_vote_list_header($statuses);
	$vote_groups = vote_helpers::get_vote_groups($statuses);
?>
<div class="list_of_links">
	<?php foreach($vote_groups as $vote_group) : ?>
		<h2><?php echo $vote_group->constituency; ?></h2>
		<?php foreach($vote_group->votes as $row) : ?>
			<a href="index.php?type=vote&action=view_vote&id=<?php echo $row['id']; ?>"><?php echo $row['title']; ?></a><br>
		<?php endforeach; ?>
	<?php endforeach; ?>
</div>
