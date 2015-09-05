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
			foreach($constituencies as $row){
				echo "<option value=\"" . $row['id'] . "\">" . $row['name'] . "</option>";
			}
		?>
	</select>

	<br><label for "title">Titel</label>
	<input type="text" name="title" id="title" tabindex="4" value="">

	<br><label for "description">Beskrivning</label>
	<textarea name="description" id="description" tabindex="5"></textarea>


	<br><label for "year">Omröstningen slutar</label>
	<input type="text" value="<?php echo date("Y", time()+14*24*3600); ?>" name="year" id="year" style="width: 50px;">

	<select name="month" id="month" style="width: 100px;">
		<option value="1"<?php if(date("n", time()+14*24*3600) == 1) echo " selected"; ?>>Januari</option>
		<option value="2"<?php if(date("n", time()+14*24*3600) == 2) echo " selected"; ?>>Februari</option>
		<option value="3"<?php if(date("n", time()+14*24*3600) == 3) echo " selected"; ?>>Mars</option>
		<option value="4"<?php if(date("n", time()+14*24*3600) == 4) echo " selected"; ?>>April</option>
		<option value="5"<?php if(date("n", time()+14*24*3600) == 5) echo " selected"; ?>>Maj</option>
		<option value="6"<?php if(date("n", time()+14*24*3600) == 6) echo " selected"; ?>>Juni</option>
		<option value="7"<?php if(date("n", time()+14*24*3600) == 7) echo " selected"; ?>>Juli</option>
		<option value="8"<?php if(date("n", time()+14*24*3600) == 8) echo " selected"; ?>>Augusti</option>
		<option value="9"<?php if(date("n", time()+14*24*3600) == 9) echo " selected"; ?>>September</option>
		<option value="10"<?php if(date("n", time()+14*24*3600) == 10) echo " selected"; ?>>Oktober</option>
		<option value="11"<?php if(date("n", time()+14*24*3600) == 11) echo " selected"; ?>>November</option>
		<option value="12"<?php if(date("n", time()+14*24*3600) == 12) echo " selected"; ?>>December</option>
	</select>

	<select name="day" id="day" style="width: 50px; margin-right: 12px;">
		<?php for($i=1; $i<32; $i++) : ?>
			<option value="<?php echo $i; ?>"<?php if(date("j", time()+14*24*3600) == $i) echo " selected"; ?>><?php echo $i; ?></option>
		<?php endfor; ?>
	</select>

	Kl.
	<input type="text" value="<?php echo date("G", time()+14*24*3600); ?>" name="hour" id="hour" style="width: 30px;">
	: <input type="text" value="<?php echo date("i", time()+14*24*3600); ?>" name="minute" id="minute" style="width: 30px;">

	<p>Delegatomröstning avslutas efter halva omröstningstiden. Om detta inte är lämpligt finns möjligheten att gå in och ändra delegatomröstningstiden efter att omröstningen har skapats.</p>

	<br><input type="submit" name="" id="submit" value="Skapa" tabindex="6">

</form>