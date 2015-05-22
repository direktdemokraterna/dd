<?php $cat_info = db_forum_admin::get_category_info($_GET['id']); ?>

<h1><?php echo $cat_info['title']; ?></h1>

<form class="standard-form" method="post" action="">
<p>
<label for "title">Namn</label>
<input type="text" name="title" id="title" value="<?php echo $cat_info['title']; ?>" tabindex="1">
<br><label for "description">Beskrivning</label>
<textarea name="description" id="description" cols="60" rows="5" tabindex="3"><?php echo $cat_info['description']; ?></textarea>
<br><input type="submit" value="Uppdatera" tabindex="4">
</p>
</form>

<h2>Underforum till denna kategori</h2>

<?php $sub_forums = db_forum_admin::list_sub_forums($_GET['id']); ?>

<?php if(!empty($sub_forums)) : ?>
	<?php foreach($sub_forums as $row) : ?>
		<div class="topic_list_row" style="text-align: left;">
			<span class="forum_name">
				<a href="index.php?type=forum_admin&action=edit_forum&id=<?php echo $row['forum_id']; ?>"><?php echo $row['forum_name']; ?></a>
				<br><span class="list_sub_text"><?php echo $row['number_of_topics']; ?> ämnen, <?php echo $row['number_of_posts']; ?> inlägg</span>
			</span>
			<span class="forum_last_post">
				<?php if(isset($row['last_posted_id'])) : ?>
					<?php $post_info = db_forum::get_post_info($row['last_posted_id']); ?>
					<a href="index.php?type=forum_admin&action=edit_topic&id=<?php echo $post_info['topic_id']; ?>"><?php echo $post_info['title']; ?></a>
					<br><span class="list_sub_text">av <a href="index.php?type=member&action=view&id=<?php echo $post_info['user_id']; ?>"><?php echo $post_info['full_name']; ?></a> <?php echo general_helpers::show_date($row['last_posted_time']); ?></span>
				<?php else : ?>
					Inga inlägg
				<?php endif; ?>
			</span>
			<div style="clear: both;"></div>
		</div>
	<?php endforeach; ?>
<?php else : ?>
	Inga underforum
<?php endif; ?>