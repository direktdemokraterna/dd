<?php 
	$workgroup = db_workgroup::get_info($_GET['id']);
?>

<h1>Administrera arbetsgruppen <?php echo $workgroup['title']; ?></h1>

<form method="post" action="" class="standard-form">
	<p>

	<label for "workgroup_type">Typ av arbetsgrupp</label>
	<input type="radio" name="workgroup_type" id="workgroup_type" value="0" <?php if($workgroup['is_restricted']==0) echo "checked"; ?>>Öppen
	<input type="radio" name="workgroup_type" id="workgroup_type" value="1" <?php if($workgroup['is_restricted']==1) echo "checked"; ?>>Stängd
	<br>

	<label for "title">Namn på arbetsgrupp</label>
	<input type="text" name="title" id="title" value="<?php echo $workgroup['title']; ?>">
	<br>

	<?php if($workgroup['is_restricted']) : ?>
		<label for "number_of_members">Antal medlemmar</label>
		<input type="text" name="number_of_members" id="number_of_members" value="<?php echo $workgroup['number_of_members']; ?>">
		<br>
	<?php endif; ?>

	<label for "description">Beskrivning av arbetsgruppen</label>
	<textarea name="description" id="description" cols="60" rows="10"><?php forum_helpers::de_process_text(echo $workgroup['description']); ?></textarea>
	<br>
	<input type="submit" value="Ändra">

</form>