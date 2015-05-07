<h1>Lägg till kalenderhändelse</h1>

<form method="post" class="calendar_form" action="">

<br><label for "year">Datum</label>
<input type="text" value="<?php echo date("Y"); ?>" name="year" id="year">

<select name="month" id="month">
	<option value="1"<?php if(date("n") == 1) echo " selected"; ?>>Januari</option>
	<option value="2"<?php if(date("n") == 2) echo " selected"; ?>>Februari</option>
	<option value="3"<?php if(date("n") == 3) echo " selected"; ?>>Mars</option>
	<option value="4"<?php if(date("n") == 4) echo " selected"; ?>>April</option>
	<option value="5"<?php if(date("n") == 5) echo " selected"; ?>>Maj</option>
	<option value="6"<?php if(date("n") == 6) echo " selected"; ?>>Juni</option>
	<option value="7"<?php if(date("n") == 7) echo " selected"; ?>>Juli</option>
	<option value="8"<?php if(date("n") == 8) echo " selected"; ?>>Augusti</option>
	<option value="9"<?php if(date("n") == 9) echo " selected"; ?>>September</option>
	<option value="10"<?php if(date("n") == 10) echo " selected"; ?>>Oktober</option>
	<option value="11"<?php if(date("n") == 11) echo " selected"; ?>>November</option>
	<option value="12"<?php if(date("n") == 12) echo " selected"; ?>>December</option>
</select>

<select name="day" id="day">
	<?php for($i=1; $i<32; $i++) : ?>
		<option value="<?php echo $i; ?>"<?php if(date("j") == $i) echo " selected"; ?>><?php echo $i; ?></option>
	<?php endfor; ?>
</select>

<br><label for "time">Tidpunkt</label>
<input type="text" value="" name="time" id="time" style="width: 200px;">

<br><label for "location">Plats</label>
<select name="location" id="location">
	<option value="Internet" selected>Internet</option>
	<?php 
		$counties = db_helpers::get_counties();
		foreach($counties as $row){
			echo "<option value=\"" . $row['kommun'] . "\">" . $row['kommun'] . "</option>";
		}
	?>
</select>

<br><label for "title">Rubrik</label>
<input type="text" value="" name="title" id="title" style="width: 200px;">

<br><label for "content">Beskrivning</label>
<textarea name="content" id="content" cols="60" rows="5"></textarea>

<p>Kryssa för om du vill att händelsen ska upprepas under flera dagar i rad, varje dag i flera veckor eller varje dag i flera månader:</p>

<div class="checkbox_div">
	<label for "repeat_per_day">Per dag</label>
	<div class="checkbox_inner_div">
		<input type="radio" name="repeat_type" value="day" id="repeat_per_day">
	</div>
</div>
<div class="checkbox_div">
	<label for "repeat_per_week">Per vecka</label>
	<div class="checkbox_inner_div">
		<input type="radio" name="repeat_type" value="week" id="repeat_per_week">
	</div>
</div>
<div class="checkbox_div">
	<label for "repeat_per_month">Per månad</label>
	<div class="checkbox_inner_div">
		<input type="radio" name="repeat_type" value="month" id="repeat_per_month">
	</div>
</div>

<br><label for "repeat_number">Antal upprepningar</label>
<select name="repeat_number" id="repeat_number">
	<?php for($i=2; $i<53; $i++) : ?>
		<option value="<?php echo $i; ?>"><?php echo $i; ?></option>
	<?php endfor; ?>
</select>

<p>2 upprepningar innebär att händelsen läggs 2 gånger i kalendern, t ex den här veckan och samma tid nästa vecka (om Per vecka har valts). Fler upprepningar ger fler händelser i kalendern enligt samma princip.</p>

<input type="submit" id="submit" value="Lägg till">

</form>