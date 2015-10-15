
<?php $user_settings = db_user::get_user_data($_SESSION['id']); ?>

	<h1>Ändra din profil</h1>

	<h2>Ändra uppgifter</h2>
	<form method="post" class="standard-form" action="">
	<br><label for "settings_first_name">Förnamn</label>
	<input type="text" value="<?php echo $user_settings['first_name']; ?>" name="first_name" id="settings_first_name">
	<br><label for "settings_last_name">Efternamn</label>
	<input type="text" value="<?php echo $user_settings['last_name']; ?>" name="last_name" id="settings_last_name">
	<br><label for "settings_street_address">Gatuadress</label>
	<input type="text" value="<?php echo $user_settings['street_address']; ?>" name="street_address" id="settings_street_address">
	<br><label for "settings_zip_code">Postnummer</label>
	<input type="text" value="<?php echo $user_settings['zip_code']; ?>" name="zip_code" id="settings_zip_code">
	<br><label for "settings_city_address">Postort</label>
	<input type="text" value="<?php echo $user_settings['city_address']; ?>" name="city_address" id="settings_city_address">
	<br><label for "settings_county">Kommun</label>
	<select name="county" id="settings_county">
		<?php 
			$counties = db_error::get_counties();
			foreach($counties as $row){
				echo "<option value=\"" . $row['kommun'] . "\"";
				if($row['kommun']==$user_settings['county']) echo " selected";
				echo ">" . $row['kommun'] . "</option>";
			}
		?>
	</select>
	<br><label for "settings_email">Mejladress</label>
	<input type="text" value="<?php echo $user_settings['email']; ?>" name="email" id="settings_email">
	<br><label for "settings_skype_name">Skype användarnamn</label>
	<input type="text" value="<?php echo $user_settings['skype_name']; ?>" name="skype_name" id="settings_skype_name">
	<br><label for "settings_telephone1">Telefonnummer</label>
	<input type="text" value="<?php echo $user_settings['telephone1']; ?>" name="telephone1" id="settings_telephone1">
	<br><label for "settings_telephone2">Annat telefonnummer</label>
	<input type="text" value="<?php echo $user_settings['telephone2']; ?>" name="telephone2" id="settings_telephone2">
	<input type="hidden" name="form_type" value="profile">
	<br><input type="submit" id="settings_submit" value="Ändra">
	</form>


	<h2>Ändra presentation</h2>
	<form class="standard-form" method="post" action="">
	<br><label for "settings_description">Personlig presentation (synlig för andra medlemmar)</label>
	<textarea name="settings_description" id="settings_description"><?php echo forum_helpers::de_process_text($user_settings['description']); ?></textarea>
	<input type="hidden" name="form_type" value="description">
	<br><input type="submit" id="settings_submit" value="Ändra">
	</form>


	<h2>Ändra presentationsbild</h2>
	<form enctype="multipart/form-data" class="standard-form" method="post" action="">
	<br><label for "settings_image">Personlig bild (jpg, gif eller png)</label>
	<input type="file" name="image" value="" id="settings_image">
	<br><br><label>Nuvarande bild:</label>
	<br><img class="image150" src="<?php echo USERIMG_PATH . $user_settings['image']; ?>">
	<input type="hidden" name="form_type" value="image">
	<br><input type="submit" id="settings_submit" value="Ändra">
	</form>


	<h2>Ändra inställningar</h2>
	<form class="standard-form" method="post" action="">
	<br><label for "settings_show_email">Visa mejladress</label>
	<input type="checkbox" name="show_email" value="1" id="settings_show_email" <?php if($user_settings['show_email']) echo "checked"; ?>>
	<br><label for "settings_show_telephone">Visa telefonnummer</label>
	<input type="checkbox" name="show_telephone" value="1" id="settings_show_telephone" <?php if($user_settings['show_telephone']) echo "checked"; ?>>
	<br><label for "settings_show_skype">Visa Skype-namn</label>
	<input type="checkbox" name="show_skype" value="1" id="settings_show_skype" <?php if($user_settings['show_skype']) echo "checked"; ?>>
	<input type="hidden" name="form_type" value="settings">
	<br><input type="submit" id="settings_submit" value="Ändra">
	</form>


	<h2>Ändra lösenord</h2>
	<form class="standard-form" method="post" action="">
	<br><label for "settings_old_password">Gammalt lösenord</label>
	<input type="password" name="old_password" id="settings_old_password">
	<br><label for "settings_new_password1">Nytt lösenord</label>
	<input type="password" name="new_password1" id="settings_new_password1">
	<br><label for "settings_new_password2">Upprepa nytt lösenord</label>
	<input type="password" name="new_password2" id="settings_new_password2">
	<input type="hidden" name="form_type" value="password">
	<br><input type="submit" id="settings_submit" value="Ändra">
	</form>
