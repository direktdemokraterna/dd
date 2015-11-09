<?php 
	$workgroup = db_workgroup::get_info($_GET['id']);
	if($workgroup['is_restricted'] > 0){
		$constituency_id = db_vote::get_constituency_id_for_vote($workgroup['is_restricted']);
	}
?>

<h1>Administrera arbetsgruppen <?php \View\general::output_internal_link($workgroup['title'], 'workgroup', 'view', 'id=' . $_GET['id']); ?></h1>

<form method="post" action="" class="standard-form">
	<p>

	<label for "workgroup_type">Typ av arbetsgrupp</label>
	<input type="radio" name="is_restricted" id="is_restricted" value="0" tabindex="1" <?php if($workgroup['is_restricted']==0) echo "checked"; ?>>Öppen
	<input type="radio" name="is_restricted" id="is_restricted" value="1" tabindex="2" <?php if($workgroup['is_restricted']>0) echo "checked"; ?>>Stängd
	<br>

	<label for "title">Namn på arbetsgrupp</label>
	<input type="text" name="title" id="title" value="<?php echo $workgroup['title']; ?>" tabindex="4">
	<br>

	<?php if($workgroup['is_restricted']) : ?>
		<label for "number_of_members">Antal medlemmar</label>
		<input type="text" name="number_of_members" id="number_of_members" value="<?php echo $workgroup['number_of_members']; ?>" tabindex="5">
		<br>
	<?php endif; ?>
	<input type="submit" value="Ändra" tabindex="7">
</form>
<?php
	\View\forum::output_text_editor('edit_description', 'Beskrivning av arbetsgruppen', $_GET['id'], $workgroup['description'], "Ändra");
?>

<form method="post" action="" class="standard-form">

	<input type="hidden" name="delete" value="1">
	<input type="submit" value="Ta bort" tabindex="8" onclick="return confirm('Vill du verkligen ta bort den här arbetsgruppen?');">
	<p>
	Borttagande av arbetsgrupp kan inte ångras.
	</p>
</form>
