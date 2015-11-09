<?php 
	$post_info = db_forum::get_full_post_info($_GET['id'], $_SESSION['id']);
?>

<h1>Redigera inlägg</h1>

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
		<span id="post_content_<?php echo $post_info['post_id']; ?>"><?php echo \forum_helpers::bbcode_to_html($post_info['content']); ?></span>
		<?php if(isset($post_info['last_edited_time'])) : ?>
			<span class="post_last_edited">Ändrades senast <?php echo strtolower(general_helpers::show_date($post_info['last_edited_time'])); ?>.</span>
		<?php endif; ?>
	</div>
	</div>
		
	<div style="clear: both;"></div>
</div>
<?php
	\View\forum::output_rich_text_editor('edit_post', 'Redigera ovanstående inlägg', $_GET['id'], $post_info['content'], "Ändra");
?>
