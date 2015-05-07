<?php 
	$forum_info = db_forum::get_forum_info($_GET['id']); 
?>

<?php if(empty($forum_info)) : ?>
	<p>Hittar inte forumet.</p>
<?php else : ?>

	<?php
		if(isset($_GET['page'])) $page = $_GET['page']; else $page = 1;
		$i = 0;

	?>
	<h1><?php echo $forum_info['title']; ?></h1>

	<?php $topics = db_forum::list_topics($forum_info['id'], $_SESSION['id'], $page); ?>
	<?php if(empty($topics)) : ?>
		<p>Inga ämnen i detta forum.</p>
	<?php else : ?>

		<table class="topic_list">
		<tr class="topic_list_top_row" id="topic_list_top_row_tr"><td>Ämne</td><td>Deltagare</td><td>Inlägg</td><td>Senaste inlägg</td></tr>

		<?php foreach($topics as $row) : ?>
			<?php 
				$i++; 
				$number_of_pages = ceil( $row['number_of_posts'] / POSTS_PER_PAGE );
			?>
			<tr>
				<td style="width: 300px;" class="topic_list_<?php if($i % 2 == 0) echo "even"; else echo "odd"; ?>">
					<a href="index.php?type=forum&action=show_posts&id=<?php echo $row['topic_id']; ?>"><?php echo $row['topic_title']; ?></a>
					<?php if($number_of_pages > 1) : ?>
						 <a href="index.php?type=forum&action=show_posts&id=<?php echo $row['topic_id']; ?>&page=<?php echo $number_of_pages; ?>">(<?php echo $number_of_pages; ?>)</a>
					<?php endif; ?>
					<br><span class="list_sub_text">Startat av: <a href="index.php?type=member&action=view&id=<?php echo $row['topic_user_id']; ?>"><?php echo $row['topic_user_full_name']; ?></a></span>
				</td>
				<td style="width: 100px;" class="topic_list_<?php if($i % 2 == 0) echo "even"; else echo "odd"; ?>">
					<?php echo $row['number_of_participants']; ?>
				</td>
				<td style="width: 100px;" class="topic_list_<?php if($i % 2 == 0) echo "even"; else echo "odd"; ?>">
					<?php echo $row['number_of_posts']; ?>
				</td>
				<td style="width: 300px;" class="topic_list_<?php if($i % 2 == 0) echo "even"; else echo "odd"; ?>">
					<?php echo general_helpers::show_date($row['last_posted_time']); ?><br>
					<span class="list_sub_text">Av: <a href="index.php?type=member&action=view&id=<?php echo $row['last_user_id']; ?>"><?php echo $row['last_user_full_name']; ?></a></span>
				</td>
			</tr>
		<?php endforeach; ?>

		</table>
	<?php endif; ?>

	<form method="post" action="" id="new_topic_form" class="text-editor">
		<fieldset>
			<legend class="create_new_topic">Skapa ny tråd i detta forum</legend>
			<input type="hidden" name="forum_id" value="<?php echo $forum_info['id']; ?>">
			<label for "new_topic_title">Ämnestitel</label>
			<input type="text" name="new_topic_title" id="new_topic_title">
			<br>
			<div id="post_buttons_div">
				<input type="button" class="post_buttons" id="post_buttons_b" accesskey="b" title="" value="b">
				<input type="button" class="post_buttons" id="post_buttons_i" accesskey="i" title="" value="i">
				<input type="button" class="post_buttons" id="post_buttons_u" accesskey="u" title="" value="u">
			</div>
			<textarea name="new_topic_content" id="new_topic_content" rows="12" cols="30"></textarea>
			<br>
			<input type="submit" id="new_topic_submit" value="Skicka">
		</fieldset>
	</form>

<?php endif; ?>