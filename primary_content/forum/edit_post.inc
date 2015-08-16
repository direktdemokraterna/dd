<?php 
	$post_info = db_forum::get_full_post_info($_GET['id'], $_SESSION['id']);
?>

<h1>Redigera inlägg</h1>

<div class="single_post_container">
<a id="post<?php echo $post_info['post_id']; ?>"></a>
	<div class="post_top_row">
		<span class="post_date"><?php echo general_helpers::show_date($post_info['posted_time']); ?></span>
		<span class="post_alternatives">
			<a href="index.php?type=forum&action=show_posts&id=<?php echo $_GET['id']; ?>#<?php echo $post_info['post_id']; ?>">#<?php echo $post_info['post_id']; ?></a> 
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


<form method="post" action="" id="edit_post_form" class="text-editor">
	<fieldset>
		<legend class="edit_post">Redigera ovanstående inlägg</legend>
		<input type="hidden" name="post_id" value="<?php echo $_GET['id']; ?>">
		<textarea name="edit_post_content" id="edit_post_content" rows="32" cols="30"><?php echo forum_helpers::de_process_post_text($post_info['content']); ?></textarea><br>
		<input type="submit" id="edit_post_submit" value="Ändra">
	</fieldset>
</form>

