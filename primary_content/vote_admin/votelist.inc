<h1>Pågående omröstningar</h1>
<?php 
	vote_helpers::make_vote_list_header();
	$vote_list = vote_helpers::get_vote_list();
?>
<div class="list_of_links">
<?php foreach($result as $row) : ?>
	<a href="index.php?type=vote_admin&action=edit_vote&id=<?php echo $row['id']; ?>"><?php echo $row['title']; ?></a><br>
<?php endforeach; ?>
</div>