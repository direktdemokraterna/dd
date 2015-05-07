<?php $forum_info = db_forum_admin::get_forum_info($_GET['id']); ?>

<h1><?php echo $forum_info['title']; ?></h1>

<form class="standard-form" method="post" action="">
<p>
<label for "title">Namn</label>
<input type="text" name="title" id="title" value="<?php echo $forum_info['title']; ?>" tabindex="1">
<br><label for "description">Beskrivning</label>
<textarea name="description" id="description" cols="60" rows="5" tabindex="3"><?php echo $forum_info['description']; ?></textarea>
<br><label for "category">Kategori</label>
<select name="category" id="category">
	<?php 
		$categories = db_forum_admin::list_categories();
		foreach($categories as $row){
			echo "<option value=\"" . $row['id'] . "\"";
			if($forum_info['category_id'] == $row['id']) echo " checked";
			echo ">" . $row['title'] . "</option>";
		}
	?>
</select>
<br><input type="submit" value="Uppdatera" tabindex="4">
</p>
</form>
