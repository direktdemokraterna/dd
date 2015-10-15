<?php 
	$application_data = db_user::get_user_application($_GET['id']);

	$suggested_username = strtolower($application_data['first_name'] . $application_data['last_name']);
	$suggested_username = str_replace(Array("å", "ä", "ö", "é"), Array("a", "a", "o", "e"), $suggested_username);

	if(db_user::get_user_id($suggested_username)){
		for($i=2; $i<1000; $i++){
			$suggested_username_with_number = $suggested_username . $i;
			if(!db_user::get_user_id($suggested_username_with_number)){
				break;
			}
		}
		$suggested_username = $suggested_username_with_number;
	}
?>

<h1>Processa ansökan från <?php echo $application_data['full_name']; ?></h1>

<form method="post" action="" class="standard-form">
	<p>
	<input type="hidden" name="accept" value="1">

	<br><label for "username">Användarnamn</label>
	<input type="text" name="username" id="username" value="<?php echo $suggested_username; ?>" style="background: #E8E8E8; color: #B0B0B0;" disabled>

	<br><label for "first_name">Förnamn</label>
	<input type="text" name="first_name" id="first_name" value="<?php echo $application_data['first_name']; ?>" tabindex="2">

	<br><label for "last_name">Efternamn</label>
	<input type="text" name="last_name" id="last_name" value="<?php echo $application_data['last_name']; ?>" tabindex="3">

	<br><label for "street_address">Gatuadress</label>
	<input type="text" name="street_address" id="street_address" value="<?php echo $application_data['street_address']; ?>" tabindex="4">

	<br><label for "zip_code">Postnummer</label>
	<input type="text" name="zip_code" id="zip_code" value="<?php echo $application_data['zip_code']; ?>" tabindex="5">

	<br><label for "city_address">Postort</label>
	<input type="text" name="city_address" id="city_address" value="<?php echo $application_data['city_address']; ?>" tabindex="6">

	<br><label for "county">Kommun</label>
	<select name="county" id="county" tabindex="7">
		<?php 
			$counties = db_error::get_counties();
			foreach($counties as $row){
				echo "<option value=\"" . $row['kommun'] . "\"";
				if($row['kommun'] == $application_data['county']) echo " selected";
				echo ">" . $row['kommun'] . "</option>";
			}
		?>
	</select>

	<br><label for "telephone">Telefon</label>
	<input type="text" name="telephone" id="telephone" value="<?php echo $application_data['telephone1']; ?>" tabindex="8">

	<br><label for "email">E-post</label>
	<input type="text" name="email" id="email" value="<?php echo $application_data['email']; ?>" tabindex="9">

	<br><label for "social_security_number">Personnummer</label>
	<input type="text" name="social_security_number" value="<?php echo $application_data['social_security_number']; ?>" id="social_security_number" tabindex="10">

	<br><input type="submit" name="" id="submit" value="Registrera som medlem">
	</p>
</form>

<form method="post" action="" class="standard-form">
	<p>
	<input type="hidden" name="reject" value="1">
	<br><input type="submit" name="" id="submit" value="Avslå ansökan">
	</p>
</form>
