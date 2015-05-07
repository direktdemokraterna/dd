<h1>Skapa ny proposition</h1>

<form method="post" action="" class="standard-form">

<br><label for "type_of_vote">Typ av omröstning</label>
<select name="type_of_vote" id="type_of_vote" tabindex="1">
	<option value="yes-no">Votering (ja/nej)</option>
	<option value="prio-vote">Prioritetsomröstning</option>
	<option value="candidate-election">Personval</option>
	<option value="median">Medianomröstning</option>
	<option value="budget">Budgetomröstning</option>
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
<input type="text" name="new_prop_title" id="new_prop_title" tabindex="3">

<br><label for "new_prop_description">Beskrivning</label>
<textarea name="new_prop_description" id="new_prop_description" tabindex="4"></textarea>

<br><input type="submit" name="" id="submit" value="Skicka in" tabindex="5">
</form>