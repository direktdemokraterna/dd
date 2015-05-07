<h1>Forum</h1>

<?php 
	$forums = db_forum::list_forums(); 
	$category = "";
?>

<table class="forum_list">
<?php foreach($forums as $row) : ?>
	<?php if($category != $row['cat_name']) : ?>
		<tr><td colspan="2" class="forum_list_cat"><?php echo $row['cat_name']; ?></td></tr>
		<?php 
			$category = $row['cat_name'];
			$i = 0;
		?>
	<?php endif; ?>
	<?php 
		$i++;
		if(!empty($row['last_posted_id'])){
			$post_info = db_forum::get_post_info($row['last_posted_id']);
		}
	?>
	<tr>
		<td class="forum_list_<?php if($i % 2 == 0) echo "even"; else echo "odd"; ?>">
			<a href="index.php?type=forum&action=show_topics&id=<?php echo $row['forum_id']; ?>"><?php echo $row['forum_name']; ?></a>
			<br><span class="list_sub_text"><?php echo $row['number_of_topics']; ?> ämnen, <?php echo $row['number_of_posts']; ?> inlägg</span>
		</td>
		<td class="forum_list_<?php if($i % 2 == 0) echo "even"; else echo "odd"; ?>">
			<?php if(!empty($post_info)) : ?>
				<a href="index.php?type=forum&action=show_posts&id=<?php echo $post_info['topic_id']; ?>"><?php echo $post_info['title']; ?></a>
				<br><span class="list_sub_text">av <a href="index.php?type=member&action=view&id=<?php echo $post_info['user_id']; ?>"><?php echo $post_info['full_name']; ?></a> <?php echo general_helpers::show_date($row['last_posted_time']); ?></span>
			<?php else : ?>
				Inga inlägg
			<?php endif; ?>
		</td>
	</tr>
<?php endforeach; ?>
</table>