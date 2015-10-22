<?php
	$topic_id = forum_helpers::get_requested_topic();
	$page = forum_helpers::get_requested_page($topic_id);	
	$posts = db_forum::get_posts($topic_id, $_SESSION['id'], $page);
	$post_count = db_forum::get_post_count($topic_id);

	\View\forum_post_helper::show_topic_breadcrumbs($topic_id);
	\View\forum_post_helper::show_topic_title($topic_id);
?>
<?php if(empty($posts)) : ?>
	<p>Tråden finns inte eller du saknar behörighet att läsa den.</p>
<?php else : ?>
	<?php
		\View\forum_post_helper::show_posts("index.php?type=forum&action=show_posts&topic_id=" . $topic_id, $page, $posts, $post_count);
		if(isset($_SESSION['is_forum_admin']))
			echo '<p><a href="index.php?type=forum_admin&action=edit_topic&id=' . $topic_id . '" style="float: right; margin-top: 20px;">Moderera ämne</a></p>';
	?>
	<form method="post" action="" id="new_post_form" class="text-editor">
		<fieldset>
			<legend class="create_new_topic">Skriv svar i tråden</legend>
			<input type="hidden" name="topic_id" value="<?php echo $topic_id; ?>">
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
