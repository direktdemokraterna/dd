<?php 
	$post_info = db_forum::get_full_post_info($_GET['id'], $_SESSION['id']);
	$forum_info = db_forum::get_forum_from_post($_GET['id']);
?>

<h1>Moderera inlägg</h1>

<div class="forum_info">
	<a href="index.php?type=forum&action=show_forums=1">Forum</a> > 
	<a href="index.php?type=forum&action=show_topics&id=<?php echo $forum_info['forum_id']; ?>"><?php echo $forum_info['forum_title']; ?></a> > 
	<a href="index.php?type=forum&action=show_posts&post_id=<?php echo $_GET['id']; ?>"><?php echo $post_info['title']; ?></a>
</div>
<br>
<div class="single_post_container">
<a id="post<?php echo $post_info['post_id']; ?>"></a>
	<div class="post_top_row">
		<span class="post_date"><?php echo general_helpers::show_date($post_info['posted_time']); ?></span>
		<span class="post_alternatives">
			<a href="index.php?type=forum&action=show_posts&post_id=<?php echo $_GET['id']; ?>&page=<?php echo $page; ?>#<?php echo $post_info['post_id']; ?>">#<?php echo $post_info['post_id']; ?></a> 
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

<h2>Radera inlägg</h2>
<form method="post" action="" class="standard-form">
	<input type="hidden" name="delete" value="1">
	<input type="submit" value="Radera">
</form>

<h2>Flytta inlägget till annan tråd</h2>
<form method="post" action="" class="standard-form">
	<input type="hidden" name="move" value="1">
	<select name="topic_id" id="topic_id">
		<?php 
			$topics = db_forum_admin::get_all_topics_for_forum($post_info['forum_id']);
			foreach($topics as $row){
				echo "<option value=\"" . $row['id'] . "\">" . $row['title'] . "</option>";
			}
		?>
	</select>
	<br><input type="submit" value="Flytta">
</form>

<h2>Skapa ny tråd av detta inlägg</h2>
<form method="post" action="" class="standard-form">
	<input type="hidden" name="create_new" value="1">
	<label for "topic_title">Ny titel</label>
	<input type="text" name="topic_title" id="topic_title">
	<br><input type="submit" value="Skapa">
</form>


<form method="post" action="" id="edit_post_form" class="text-editor">
	<fieldset>
		<legend class="edit_post">Redigera ovanstående inlägg</legend>
		<input type="hidden" name="edit" value="1">
		<input type="hidden" name="post_id" value="<?php echo $_GET['id']; ?>">
		<textarea name="edit_post_content" id="edit_post_content" rows="32" cols="30"><?php echo forum_helpers::de_process_post_text($post_info['content']); ?></textarea><br>
		<input type="submit" id="edit_post_submit" value="Redigera">
	</fieldset>
</form>

