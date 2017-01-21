<?php 
	$post_info = db_forum::get_full_post_info($_GET['id'], $_SESSION['id']);
	__h1("Moderera inlägg");
	\View\forum::show_post_breadcrumbs($post_info);
	__br();
?>
<div class="single_post_container">
<a id="post<?php echo $post_info['post_id']; ?>"></a>
	<div class="post_top_row">
		<span class="post_date"><?php echo general_helpers::show_date($post_info['posted_time']); ?></span>
		<span class="post_alternatives">
			<?php echo \View\forum::make_post_reference_link($_GET['id']); ?></a> 
		</span>
	</div>
	<div class="post_bottom_row">
		<div class="post_user_info">
			<img src="<?php echo USERIMG_PATH . $post_info['user_image']; ?>" class="post_user_image" width="80"><br>
			<a class="user_name_link" href="index.php?type=member&action=view&id=<?php echo $post_info['user_id']; ?>"><?php echo $post_info['user_full_name']; ?></a>
		</div>		
		<div class="post_content">
			<span id="post_content_<?php echo $post_info['post_id']; ?>"><?php echo Logic\forum::make_html_from_post_text($post_info['content']); ?></span>
			<?php if(isset($post_info['last_edited_time'])) : ?>
				<span class="post_last_edited">Ändrades senast <?php echo strtolower(general_helpers::show_date($post_info['last_edited_time'])); ?>.</span>
			<?php endif; ?>
		</div>
	</div>
	<div style="clear: both;"></div>
</div>
<?php
	__h2("Flytta inlägg till annan tråd");
	__open_form();
	__hidden('move', 1);
	$move_options = db_general::make_hash(db_forum_admin::get_all_topics_for_forum(
		$post_info['forum_id']), 'id', 'title');
	\View\controls::output_selector("topic_id", $move_options);
	__br();
	__submit_and_close("Flytta");

	__h2("Radera inlägg");
	__open_form();
	__hidden('delete', 1);
	__submit_and_close("Radera");

	__h2("Skapa en ny tråd från detta inlägg");
	__open_form();
	__hidden('create_new', 1);
	__textfield("topic_title", "Ny titel");
	__br();
	__submit_and_close("Skapa");

	__h2("Redigera inlägg");
	__open_form();
	__hidden('edit', 1);
	__hidden('post_id', $_GET['id']);
	__textarea("edit_post_content", "Beskrivning", 1, $post_info['content']);
	__submit_and_close("Ändra");
?>
