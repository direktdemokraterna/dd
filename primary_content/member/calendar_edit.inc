<?php
	
	$calendar_info = db_calendar::get_event($_GET['id']);

?>

<?php if($calendar_info['user_id'] == $_SESSION['id'] && $calendar_info['timestamp'] > time()) : ?>

<h1>Ändra kalenderhändelse</h1>

<form method="post" class="calendar_form" action="">

<br><label for "year">Datum</label>
<input type="text" value="<?php echo $calendar_info['year']; ?>" name="year" id="year">

<select name="month" id="month">
	<option value="1"<?php if($calendar_info['month'] == 1) echo " selected"; ?>>Januari</option>
	<option value="2"<?php if($calendar_info['month'] == 2) echo " selected"; ?>>Februari</option>
	<option value="3"<?php if($calendar_info['month'] == 3) echo " selected"; ?>>Mars</option>
	<option value="4"<?php if($calendar_info['month'] == 4) echo " selected"; ?>>April</option>
	<option value="5"<?php if($calendar_info['month'] == 5) echo " selected"; ?>>Maj</option>
	<option value="6"<?php if($calendar_info['month'] == 6) echo " selected"; ?>>Juni</option>
	<option value="7"<?php if($calendar_info['month'] == 7) echo " selected"; ?>>Juli</option>
	<option value="8"<?php if($calendar_info['month'] == 8) echo " selected"; ?>>Augusti</option>
	<option value="9"<?php if($calendar_info['month'] == 9) echo " selected"; ?>>September</option>
	<option value="10"<?php if($calendar_info['month'] == 10) echo " selected"; ?>>Oktober</option>
	<option value="11"<?php if($calendar_info['month'] == 11) echo " selected"; ?>>November</option>
	<option value="12"<?php if($calendar_info['month'] == 12) echo " selected"; ?>>December</option>
</select>

<select name="day" id="day">
	<?php for($i=1; $i<32; $i++) : ?>
		<option value="<?php echo $i; ?>"<?php if($calendar_info['day'] == $i) echo " selected"; ?>><?php echo $i; ?></option>
	<?php endfor; ?>
</select>

<br><label for "time">Tidpunkt</label>
<input type="text" value="<?php echo $calendar_info['time']; ?>" name="time" id="time" style="width: 200px;">

<br><label for "location">Plats</label>
<select name="location" id="location">
	<option value="Internet"<?php if($calendar_info['location'] == "Internet") echo " selected"; ?>>Internet</option>
	<?php 
		$counties = db_helpers::get_counties();
		foreach($counties as $row){
			echo "<option value=\"" . $row['kommun'] . "\"";
			if($calendar_info['location'] == $row['kommun']) echo " selected";
			echo ">" . $row['kommun'] . "</option>";
		}
	?>
</select>

<br><label for "title">Rubrik</label>
<input type="text" value="<?php echo $calendar_info['title']; ?>" name="title" id="title" style="width: 200px;">

<br><label for "content">Beskrivning</label>
<textarea name="content" id="content" cols="60" rows="5"><?php echo forum_helpers::de_process_text($calendar_info['content']); ?></textarea>

<input type="submit" id="submit" value="Ändra">

</form>


<?php else : ?>
	Du kan inte ändra den kalenderhändelsen.
<?php endif; ?>