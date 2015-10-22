<h1>Forum</h1>

<?php 
	$forums = db_forum::list_forums(); 
	$category = "";
?>

<div class="forum_list">
<?php foreach($forums as $row) : ?>
	<?php if($category != $row['cat_name']) : ?>
		<div class="topic_list_top_row" style="text-align: left;"><span class="cat_name"><?php echo $row['cat_name']; ?></span></div>
		<?php 
			$category = $row['cat_name'];
		?>
	<?php endif; ?>

	<div class="topic_list_row" style="text-align: left;">
		<span class="forum_name">
			<a href="index.php?type=forum&action=show_topics&id=<?php echo $row['forum_id']; ?>"><?php echo $row['forum_name']; ?></a>
			<br><span class="list_sub_text"><?php echo $row['number_of_topics']; ?> ämnen, <?php echo $row['number_of_posts']; ?> inlägg</span>
		</span>
		<span class="forum_last_post">
			<?php if(isset($row['last_posted_id'])) : ?>
				<?php $post_info = db_forum::get_post_info($row['last_posted_id']); ?>
				<a href="index.php?type=forum&action=show_posts&topic_id=<?php echo $post_info['topic_id']; ?>"><?php echo $post_info['title']; ?></a>
				<br><span class="list_sub_text">av <a href="index.php?type=member&action=view&id=<?php echo $post_info['user_id']; ?>"><?php echo $post_info['full_name']; ?></a> <?php echo general_helpers::show_date($row['last_posted_time']); ?></span>
			<?php else : ?>
				Inga inlägg
			<?php endif; ?>
		</span>
		<div style="clear: both;"></div>
	</div>
<?php endforeach; ?>
</div>
