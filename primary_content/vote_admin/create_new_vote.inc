<h1>Skapa ny omröstning</h1>
<form method="post" action="" class="standard-form">
	<label for "type_of_vote">Typ av omröstning</label>
	<select name="type_of_vote" id="type_of_vote" tabindex="1">
		<option value="yes-no">Votering (ja/nej)</option>
		<option value="prio-vote">Prioritetsomröstning</option>
		<option value="candidate-election">Personval</option>
		<option value="median">Medianomröstning</option>
		<option value="budget">Budgetomröstning</option>
	</select>
	<br><label for "vote_status">Omröstningslängd</label>
	<select name="vote_status" id="vote_status" tabindex="2">
		<option value="active">Tidsbegränsad</option>
		<option value="continuous">Kontinuerlig</option>
	</select>
	<br><label for "constituency_id">Valkrets</label>
	<select name="constituency_id" id="constituency_id" tabindex="3">
		<?php 
			$constituencies = db_constituency::get_all_constituencies(1, PHP_INT_MAX);
			foreach($constituencies as $row)
				echo "<option value=\"" . $row['id'] . "\">" . $row['name'] . "</option>";
		?>
	</select>
	<br><label for "title">Titel</label>
	<input type="text" name="title" id="title" tabindex="4" value="">
	<br><label for "description">Beskrivning</label>
	<textarea name="description" id="description" tabindex="5"></textarea>
	<br><label for "year">Omröstningen slutar</label>
	<?php 
		\View\vote_helper::make_vote_end_time_select(time() + \View\vote_helper::get_two_weeks_in_seconds()); 
	?>
	<p>Delegatomröstning avslutas efter halva omröstningstiden. Om detta inte är lämpligt finns möjligheten att gå in och ändra delegatomröstningstiden efter att omröstningen har skapats.</p>
	<br><input type="submit" name="" id="submit" value="Skapa" tabindex="6">
</form>