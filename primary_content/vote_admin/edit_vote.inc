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
		<button type="submit" name="action" value="end_vote">Avsluta omröstningen</button>
		<button type="submit" name="action" value="end_delegate_vote">Avsluta delegatomröstningen</button>
		<button type="submit" name="action" value="make_continuous">Gör om till kontinuerlig</button>
	<?php elseif($voteinfo['status'] == "del_ended") : ?>
		<button type="submit" name="action" value="end_vote">Avsluta omröstningen</button>
		<button type="submit" name="action" value="restore_delegate_vote">Återuppta delegatomröstningen</button>
	<?php elseif($voteinfo['status'] == "ended") : ?>
		<button type="submit" name="action" value="restore_vote">Återuppta omröstningen</button>
	<?php elseif($voteinfo['status'] == "continuous") : ?>
		<button type="submit" name="action" value="finish_vote">Avsluta omröstningen</button>
		<button type="submit" name="action" value="make_active">Gör om till tidsbegränsad</button>
	<?php elseif($voteinfo['status'] == "finished") : ?>
		<button type="submit" name="action" value="restore_finished_vote">Återuppta omröstningen</button>
	<?php endif; ?>
	<br><label for "forum_topic_id">Forumtråds-ID</label>
	<input type="text" name="forum_topic_id" id="forum_topic_id" tabindex="5" value="<?php echo $voteinfo['forum_topic_id']; ?>">
	<br><label for "year">Omröstningen slutar</label>
	<?php \View\vote_helper::make_vote_end_time_select($voteinfo['timestamp_ended']); ?>
	<br><label for "delegate_year">Delegatomröstningen slutar</label>
	<?php \View\vote_helper::make_vote_end_time_select($voteinfo['timestamp_delegate_ended'], 'delegate_'); ?>
	<br><input type="submit" name="update" id="submit" value="Uppdatera" tabindex="7">
</form>