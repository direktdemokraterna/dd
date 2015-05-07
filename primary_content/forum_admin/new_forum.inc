<h1>Skapa nytt forum</h1>

<form method="post" action="">
<p>
<label for "title">Namn</label>
<input type="text" name="title" id="title" tabindex="1">
<br><label for "description">Beskrivning</label>
<textarea name="description" id="description" cols="60" rows="5" tabindex="3"></textarea>
<br><label for"category">Kategori</label>
<select name="category" id="category">
	<?php 
		$categories = db_forum_admin::list_categories();
		foreach($categories as $row){
			echo "<option value=\"" . $row['id'] . "\">" . $row['title'] . "</option>";
		}
	?>
</select>
<br><label for"access_type">Forumtillgång</label>
<select name="access_type" id="access_type">
	<option value="1">Tillgängligt för alla</option>
	<option value="2">Begränsad tillgång</option>
</select>
<br><input type="submit" value="Skapa" tabindex="4">