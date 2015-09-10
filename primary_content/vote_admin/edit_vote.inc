<?php 
	$voteinfo = db_vote::get_vote_info($_GET['id']); 
?>

<h1>Redigera omröstning: <?php echo $voteinfo['title']; ?></h1>

<form method="post" action="" class="standard-form">

	<input type="hidden" name="vote_id" value="<?php echo $voteinfo['vote_id']; ?>">

	<label for "type_of_vote">Typ av omröstning</label>
	<select name="type_of_vote" id="type_of_vote" tabindex="1">
		<option value="yes-no"<?php if($voteinfo['type'] == "yes-no") echo " selected"; ?>>Votering (ja/nej)</option>
		<option value="prio-vote"<?php if($voteinfo['type'] == "prio-vote") echo " selected"; ?>>Prioritetsomröstning</option>
		<option value="candidate-election"<?php if($voteinfo['type'] == "candidate-election") echo " selected"; ?>>Personval</option>
		<option value="median"<?php if($voteinfo['type'] == "median") echo " selected"; ?>>Medianomröstning</option>
		<option value="budget"<?php if($voteinfo['type'] == "budget") echo " selected"; ?>>Budgetomröstning</option>
	</select>

	<br><label for "constituency_id">Valkrets</label>
	<select name="constituency_id" id="constituency_id" tabindex="2">
		<?php 
			$constituencies = db_constituency::get_all_constituencies(1, PHP_INT_MAX);
			foreach($constituencies as $row){
				echo "<option value=\"" . $row['id'] . "\"";
				if($voteinfo['constituency_id'] == $row['id']) echo " selected";
				echo ">" . $row['name'] . "</option>";
			}
		?>
	</select>

	<br><label for "title">Titel</label>
	<input type="text" name="title" id="title" tabindex="3" value="<?php echo $voteinfo['title']; ?>">

	<br><label for "description">Beskrivning</label>
	<textarea name="description" id="description" tabindex="4"><?php echo $voteinfo['description']; ?></textarea>

	<br><label for "vote_status">Omröstningens status</label>
	<?php 
		if($voteinfo['status'] == "active") echo "Pågående";
		elseif($voteinfo['status'] == "del_ended") echo "Avslutad för delegater";
		elseif($voteinfo['status'] == "ended") echo "Avslutad";
		elseif($voteinfo['status'] == "continuous") echo "Kontinuerlig";
		elseif($voteinfo['status'] == "finished") echo "Avslutad kontinuerlig";
	?>

	<br>

	<?php if($voteinfo['status'] == "active") : ?>
		<input type="submit" name="end_vote" value="Avsluta omröstningen">
		<input type="submit" name="end_delegate_vote" value="Avsluta delegatomröstningen">
		<input type="submit" name="make_continuous" value="Gör om till kontinuerlig">
	<?php elseif($voteinfo['status'] == "del_ended") : ?>
		<input type="submit" name="end_vote" value="Avsluta omröstningen">
		<input type="submit" name="restore_delegate_vote" value="Återuppta delegatomröstningen">
	<?php elseif($voteinfo['status'] == "ended") : ?>
		<input type="submit" name="restore_vote" value="Återuppta omröstningen">
	<?php elseif($voteinfo['status'] == "continuous") : ?>
		<input type="submit" name="finish_vote" value="Avsluta omröstningen">
		<input type="submit" name="make_active" value="Gör om till tidsbegränsad">
	<?php elseif($voteinfo['status'] == "finished") : ?>
		<input type="submit" name="restore_finished_vote" value="Återuppta omröstningen">
	<?php endif; ?>

	<br><label for "forum_topic_id">Forumtråds-ID</label>
	<input type="text" name="forum_topic_id" id="forum_topic_id" tabindex="5" value="<?php echo $voteinfo['forum_topic_id']; ?>">


	<br><label for "year">Omröstningen slutar</label>
	<input type="text" value="<?php echo date("Y", $voteinfo['timestamp_ended']); ?>" name="year" id="year" style="width: 50px;">

	<select name="month" id="month" style="width: 100px;">
		<option value="1"<?php if(date("n", $voteinfo['timestamp_ended']) == 1) echo " selected"; ?>>Januari</option>
		<option value="2"<?php if(date("n", $voteinfo['timestamp_ended']) == 2) echo " selected"; ?>>Februari</option>
		<option value="3"<?php if(date("n", $voteinfo['timestamp_ended']) == 3) echo " selected"; ?>>Mars</option>
		<option value="4"<?php if(date("n", $voteinfo['timestamp_ended']) == 4) echo " selected"; ?>>April</option>
		<option value="5"<?php if(date("n", $voteinfo['timestamp_ended']) == 5) echo " selected"; ?>>Maj</option>
		<option value="6"<?php if(date("n", $voteinfo['timestamp_ended']) == 6) echo " selected"; ?>>Juni</option>
		<option value="7"<?php if(date("n", $voteinfo['timestamp_ended']) == 7) echo " selected"; ?>>Juli</option>
		<option value="8"<?php if(date("n", $voteinfo['timestamp_ended']) == 8) echo " selected"; ?>>Augusti</option>
		<option value="9"<?php if(date("n", $voteinfo['timestamp_ended']) == 9) echo " selected"; ?>>September</option>
		<option value="10"<?php if(date("n", $voteinfo['timestamp_ended']) == 10) echo " selected"; ?>>Oktober</option>
		<option value="11"<?php if(date("n", $voteinfo['timestamp_ended']) == 11) echo " selected"; ?>>November</option>
		<option value="12"<?php if(date("n", $voteinfo['timestamp_ended']) == 12) echo " selected"; ?>>December</option>
	</select>

	<select name="day" id="day" style="width: 50px; margin-right: 12px;">
		<?php for($i=1; $i<32; $i++) : ?>
			<option value="<?php echo $i; ?>"<?php if(date("j", $voteinfo['timestamp_ended']) == $i) echo " selected"; ?>><?php echo $i; ?></option>
		<?php endfor; ?>
	</select>

	Kl.
	<input type="text" value="<?php echo date("G", $voteinfo['timestamp_ended']); ?>" name="hour" id="hour" style="width: 30px;">
	: <input type="text" value="<?php echo date("i", $voteinfo['timestamp_ended']); ?>" name="minute" id="minute" style="width: 30px;">


	<br><label for "delegate_year">Delegatomröstningen slutar</label>
	<input type="text" value="<?php echo date("Y", $voteinfo['timestamp_delegate_ended']); ?>" name="delegate_year" id="delegate_year" style="width: 50px;">

	<select name="delegate_month" id="delegate_month" style="width: 100px;">
		<option value="1"<?php if(date("n", $voteinfo['timestamp_delegate_ended']) == 1) echo " selected"; ?>>Januari</option>
		<option value="2"<?php if(date("n", $voteinfo['timestamp_delegate_ended']) == 2) echo " selected"; ?>>Februari</option>
		<option value="3"<?php if(date("n", $voteinfo['timestamp_delegate_ended']) == 3) echo " selected"; ?>>Mars</option>
		<option value="4"<?php if(date("n", $voteinfo['timestamp_delegate_ended']) == 4) echo " selected"; ?>>April</option>
		<option value="5"<?php if(date("n", $voteinfo['timestamp_delegate_ended']) == 5) echo " selected"; ?>>Maj</option>
		<option value="6"<?php if(date("n", $voteinfo['timestamp_delegate_ended']) == 6) echo " selected"; ?>>Juni</option>
		<option value="7"<?php if(date("n", $voteinfo['timestamp_delegate_ended']) == 7) echo " selected"; ?>>Juli</option>
		<option value="8"<?php if(date("n", $voteinfo['timestamp_delegate_ended']) == 8) echo " selected"; ?>>Augusti</option>
		<option value="9"<?php if(date("n", $voteinfo['timestamp_delegate_ended']) == 9) echo " selected"; ?>>September</option>
		<option value="10"<?php if(date("n", $voteinfo['timestamp_delegate_ended']) == 10) echo " selected"; ?>>Oktober</option>
		<option value="11"<?php if(date("n", $voteinfo['timestamp_delegate_ended']) == 11) echo " selected"; ?>>November</option>
		<option value="12"<?php if(date("n", $voteinfo['timestamp_delegate_ended']) == 12) echo " selected"; ?>>December</option>
	</select>

	<select name="delegate_day" id="delegate_day" style="width: 50px; margin-right: 12px;">
		<?php for($i=1; $i<32; $i++) : ?>
			<option value="<?php echo $i; ?>"<?php if(date("j", $voteinfo['timestamp_delegate_ended']) == $i) echo " selected"; ?>><?php echo $i; ?></option>
		<?php endfor; ?>
	</select>

	Kl.
	<input type="text" value="<?php echo date("G", $voteinfo['timestamp_delegate_ended']); ?>" name="delegate_hour" id="delegate_hour" style="width: 30px;">
	: <input type="text" value="<?php echo date("i", $voteinfo['timestamp_delegate_ended']); ?>" name="delegate_minute" id="delegate_minute" style="width: 30px;">


	<br><input type="submit" name="update" id="submit" value="Uppdatera" tabindex="7">

</form>