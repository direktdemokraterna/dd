<?php 
/*
File: /sidebar/forum.inc
Description: Sidebar for forums
*/
?>
<?php $last_posts = db_forum::get_last_posts(10); ?>

<ul>
	<li class="search-forums"> 
		<?php
		\View\controls::output_search_box("i forum", "forum", "search", 111);
		?>
	</li>
	<li class="latest-posts">
		<?php __h2("Senaste inlägg"); ?>
		<ul>
			<?php foreach($last_posts as $row) : ?>
				<li>
					<?php 
						__link($row['post_title'], 'forum', 'show_posts', 
							'post_id=' . $row['post_id']);
						echo '<span class="post-meta-sidebar">av ';
						__link($row['user_full_name'], 'member', 'view', 
							'id=' . $row['user_id']);
						echo ' ' . general_helpers::show_date($row['posted_time']);
						echo '</span>';
					?>
				</li>
			<?php endforeach; ?>
		</ul>
	</li>
</ul>