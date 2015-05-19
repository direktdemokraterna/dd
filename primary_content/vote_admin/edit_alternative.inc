<?php 
	$alternative_info = db_vote::get_alternative_info($_GET['id']); 
?>

<h1>Redigera omröstningsalternativ</h1>

<form method="post" action="" class="standard-form">

	<input type="hidden" name="alternative_id" value="<?php echo $alternative_info['id']; ?>">

	<?php if(isset($alternative_info['user_id'])) : ?>

		<label for "username">Användare</label>
		<input type="text" name="username" id="username" value="<?php echo $alternative_info['alternative_title']; ?>" disabled><br>

	<?php else : ?>

		<label for "title">Titel</label>
		<input type="text" name="title" id="title" value="<?php echo $alternative_info['alternative_title']; ?>" ><br>

	<?php endif; ?>

	<label for "description">Beskrivning</label>
	<textarea name="description" id="description"><?php echo $alternative_info['alternative_description']; ?></textarea>

	<input type="submit" value="Uppdatera">

</form>



