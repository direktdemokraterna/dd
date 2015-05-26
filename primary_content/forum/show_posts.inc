<?php 
	if(isset($_GET['page'])) $page = $_GET['page']; else $page = 1;
	$posts = db_forum::get_posts($_GET['id'], $_SESSION['id'], $page);

	$post_title = db_forum::get_title($_GET['id']);
	$forum_info = db_forum::get_forum_from_post($_GET['id']);
	$post_count = db_forum::get_post_count($_GET['id']);
	$number_of_pages = ceil($post_count / POSTS_PER_PAGE);
	$first_showed_post_number = $page * POSTS_PER_PAGE - (POSTS_PER_PAGE - 1);
	$last_showed_post_number = $page * POSTS_PER_PAGE;
	if($last_showed_post_number > $post_count) $last_showed_post_number = $post_count;
?>

<h1><?php echo $post_title; ?></h1>

<?php if(empty($posts)) : ?>
	<p>Hittar inte tråden.</p>
<?php else : ?>
	<div class="forum_info">
		<a href="index.php?type=forum&action=show_forums=1">Forum</a> > 
		<a href="index.php?type=forum&action=show_topics&id=<?php echo $forum_info['forum_id']; ?>"><?php echo $forum_info['forum_title']; ?></a> > 
		<a href="index.php?type=forum&action=show_posts&id=<?php echo $_GET['id']; ?>"><?php echo $post_title; ?></a>
	</div>
	<div class="post_count_info">
		<span class="post_counter">Visar inlägg <?php echo $first_showed_post_number; ?> - <?php echo $last_showed_post_number; ?> av totalt <?php echo $post_count; ?></span>
		<?php if($post_count > POSTS_PER_PAGE) : ?>
			<span class="post_page_chooser">
				<?php forum_helpers::output_page_links($number_of_pages, $page, "index.php?type=forum&action=show_posts&id=" . $_GET['id'] . "&page="); ?>
			</span>
		<?php endif; ?>
	</div>
	<?php foreach($posts as $post_info) : ?>
		<div class="single_post_container">
		<a id="post<?php echo $post_info['post_id']; ?>"></a>
			<div class="post_top_row">
				<span class="post_date"><?php echo general_helpers::show_date($post_info['posted_time']); ?></span>
				<span class="post_alternatives">
					<?php if($_SESSION['is_forum_admin']) : ?>
						<a href="index.php?type=forum_admin&action=edit_post&id=<?php echo $post_info['post_id']; ?>">Moderera</a> 
					<?php endif; ?>
					<?php if($post_info['posted_time'] > (time() - 10*60) && $post_info['user_id'] == $_SESSION['id']) : ?>
						<a href="index.php?type=forum&action=delete&id=<?php echo $post_info['post_id']; ?>" onclick="return confirm('Vill du verkligen radera inlägget?')">Radera</a> 
						<a href="index.php?type=forum&action=edit&id=<?php echo $post_info['post_id']; ?>">Redigera</a> 
					<?php elseif($post_info['posted_time'] <= (time() - 10*60) && $post_info['user_id'] == $_SESSION['id']) : ?>
						<a href="index.php?type=forum&action=add&id=<?php echo $post_info['post_id']; ?>">Tillägg</a> 
					<?php endif; ?>
					<a href="index.php?type=forum&action=report&id=<?php echo $post_info['post_id']; ?>">Anmäl</a> 
					<a onMouseDown="quote_post(<?php echo $post_info['post_id']; ?>)" style="user-select: none;" unselectable="on">Citera</a> 
					<a href="index.php?type=forum&action=show_posts&id=<?php echo $_GET['id']; ?>&page=<?php echo $page; ?>#<?php echo $post_info['post_id']; ?>">#<?php echo $post_info['post_id']; ?></a> 
				</span>
			</div>

			<div class="post_bottom_row">
			<div class="post_user_info">
				<img src="<?php echo USERIMG_PATH . $post_info['user_image']; ?>" class="post_user_image" width="80"><br>
				<a class="user_name_link" href="index.php?type=member&action=view&id=<?php echo $post_info['user_id']; ?>"><?php echo $post_info['user_full_name']; ?></a>
			</div>
			
			<div class="post_content">
				<span id="post_content_<?php echo $post_info['post_id']; ?>"><?php echo nl2br($post_info['content']); ?></span>
				<?php if(isset($post_info['last_edited_time'])) : ?>
					<span class="post_last_edited">Ändrades senast <?php echo strtolower(general_helpers::show_date($post_info['last_edited_time'])); ?>.</span>
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

	<?php if($_SESSION['is_forum_admin']) : ?>
		<p><a href="index.php?type=forum_admin&action=edit_topic&id=<?php echo $_GET['id']; ?>" style="float: right; margin-top: 20px;">Moderera ämne</a></p>
	<?php endif; ?>

	<form method="post" action="" id="new_post_form" class="text-editor">
		<fieldset>
			<legend class="create_new_topic">Skriv svar i tråden</legend>
			<input type="hidden" name="topic_id" value="<?php echo $_GET['id']; ?>">
			<div id="post_buttons_div">
				<input type="button" class="post_buttons" id="post_buttons_b" accesskey="b" title="Fet" value="b" onClick="make_bold()">
				<input type="button" class="post_buttons" id="post_buttons_i" accesskey="i" title="Kursiv" value="i" onClick="make_italic()">
				<input type="button" class="post_buttons" id="post_buttons_u" accesskey="u" title="Understruken" value="u" onClick="make_underline()">
			</div>
			<textarea name="new_post_content" id="new_post_content" tabindex="1"></textarea><br>
			<input type="submit" id="new_post_submit" value="Skicka" tabindex="2">
		</fieldset>
	</form>


<?php endif; ?>

