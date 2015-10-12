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

<?php if(empty($posts)) : ?>
	<p>Tråden finns inte eller du saknar behörighet att läsa den.</p>
<?php else : ?>
	<div class="forum_info">
		<a href="index.php?type=forum&action=show_forums=1">Forum</a> > 
		<a href="index.php?type=forum&action=show_topics&id=<?php echo $forum_info['forum_id']; ?>"><?php echo $forum_info['forum_title']; ?></a> > 
	</div>
	<h1><?php echo $post_title; ?></h1>
	<div class="post_count_info">
		<span class="post_counter">Visar inlägg <?php echo $first_showed_post_number; ?> - <?php echo $last_showed_post_number; ?> av totalt <?php echo $post_count; ?></span>
		<?php if($post_count > POSTS_PER_PAGE) : ?>
			<span class="post_page_chooser">
				<?php forum_helpers::output_page_links($number_of_pages, $page, "index.php?type=forum&action=show_posts&id=" . $_GET['id'] . "&page="); ?>
			</span>
		<?php endif; ?>
	</div>
	<?php 
		foreach($posts as $post_info) 
			\View\forum_post_helper::make_post($post_info, $page);
	?>

	<div class="post_count_info">
		<span class="post_counter">Visar inlägg <?php echo $first_showed_post_number; ?> - <?php echo $last_showed_post_number; ?> av totalt <?php echo $post_count; ?></span>
		<?php if($post_count > POSTS_PER_PAGE) : ?>
			<span class="post_page_chooser">
				<?php forum_helpers::output_page_links($number_of_pages, $page, "index.php?type=forum&action=show_posts&id=" . $_GET['id'] . "&page="); ?>
			</span>
		<?php endif; ?>
	</div>

	<?php if(isset($_SESSION['is_forum_admin'])) : ?>
		<p><a href="index.php?type=forum_admin&action=edit_topic&id=<?php echo $_GET['id']; ?>" style="float: right; margin-top: 20px;">Moderera ämne</a></p>
	<?php endif; ?>

	<form method="post" action="" id="new_post_form" class="text-editor">
		<fieldset>
			<legend class="create_new_topic">Skriv svar i tråden</legend>
			<input type="hidden" name="topic_id" value="<?php echo $_GET['id']; ?>">
			<div id="post_buttons_div">
				<input type="button" class="post_buttons" id="post_buttons_b" accesskey="b" title="Fet" value="b" onClick="make_bold('new_post_content')">
				<input type="button" class="post_buttons" id="post_buttons_i" accesskey="i" title="Kursiv" value="i" onClick="make_italic('new_post_content')">
				<input type="button" class="post_buttons" id="post_buttons_u" accesskey="u" title="Understruken" value="u" onClick="make_underline('new_post_content')">
			</div>
			<textarea name="new_post_content" id="new_post_content" tabindex="1"></textarea><br>
			<input type="submit" id="new_post_submit" value="Skicka" tabindex="2">
		</fieldset>
	</form>


<?php endif; ?>

