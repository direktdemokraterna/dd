<?php $forums = db_forum_admin::list_forums(); ?>

<h1>Forum</h1>

<div class="list_of_links">

<?php foreach($forums as $row) : ?>
	<a href="index.php?type=forum_admin&action=edit_forum&id=<?php echo $row['id']; ?>"><?php echo $row['title']; ?></a><br>
<?php endforeach; ?>

</div>