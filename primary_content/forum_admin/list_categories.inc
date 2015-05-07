<?php $categories = db_forum_admin::list_categories(); ?>

<h1>Kategorier</h1>

<div class="list_of_links">

<?php foreach($categories as $row) : ?>
	<a href="index.php?type=forum_admin&action=edit_category&id=<?php echo $row['id']; ?>"><?php echo $row['title']; ?></a><br>
<?php endforeach; ?>

</div>