<?php 
 	//going to correct post by redirecting to #[POST_ID] no longer possible, did this work before?
	$topic_id = db_forum::get_topic($_GET['id']);
	$page = isset($_GET['page']) ? $_GET['page'] : 1;

	if($topic_id != $_GET['id']){ // $_GET['id'] is not a topic, calculating topic and relevant page
		$number_of_posts_in_topic = db_forum::get_number_of_posts($topic_id);
		if($number_of_posts_in_topic > POSTS_PER_PAGE){
			$posts_before_this_post = db_forum::count_posts_before_post_id($topic_id, $_GET['id']);
			$page = ceil(($posts_before_this_post+1) / POSTS_PER_PAGE);
		}
	}

	if(isset($_GET['page']) && $_GET['page'] == "last"){
		$number_of_posts_in_topic = db_forum::get_number_of_posts($topic_id);
		$page = ceil($number_of_posts_in_topic / POSTS_PER_PAGE);
	}
	$posts = db_forum::get_posts($topic_id, $_SESSION['id'], $page);
	$post_count = db_forum::get_post_count($topic_id);
?>

<?php if(empty($posts)) : ?>
	<p>Tråden finns inte eller du saknar behörighet att läsa den.</p>
<?php else : ?>
	<?php
		\View\forum_post_helper::show_topic_breadcrumbs($topic_id);
		\View\forum_post_helper::show_topic_title($topic_id);
		\View\forum_post_helper::show_posts("index.php?type=forum&action=show_posts&id=" . $topic_id, $page, $posts, $post_count);
	?>

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

