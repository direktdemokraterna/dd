<?php 
	if(isset($_GET['page'])) $page = $_GET['page']; else $page = 1;
	$posts = db_forum::get_posts_by_user($_GET['id'], $_SESSION['id'], $page);

	$post_count = db_forum::get_post_count_by_user($_GET['id'], $_SESSION['id']);
	$number_of_pages = ceil($post_count / POSTS_PER_PAGE);
	$first_showed_post_number = $page * POSTS_PER_PAGE - 49;
	$last_showed_post_number = $page * POSTS_PER_PAGE;
	if($last_showed_post_number > $post_count) $last_showed_post_number = $post_count;

	$user_full_name = db_user::get_user_full_name($_GET['id']);
?>


<h1>Inlägg av <?php echo $user_full_name; ?></h1>

<?php if(empty($posts)) : ?>
	<p>Inga inlägg.</p>
<?php else : ?>
	<div class="post_count_info">
		<span class="post_counter">Visar inlägg <?php echo $first_showed_post_number; ?> - <?php echo $last_showed_post_number; ?> av totalt <?php echo $post_count; ?></span>
		<?php if($post_count > POSTS_PER_PAGE) : ?>
			<span class="post_page_chooser">
				<?php forum_helpers::output_page_links($number_of_pages, $page, "index.php?type=forum&action=show_posts&id=" . $_GET['id'] . "&page="); ?>
			</span>
		<?php endif; ?>
	</div>
	<?php foreach($posts as $row) : ?>
		<div class="single_post_container">
		<a id="post<?php echo $row['post_id']; ?>"></a>
			<div class="post_top_row">
				<span class="post_date"><?php echo general_helpers::show_date($row['posted_time']); ?></span>
				<span class="post_alternatives">
					<?php if($row['posted_time'] > (time() - 10*60) && $row['user_id'] == $_SESSION['id']) : ?>
						<a href="index.php?type=forum&action=delete&id=<?php echo $row['post_id']; ?>" onclick="return confirm('Vill du verkligen radera inlägget?')">Radera</a> 
						<a href="index.php?type=forum&action=edit&id=<?php echo $row['post_id']; ?>">Redigera</a> 
					<?php elseif($row['posted_time'] <= (time() - 10*60) && $row['user_id'] == $_SESSION['id']) : ?>
						<a href="index.php?type=forum&action=add&id=<?php echo $row['post_id']; ?>">Tillägg</a> 
					<?php endif; ?>
					<a href="index.php?type=forum&action=report&id=<?php echo $row['post_id']; ?>">Anmäl</a> 
					<a onMouseDown="quote_post(<?php echo $row['post_id']; ?>)" unselectable="on">Citera</a> 
					<a href="index.php?type=forum&action=show_posts&id=<?php echo $_GET['id']; ?>&page=<?php echo $page; ?>#<?php echo $row['post_id']; ?>">#<?php echo $row['post_id']; ?></a> 
				</span>
			</div>

			<div class="post_bottom_row">
			<div class="post_user_info">
				<img src="<?php echo USERIMG_PATH . $row['user_image']; ?>" class="post_user_image" width="80"><br>
				<a class="user_name_link" href="index.php?type=member&action=view&id=<?php echo $row['user_id']; ?>"><?php echo $row['user_full_name']; ?></a>
			</div>
			
			<div class="post_content">
				<span id="post_content_<?php echo $row['post_id']; ?>"><?php echo nl2br($row['content']); ?></span>
				<?php if(isset($row['last_edited_time'])) : ?>
					<span class="post_last_edited">Ändrades senast <?php echo strtolower(general_helpers::show_date($row['last_edited_time'])); ?>.</span>
				<?php endif; ?>
			</div>
			</div>
		
			<div style="clear: both;"></div>
		</div>
	<?php endforeach; ?>

	<div class="post_count_info">
		<span class="post_counter">Visar inlägg <?php echo $first_showed_post_number; ?> - <?php echo $last_showed_post_number; ?> av totalt <?php echo $post_count; ?></span>
		<?php if($post_count > POSTS_PER_PAGE) : ?>
			<span class="post_page_chooser">
				<?php forum_helpers::output_page_links($number_of_pages, $page, "index.php?type=forum&action=show_posts&id=" . $_GET['id'] . "&page="); ?>
			</span>
		<?php endif; ?>
	</div>

<?php endif; ?>

