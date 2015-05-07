<h1>Redigera medlem</h1>
	
<?php $result = db_user::get_user_data($_GET['id']); ?>

<form method="post" class="standard-form" action="">
<br><label for "email">Mejladress</label>
<input type="text" name="email" value="<?php echo $result['email']; ?>"id="email">
<br><label for "social_security_number">Personnummer</label>
<input type="text" name="social_security_number" value="<?php echo $result['social_security_number']; ?>"id="social_security_number">
<br><label for "username">Användarnamn</label>
<input type="text" name="username" value="<?php echo $result['username']; ?>"id="username">
<br><label for "first_name">Förnamn</label>
<input type="text" name="first_name" value="<?php echo $result['first_name']; ?>"id="first_name">
<br><label for "last_name">Efternamn</label>
<input type="text" name="last_name" value="<?php echo $result['last_name']; ?>"id="last_name">
<br><label for "street_address">Gatuadress</label>
<input type="text" name="street_address" value="<?php echo $result['street_address']; ?>"id="street_address">
<br><label for "zip_code">Postnummer</label>
<input type="text" name="zip_code" value="<?php echo $result['zip_code']; ?>"id="zip_code">
<br><label for "city_address">Postort</label>
<input type="text" name="city_address" value="<?php echo $result['city_address']; ?>"id="city_address">
<br><label for "county">Kommun</label>
<select name="county" id="county">
	<?php 
		$counties = db_helpers::get_counties();
		foreach($counties as $row){
			echo "<option value=\"" . $row['kommun'] . "\"";
			if($result['county'] == $row['kommun']) echo " selected";
			echo ">" . $row['kommun'] . "</option>";
		}
	?>
</select>
<br><label for "skype_name">Skype användarnamn</label>
<input type="text" name="skype_name" value="<?php echo $result['skype_name']; ?>"id="skype_name">
<br><label for "telephone1">Primärt telefonnummer</label>
<input type="text" name="telephone1" value="<?php echo $result['telephone1']; ?>"id="telephone1">
<br><label for "telephone2">Sekundärt telefonnummer</label>
<input type="text" name="telephone2" value="<?php echo $result['telephone2']; ?>"id="telephone2">
<br><input type="submit" name="" id="submit" value="Uppdatera">
</form>

<p><a href="index.php?type=member_admin&action=edit&id=<?php echo $_GET['id']; ?>&change_password=1">Byt lösenord för denna användare</a></p>

<?php if(isset($_SESSION['superuser'])) : ?>
	<p><a href="index.php?type=superadmin&action=edit_admin&id=<?php echo $_GET['id']; ?>">Ställ in administratörsrättigheter för denna användare</a></p>
<?php endif; ?>