<h1>Skapa ny proposition</h1>

<form method="post" action="" class="standard-form">

<br><label for "type_of_vote">Typ av omröstning</label>
<select name="type_of_vote" id="type_of_vote" tabindex="1">
	<option value="yes-no"<?php echo (isset($_POST['type_of_vote']) && $_POST['type_of_vote'] == 'yes-no') ? ' selected' : ''?>>Votering (ja/nej)</option>
	<option value="prio-vote"<?php echo (isset($_POST['type_of_vote']) && $_POST['type_of_vote'] == 'prio-vote') ? ' selected' : ''?>>Prioritetsomröstning</option>
	<option value="candidate-election"<?php echo (isset($_POST['type_of_vote']) && $_POST['type_of_vote'] == 'candidate-election') ? ' selected' : ''?>>Personval</option>
	<option value="median"<?php echo (isset($_POST['type_of_vote']) && $_POST['type_of_vote'] == 'median') ? ' selected' : ''?>>Medianomröstning</option>
	<option value="budget"<?php echo (isset($_POST['type_of_vote']) && $_POST['type_of_vote'] == 'budget') ? ' selected' : ''?>>Budgetomröstning</option>
</select>

<br><label for "constituency_id">Valkrets</label>
<select name="constituency_id" id="constituency_id" tabindex="2">
	<?php 
		$constituencies = db_constituency::get_constituencies_for_user($_SESSION['id']);
		foreach($constituencies as $row){
			echo "<option value=\"" . $row['id'] . "\">" . $row['name'] . "</option>";
		}
	?>
</select>

<br><label for "new_prop_title">Titel</label>
<input type="text" name="new_prop_title" id="new_prop_title" tabindex="3" 
	value="<?php echo isset($_POST['new_prop_title']) ? $_POST['new_prop_title'] : ''?>">

<br><label for "new_prop_description">Beskrivning</label>
<textarea name="new_prop_description" id="new_prop_description" tabindex="4"
	value="<?php echo isset($_POST['new_prop_description']) ? $_POST['new_prop_description'] : ''?>">
</textarea>

<br><input type="submit" name="" id="submit" value="Skicka in" tabindex="5">
</form>
