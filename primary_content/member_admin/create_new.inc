<h1>Skapa ny medlem</h1>

<form method="post" action="" class="standard-form">
<br><label for "create_member_email">Mejladress</label>
<input type="text" name="email" id="create_member_email">
<br><label for "create_member_username">Användarnamn</label>
<input type="text" name="username" id="create_member_username">
<br><label for "create_member_first_name">Förnamn</label>
<input type="text" name="first_name" id="create_member_first_name">
<br><label for "create_member_last_name">Efternamn</label>
<input type="text" name="last_name" id="create_member_last_name">
<br><label for "create_member_street_address">Gatuadress</label>
<input type="text" name="street_address" id="create_member_street_address">
<br><label for "create_member_zip_code">Postnummer</label>
<input type="text" name="zip_code" id="create_member_zip_code">
<br><label for "create_member_city_address">Postort</label>
<input type="text" name="city_address" id="create_member_city_address">
<br><label for "create_member_county">Kommun</label>
<select name="county" id="create_member_county">
	<?php 
		$counties = db_constituency::get_counties();
		foreach($counties as $row){
			echo "<option value=\"" . $row['kommun'] . "\">" . $row['kommun'] . "</option>";
		}
	?>
</select>
<br><label for "create_member_social_security_number">Personnummer</label>
<input type="text" name="social_security_number" id="create_member_social_security_number">
<br><label for "create_member_skype_name">Skype användarnamn</label>
<input type="text" name="skype_name" id="create_member_skype_name">
<br><input type="submit" name="" id="submit" value="Skapa">
</form>