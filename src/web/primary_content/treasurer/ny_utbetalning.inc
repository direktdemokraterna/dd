<?php 
	__h1("Registrera utbetalning");
    __open_form();
?>
	<fieldset>
		<label for "amount">Utbetald summa</label>
		<input type="text" name="amount" id="amount" tabindex="1">
		<br>
		<label for "type_of_transaction">Typ av utbetalning</label>
		<select name="type_of_transaction" id="type_of_transaction" tabindex="2">
			<option value="övriga utgifter">Övriga utgifter</option>
			<option value="webbutgift">Webbrelaterad utgift</option>
			<option value="finansutgift">Finansiell utgift</option>
			<option value="marknadsföringsutgift">Marknadsföringsutgift</option>
		</select>
		<br>
		<label for "accounting_day">Utbetalningsdag</label>
		<input type="text" name="accounting_day" id="accounting_day" value="<?php echo date("Y") . "-" . date("m") . "-" . date("d"); ?>" tabindex="3">
		<br>
		<label for "comment_from_admin">Beskrivning av utbetalningen</label>
		<input type="text" name="comment_from_admin" id="comment_from_admin" tabindex="4">
		<br>
		<button type="submit" value="Registrera" tabindex="5">Registrera</button>
	</fieldset>
</form>
