<?php 
	__h1("Medlemsavgifter");
?>

<form method="post" action="" class="standard-form">
	<fieldset>
		<legend>Välj användare</legend>
		<select name="user_id" id="user_id">
			<option value=""></option>
			<?php
				$users = db_user::get_all_ids_full_names_and_social_security_numbers();
				foreach ($users as $user){
					echo "<option value=\"" . $user['id'] . "\">" . $user['full_name'] . " (" . $user['social_security_number'] . ")</option>\n";
				}
			?>
		</select>
		<input type="submit" value="Välj">
	</fieldset>
</form>

<?php if(isset($_POST['user_id'])) : ?>
	<?php
		