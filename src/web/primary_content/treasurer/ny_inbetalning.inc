<?php 
	__h1("Registrera inbetalning");
	__open_form();
?>
	<fieldset>
		<label for "amount">Inbetald summa</label>
		<input type="text" name="amount" id="amount" tabindex="1">
		<br>
		<label for "accounting_day">Inbetalningsdag</label>
		<input type="text" name="accounting_day" id="accounting_day" value="<?php echo date("Y") . "-" . date("m") . "-" . date("d"); ?>" tabindex="2">
		<br>
		<label for "comment_from_admin">Beskrivning av inbetalningen (kan lämnas blankt)</label>
		<input type="text" name="comment_from_admin" id="comment_from_admin" tabindex="3">
		<br>
		<label for "type_of_transaction">Typ av inbetalning</label>
		<select name="type_of_transaction" id="type_of_transaction" tabindex="4">
			<option value="medlemsavgift">Medlemsinbetalning</option>
			<option value="donation">Donation</option>
			<option value="annan inkomst">annan inkomst</option>
		</select>
		<br>
		<label for "user_id">Användare</label>
		<select name="user_id" id="user_id" tabindex="5">
			<option value="">Ingen användare</option>
			<?php
				$users = db_user::get_all_ids_full_names_and_social_security_numbers();
				foreach ($users as $user){
					echo "<option value=\"" . $user['id'] . "\">" . $user['full_name'] . " (" . $user['social_security_number'] . ")</option>\n";
				}
			?>
		</select>
		<br>
		<button type="submit" value="Registrera" tabindex="6">Registrera</button>
	</fieldset>
</form>
