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
		<h2>Sök i forum</h2>
		<form method="post" class="sidebar_search_form" action="index.php?type=forum&action=search">
			<input tabindex="111" type="text" value="" name="forum_search_input" class="sidebar_search_input">
			<input tabindex="112" type="submit" class="sidebar_search_submit" value="Sök">
		</form>
	</li>
</ul>