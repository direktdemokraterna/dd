<?php 
	$post_info = db_forum::get_full_post_info($_GET['id'], $_SESSION['id']);
?>

<h1>Gör ett tillägg till ditt inlägg</h1>

<table class="single_post_table">
	<tr class="single_post_top_row">
		<td class="single_post_top_left_cell"><?php echo general_helpers::show_date($post_info['posted_time']); ?></td>
		<td class="single_post_top_right_cell">
			<a href="index.php?type=forum&action=show_posts&id=<?php echo $_GET['id']; ?>&page=<?php echo $page; ?>#<?php echo $post_info['post_id']; ?>" class="specific_post_link">#<?php echo $post_info['post_id']; ?></a> 
		</td>
	</tr>
	<tr class="single_post_bottom_row">
		<td class="single_post_bottom_left_cell">
			<img src="<?php echo USERIMG_PATH . $post_info['user_image']; ?>" class="post_user_image" width="80"><br>
			<a href="index.php?type=member&action=view&id=<?php echo $post_info['user_id']; ?>"><?php echo $post_info['user_full_name']; ?></a>
		</td>
		<td class="single_post_bottom_right_cell">
			<?php echo nl2br($post_info['content']); ?>
			<?php if(isset($post_info['last_edited_time'])) : ?>
				<br><br>
				<i>Ändrades senast <?php echo strtolower(general_helpers::show_date($post_info['last_edited_time'])); ?>.</i>
			<?php endif; ?>
		</td>
	</tr>
</table>

<form method="post" action="" id="add_to_post_form" class="text-editor">
	<fieldset>
		<legend class="add_to_post">Tillägg till ovanstående inlägg</legend>
		<input type="hidden" name="post_id" value="<?php echo $_GET['id']; ?>">
		<textarea name="add_to_post_content" id="add_to_post_content" rows="32" cols="30"></textarea><br>
		<input type="submit" id="add_to_post_submit" value="Lägg till">
	</fieldset>
</form>

