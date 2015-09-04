<?php 
	$voteinfo = db_vote::get_vote_info($_GET['id']); 
	$user_allowed_to_vote = db_constituency::check_user_constituency_access($_SESSION['id'], $voteinfo['constituency_id']);
?>

<?php if($user_allowed_to_vote) : ?>

	<?php if($voteinfo['type'] == "prio-vote") : ?>

		<h1>Lägg till alternativ till omröstningen: <?php echo $voteinfo['title']; ?></h1>

		<p><a href="index.php?type=vote&action=view_vote&id=<?php echo $voteinfo['vote_id']; ?>">Tillbaka till omröstningen.</a></p>

		<P>Här kan du skapa fler omröstningsalternativ till ovanstående prioritetsomröstning. Notera att när du skapat ett alternativ kan det inte tas bort annat än av en omröstningsadministratör.</P>

		<form method="post" action="" class="standard-form">
			<input type="hidden" name="vote_id" value="<?php echo $voteinfo['vote_id']; ?>">

			<label for "alternative_title">Titel</label>
			<input type="text" name="alternative_title" id="alternative_title" tabindex="1"><br>

			<label for "alternative_description">Beskrivning</label>
			<textarea name="alternative_description" id="alternative_description" tabindex="2"></textarea>

			<input type="submit" value="Skapa alternativ" tabindex="3">
		</form>

	<?php elseif($voteinfo['type'] == "candidate-election" || $voteinfo['type'] == "workgroup-election") : ?>

		<?php if(!db_vote::is_user_candidate_in_vote($_SESSION['id'], $_GET['id'])) : ?>

			<h1>Anmäl dig som kandidat i omröstningen: <?php echo $voteinfo['title']; ?></h1>

			<p><a href="index.php?type=vote&action=view_vote&id=<?php echo $voteinfo['vote_id']; ?>">Tillbaka till omröstningen.</a></p>

			<form method="post" action="" class="standard-form">
				<input type="hidden" name="vote_id" value="<?php echo $voteinfo['vote_id']; ?>">

				<label for "alternative_description">Kandidatbeskrivning</label>
				<textarea name="alternative_description" id="alternative_description" tabindex="1"></textarea>

				<input type="submit" value="Kandidera" tabindex="2">
			</form>

		<?php else : ?>

			<form method="post" action="" class="standard-form">
				<input type="hidden" name="vote_id" value="<?php echo $voteinfo['vote_id']; ?>">

				<p>Ta bort din kandidatur i omröstningen: <?php echo $voteinfo['title']; ?></p>

				<input type="submit" value="Ta bort kandidatur">
			</form>

		<?php endif; ?>			

	<?php endif; ?>

<?php endif; ?>