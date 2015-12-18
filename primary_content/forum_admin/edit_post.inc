<?php 
	$post_info = db_forum::get_full_post_info($_GET['id'], $_SESSION['id']);
	_h1(_t("Moderate post"));
	\View\forum::show_post_breadcrumbs($post_info);
	_br();
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
			<span id="post_content_<?php echo $post_info['post_id']; ?>"><?php echo \View\general::make_html_from_wiki_text($post_info['content']); ?></span>
			<?php if(isset($post_info['last_edited_time'])) : ?>
				<span class="post_last_edited">Ändrades senast <?php echo strtolower(general_helpers::show_date($post_info['last_edited_time'])); ?>.</span>
			<?php endif; ?>
		</div>
	</div>
	<div style="clear: both;"></div>
</div>
<?php
	_h2(_t("Move the post to another thread"));
	_open_form();
	_hidden('move', 1);
	$move_options = db_general::make_hash(db_forum_admin::get_all_topics_for_forum(
		$post_info['forum_id']), 'id', 'title');
	\View\general::make_selector("topic_id", $move_options);
	_br();
	_submit_and_close(_t("Move"));

	_h2(_t("Delete the post"));
	_open_form();
	_hidden('delete', 1);
	_submit_and_close(_t("Delete"));

	_h2(_t("Create a new thread from this post"));
	_open_form();
	_hidden('create_new', 1);
	\View\general::make_textfield("topic_title", _t("New title"));
	_br();
	_submit_and_close(_t("Create"));

	_h2(_t("Edit post"));
	_open_form();
	_hidden('edit', 1);
	_hidden('post_id', $_GET['id']);
	\View\general::make_textarea("edit_post_content", _t("Description"), 1, $post_info['content']);
	_submit_and_close(_t("Edit"));
?>
