<?php
    __open_form("text-editor");
?>
	<fieldset>
		<legend class="create_new_topic">Skapa ny arbetsgrupp</legend>
		<label for "title">Arbetsgruppens namn</label>
		<input type="text" name="title" id="title">
		<br>
		<label for "description">Beskrivning av arbetsgruppen</label>
		<textarea name="description" id="description" cols="60" rows="10"></textarea>
		<br>
		<button type="submit" value="Skapa">Skapa</button>
	</fieldset>
</form>
<?php
	__p("Arbetsgrupper kan skapas av tre medlemmar tillsammans. Genom att fylla i ovanstående uppgifter kan du föreslå en arbetsgrupp. När tre medlemmar stöder denna föreslagna arbetsgrupp kommer den att förvandlas till en riktig arbetsgrupp.");
?>
