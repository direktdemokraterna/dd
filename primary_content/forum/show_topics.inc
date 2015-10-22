<?php 
	$forum_info = db_forum::get_forum_info($_GET['id']); 
?>

<?php if(empty($forum_info)) : ?>
	<p>Hittar inte forumet.</p>
<?php else : ?>
	<div class="forum_info">
		<a href="index.php?type=forum&action=show_forums=1">Forum</a> > 
	</div>

	<?php
		if(isset($_GET['page'])) $page = $_GET['page']; else $page = 1;
	?>
	<h1><?php echo $forum_info['title']; ?></h1>

	<?php $topics = db_forum::list_topics($forum_info['id'], $_SESSION['id'], $page); ?>
	<?php if(empty($topics)) : ?>
		<p>Inga ämnen i detta forum.</p>
	<?php else : ?>

		<div class="topic_list">
		<div class="topic_list_top_row">
			<span class="subject_column">Ämne</span><span class="numerical_column">Deltagare</span><span class="numerical_column">Inlägg</span><span class="last_post_column">Senaste inlägg</span>
			<div style="clear: both;"></div>
		</div>


		<?php foreach($topics as $row) : ?>
			<?php 
				$number_of_pages = ceil( $row['number_of_posts'] / POSTS_PER_PAGE );
			?>
			<div class="topic_list_row">
				<span class="subject_column">
					<a href="index.php?type=forum&action=show_posts&topic_id=<?php echo $row['topic_id']; ?>"><?php echo $row['topic_title']; ?></a>
					<?php if($number_of_pages > 1) : ?>
						 <a href="index.php?type=forum&action=show_posts&topic_id=<?php echo $row['topic_id']; ?>&page=<?php echo $number_of_pages; ?>">(<?php echo $number_of_pages; ?>)</a>
					<?php endif; ?>
					<br><span class="list_sub_text">Startat av: <a href="index.php?type=member&action=view&id=<?php echo $row['topic_user_id']; ?>"><?php echo $row['topic_user_full_name']; ?></a></span>
				</span>
				<span class="numerical_column"><?php echo $row['number_of_participants']; ?></span>
				<span class="numerical_column"><?php echo $row['number_of_posts']; ?></span>
				<span class="last_post_column">
					<?php echo general_helpers::show_date($row['last_posted_time']); ?><br>
					<span class="list_sub_text">Av: <a href="index.php?type=member&action=view&id=<?php echo $row['last_user_id']; ?>"><?php echo $row['last_user_full_name']; ?></a></span>
				</span>
				<div style="clear: both;"></div>
			</div>
		<?php endforeach; ?>

		</div>
	<?php endif; ?>

	<form method="post" action="" id="new_topic_form" class="text-editor">
		<fieldset>
			<legend class="create_new_topic">Skapa ny tråd i detta forum</legend>
			<input type="hidden" name="forum_id" value="<?php echo $forum_info['id']; ?>">
			<label for "new_topic_title">Ämnestitel</label>
			<input type="text" name="new_topic_title" id="new_topic_title" tabindex="1">
			<br>
			<div id="post_buttons_div">
				<input type="button" class="post_buttons" id="post_buttons_b" accesskey="b" title="Fet" value="b" onClick="make_bold()">
				<input type="button" class="post_buttons" id="post_buttons_i" accesskey="i" title="Kursiv" value="i" onClick="make_italic()">
				<input type="button" class="post_buttons" id="post_buttons_u" accesskey="u" title="Understruken" value="u" onClick="make_underline()">
			</div>
			<textarea name="new_topic_content" id="new_topic_content" rows="12" cols="30" tabindex="2"></textarea>
			<br>
			<input type="submit" id="new_topic_submit" value="Skicka" tabindex="3">
		</fieldset>
	</form>

<?php endif; ?>