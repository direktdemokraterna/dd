<?php 
	__h1("Registrera inbetalning");
    __open_form();
?>
	<fieldset>
		<legend>Registrera inbetalning</legend>
		<label for "amount">Inbetald summa</label>
		<input type="text" name="amount" id="amount">
		<br>
		<label for "accounting_day">Inbetalningsdag</label>
		<input type="text" name="accounting_day" id="accounting_day" value="<?php echo date("Y") . "-" . date("m") . "-" . date("d"); ?>">
		<br>
		<label for "comment_from_admin">Beskrivning av inbetalningen</label>
		<input type="text" name="comment_from_admin" id="comment_from_admin">
		<br>
		<label for "comment_from_bank">Beskrivning från avsändaren (texten på bankutdraget)</label>
		<input type="text" name="comment_from_bank" id="comment_from_bank">
		<br>
		<label for "user_id">Användare (lämna blankt om inbetalningen inte kommer från en specifik användare)</label>
		<select name="user_id" id="user_id">
			<option value=""></option>
			<?php
				$users = db_user::get_all_ids_full_names_and_social_security_numbers();
				foreach ($users as $user){
					echo "<option value=\"" . $user['id'] . "\">" . $user['full_name'] . " (" . $user['social_security_number'] . ")</option>\n";
				}
			?>
		</select>
		<br>
		<button type="submit" value="Registrera">Registrera</button>
	</fieldset>
</form>
