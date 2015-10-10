<h1>Pågående omröstningar</h1>
<?php 
	vote_helpers::make_vote_list_header();
	$vote_list = vote_helpers::get_vote_list();
?>
<div class="list_of_links">
<?php foreach($vote_list as $row) : ?>
	<a href="index.php?type=vote&action=view_vote&id=<?php echo $row['id']; ?>"><?php echo $row['title']; ?></a><br>
<?php endforeach; ?>
</div>