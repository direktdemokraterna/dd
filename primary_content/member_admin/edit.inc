<?php 
	\View\general::output_internal_link('<- Tillbaka till Visa användare', 'member', 'view', 'id=' . $_GET['id']);
?>
<h1>Redigera medlem</h1>
	
<?php 
	$user_data = db_user::get_user_data($_GET['id']);
	if($user_data['deletion_time'])
		echo "<p>Denna användare ströks från medlemslistan " . 
	general_helpers::show_date($user_data['deletion_time']) . ".</p>";
?>

<form method="post" class="standard-form" action="">
<input type="hidden" name="edit_user" value="1">
<?php
	\View\member::output_edit_fields($user_data);
?>
<br><input type="submit" name="" id="submit" value="Uppdatera">
</form>

<form method="post" action="" class="standard-form" onsubmit="confirm('Vill du verkligen ersätta lösenordet för denna användare med ett automatgenererat lösenord?');">
	<input type="hidden" name="change_password" value="1">
	<input type="hidden" name="username" value="<?php echo $user_data['username']; ?>">
	<input type="hidden" name="user_email" value="<?php echo $user_data['email']; ?>">
	<input type="submit" value="Generera nytt lösenord" style="width: auto;">
</form>
