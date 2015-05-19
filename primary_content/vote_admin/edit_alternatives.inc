<?php 
	$voteinfo = db_vote::get_vote_info($_GET['id']); 

	if($voteinfo['type'] == "prio-vote"){
		$votes_alternatives = db_vote::get_alternatives_for_vote($voteinfo['vote_id']);
	}
	else{
		$votes_alternatives = db_vote::get_candidates_for_vote($voteinfo['vote_id']);
	}
?>

<h1>Redigera omröstningsalternativ för omröstningen: <?php echo $voteinfo['title']; ?></h1>

<form method="post" action="" class="standard-form">

	<input type="hidden" name="delete" value="1">
	<input type="hidden" name="vote_id" value="<?php echo $_GET['id']; ?>">

	<?php foreach($votes_alternatives as $row) : ?>
		<input type="checkbox" name="check_list[]" class="delete_checkbox" value="<?php echo $row['id']; ?>">
		<?php echo $row['title']; ?>
		[<a href="index.php?type=vote_admin&action=edit_alternative&id=<?php echo $row['id']; ?>">Redigera</a>]<br>
	<?php endforeach; ?>

	<br><input type="checkbox" name="checkall" onclick="checkAll(this, 'delete_checkbox');">Markera alla<br>

	<input type="submit" value="Radera markerade">

</form>

<h2>Lägg till alternativ till denna omröstning</h2>

<form method="post" action="" class="standard-form">

	<input type="hidden" name="new_alternative" value="1">
	<input type="hidden" name="vote_id" value="<?php echo $_GET['id']; ?>">

	<?php if($voteinfo['type'] == "prio-vote") : ?>
		<label for "title">Titel</label>
		<input type="text" name="title" id="title"><br>
	<?php else : ?>
		<label for "username">Användarnamn</label>
		<input type="text" name="username" id="username"><br>
	<?php endif; ?>

	<label for "description">Beskrivning</label>
	<textarea name="description" id="description"></textarea>

	<input type="submit" value="Lägg till">

</form>