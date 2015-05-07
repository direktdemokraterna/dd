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
	<table class="forum_list">
	<?php $i = 0; ?>
	<?php foreach($sub_forums as $row) : ?>
		<tr><td class="forum_list_<?php if($i++ % 2 == 0) echo "even"; else echo "odd"; ?>">
			<a href="index.php?type=forum_admin&action=edit_forum&id=<?php echo $row['forum_id']; ?>"><?php echo $row['forum_name']; ?></a>
			<br><?php echo $row['number_of topics']; ?> ämnen, <?php echo $row['number_of posts']; ?> inlägg
		</td>
		<td class="forum_list_<?php if($i++ % 2 == 0) echo "even"; else echo "odd"; ?>">
			<a href="index.php?type=forum&action=show_post&id=<?php echo $row['last_posted_id']; ?>"><?php echo $row['post_title']; ?></a>
			<br>av <a href="index.php?type=member&action=view&id=<?php echo $row['user_id']; ?>"><?php echo $row['full_name']; ?></a> <?php echo general_helpers::show_date($row['last_posted_time']); ?>
		</td></tr>
	<?php endforeach; ?>
	</table>
<?php else : ?>
	Inga underforum
<?php endif; ?>