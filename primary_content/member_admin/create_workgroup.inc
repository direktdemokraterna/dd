<h1>Skapa en ny arbetsgrupp</h1>

<form method="post" action="" class="standard-form">
	<p>
	<label for "title">Namn</label>
	<input type="text" name="title" id="title" tabindex="2"><br>

	<label for "constituency_id">Valkrets</label>
	<select name="constituency_id" id="constituency_id" tabindex="3">
		<?php 
			$constituencies = db_constituency::get_all_constituencies(1, PHP_INT_MAX);
			foreach($constituencies as $row){
				echo "<option value=\"" . $row['id'] . "\">" . $row['name'] . "</option>";
			}
		?>
	</select><br>

	<label for "number_of_members">Antal medlemmar</label>
	<input type="text" name="number_of_members" id="number_of_members" tabindex="4"><br>

	<label for "description">Beskrivning</label>
	<textarea name="description" id="description" tabindex="5"></textarea>

	<input type="submit" value="Skapa" tabindex="6">
	</p>
</form>

<p>	Här skapar man statiska arbetsgrupper, arbetsgrupper vars medlemskap inte är öppet och vars medlemsantal är begränsat. I samband med att arbetsgruppen skapas kommer det också att skapas en kontinuerlig omröstning där medlemmarna i denna arbetsgrupp utses. </p>