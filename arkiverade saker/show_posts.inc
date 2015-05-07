<?php 
	if(isset($_GET['page'])) $page = $_GET['page']; else $page = 1;
	$posts = db_forum::get_posts($_GET['id'], $_SESSION['id'], $page);

	$post_title = db_forum::get_title($_GET['id']);
	$post_count = db_forum::get_post_count($_GET['id']);
	$number_of_pages = ceil($post_count / POSTS_PER_PAGE);
	$first_showed_post_number = $page * POSTS_PER_PAGE - 49;
	$last_showed_post_number = $page * POSTS_PER_PAGE;
	if($last_showed_post_number > $post_count) $last_showed_post_number = $post_count;
?>

<h1><?php echo $post_title; ?></h1>

<?php if(empty($posts)) : ?>
	<p>Hittar inte tråden.</p>
<?php else : ?>
	<div id="post_count_info">
		<span id="post_counter">Visar inlägg <?php echo $first_showed_post_number; ?> - <?php echo $last_showed_post_number; ?> av totalt <?php echo $post_count; ?></span>
		<?php if($post_count > POSTS_PER_PAGE) : ?>
			<span id="post_page_chooser">
				<?php forum_helpers::output_page_links($number_of_pages, $page, "index.php?type=forum&action=show_posts&id=" . $_GET['id'] . "&page="); ?>
			</span>
		<?php endif; ?>
	</div>
	<?php foreach($posts as $row) : ?>
		<table class="single_post_table">
		<a id="post<?php echo $row['post_id']; ?>"></a>
			<tr class="single_post_top_row">
				<td class="single_post_top_left_cell"><?php echo general_helpers::show_date($row['posted_time']); ?></td>
				<td class="single_post_top_right_cell">
					<?php if($row['posted_time'] > (time() - 10*60) && $row['user_id'] == $_SESSION['id']) : ?>
						<a href="index.php?type=forum&action=delete&id=<?php echo $row['post_id']; ?>" class="post_quote_link" onclick="return confirm('Vill du verkligen radera inlägget?')">Radera</a> 
						<a href="index.php?type=forum&action=edit&id=<?php echo $row['post_id']; ?>" class="post_quote_link">Redigera</a> 
					<?php elseif($row['posted_time'] <= (time() - 10*60) && $row['user_id'] == $_SESSION['id']) : ?>
						<a href="index.php?type=forum&action=add&id=<?php echo $row['post_id']; ?>" class="post_quote_link">Tillägg</a> 
					<?php endif; ?>
					<a href="index.php?type=forum&action=report&id=<?php echo $row['post_id']; ?>" class="post_quote_link">Anmäl</a> 
					<a class="post_quote_link" onMouseDown="quote_post(<?php echo $row['post_id']; ?>)" unselectable="on">Citera</a> 
					<a href="index.php?type=forum&action=show_posts&id=<?php echo $_GET['id']; ?>&page=<?php echo $page; ?>#<?php echo $row['post_id']; ?>" class="specific_post_link">#<?php echo $row['post_id']; ?></a> 
				</td>
			</tr>
			<tr class="single_post_bottom_row">
				<td class="single_post_bottom_left_cell">
					<img src="<?php echo USERIMG_PATH . $row['user_image']; ?>" class="post_user_image" width="80"><br>
					<a class="user_name_link" href="index.php?type=member&action=view&id=<?php echo $row['user_id']; ?>"><?php echo $row['user_full_name']; ?></a>
				</td>
				<td class="single_post_bottom_right_cell">
					<div class="post_content">
						<span id="post_content_<?php echo $row['post_id']; ?>"><?php echo nl2br($row['content']); ?></span>
					</div>
					<?php if(isset($row['last_edited_time'])) : ?>
						<span class="post_last_edited">Ändrades senast <?php echo strtolower(general_helpers::show_date($row['last_edited_time'])); ?>.</span>
					<?php endif; ?>
				</td>
			</tr>
		</table>
	<?php endforeach; ?>

	<div id="post_count_info">
		<span id="post_counter">Visar inlägg <?php echo $first_showed_post_number; ?> - <?php echo $last_showed_post_number; ?> av totalt <?php echo $post_count; ?></span>
		<?php if($post_count > POSTS_PER_PAGE) : ?>
			<span id="post_page_chooser">
				<?php forum_helpers::output_page_links($number_of_pages, $page, "index.php?type=forum&action=show_posts&id=" . $_GET['id'] . "&page="); ?>
			</span>
		<?php endif; ?>
	</div>

	<form method="post" action="" id="new_post_form" class="text-editor">
		<fieldset>
			<legend class="create_new_topic">Skriv svar i tråden</legend>
			<input type="hidden" name="topic_id" value="<?php echo $_GET['id']; ?>">
			<div id="post_buttons_div">
				<input type="button" class="post_buttons" id="post_buttons_b" accesskey="b" title="Fet" value="b" onClick="make_bold()">
				<input type="button" class="post_buttons" id="post_buttons_i" accesskey="i" title="Kursiv" value="i" onClick="make_italic()">
				<input type="button" class="post_buttons" id="post_buttons_u" accesskey="u" title="Understruken" value="u" onClick="make_underline()">
			</div>
			<textarea name="new_post_content" id="new_post_content" rows="32" cols="30"></textarea><br>
			<input type="submit" id="new_post_submit" value="Skicka">
		</fieldset>
	</form>


<?php endif; ?>

