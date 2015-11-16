<?php $last_posts = db_forum::get_last_posts(10); ?>

<ul>
	<li>
		<h2>Senaste inläggen</h2>
		<ul>
			<?php foreach($last_posts as $row) : ?>
				<li>
					<a href="index.php?type=forum&action=show_posts&post_id=<?php echo $row['post_id']; ?>"><?php echo $row['post_title']; ?></a><br>
					av <a href="index.php?type=member&action=view&id=<?php echo $row['user_id']; ?>"><?php echo $row['user_full_name']; ?></a> <?php echo general_helpers::show_date($row['posted_time']); ?>
				</li>
			<?php endforeach; ?>
		</ul>
	</li>
	<li>
		<?php 
			\View\general::output_search_box(":in forum", "forum", "search", 111);
		?>
	</li>
</ul>