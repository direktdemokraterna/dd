<?php $last_posts = db_forum::get_last_posts(10); ?>

<ul>
	<li>
		<?php __h2(_t("Latest posts")); ?>
		<ul>
			<?php foreach($last_posts as $row) : ?>
				<li>
					<?php 
						\View\controls::output_internal_link($row['post_title'], 'forum', 'show_posts', 
							'post_id=' . $row['post_id']);
						echo '<br>' . _t("by") . ' ';
						\View\controls::output_internal_link($row['user_full_name'], 'member', 'view', 
							'id=' . $row['user_id']);
						echo ' ' . general_helpers::show_date($row['posted_time']); 
					?>
				</li>
			<?php endforeach; ?>
		</ul>
	</li>
	<li>
		<?php 
			\View\controls::output_search_box("in forum", "forum", "search", 111);
		?>
	</li>
</ul>