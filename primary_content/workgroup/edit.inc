<?php 
	$workgroup = db_workgroup::get_info($_GET['id']);
	$is_member = db_workgroup::is_member($workgroup['id'], $_SESSION['id']);
?>

<?php if($is_member) : ?>

	<h1>Redigera arbetsgruppen <?php echo $workgroup['title']; ?></h1>

	<form method="post" action="" class="text-editor">
		<fieldset>
			<legend class="create_new_topic">Ändra beskrivning</legend>
			<input type="hidden" name="confirm_change" value="1">
			<div id="post_buttons_div">
				<input type="button" class="post_buttons" id="post_buttons_b" accesskey="b" title="Fet" value="b" onClick="make_bold('description')">
				<input type="button" class="post_buttons" id="post_buttons_i" accesskey="i" title="Kursiv" value="i" onClick="make_italic('description')">
				<input type="button" class="post_buttons" id="post_buttons_u" accesskey="u" title="Understruken" value="u" onClick="make_underline('description')">
			</div>
			<textarea name="description" id="description" cols="60" rows="10" tabindex="1"><?php echo forum_helpers::de_process_text($workgroup['description']); ?></textarea><br>
			<input type="submit" value="Ändra" tabindex="2">
		</fieldset>
	</form>

<?php else : ?>
	<p>Du är inte medlem i den här arbetsgruppen.</p>
<?php endif; ?>