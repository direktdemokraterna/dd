<?php 
	__h1("Registrera utbetalning");
    __open_form();
?>
	<fieldset>
		<legend>Registrera utbetalning</legend>
		<label for "amount">Utbetald summa</label>
		<input type="text" name="amount" id="amount">
		<br>
		<label for "type_of_transaction">Typ av utbetalning</label>
		<select name="type_of_transaction" id="type_of_transaction">
			<option value="utbetalning">Utbetalning</option>
		</select>
		<br>
		<label for "accounting_day">Utbetalningsdag</label>
		<input type="text" name="accounting_day" id="accounting_day" value="<?php echo date("Y") . "-" . date("m") . "-" . date("d"); ?>">
		<br>
		<label for "comment_from_admin">Beskrivning av utbetalningen</label>
		<input type="text" name="comment_from_admin" id="comment_from_admin">
		<br>
		<button type="submit" value="Registrera">Registrera</button>
	</fieldset>
</form>
