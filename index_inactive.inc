<?php
	if (isset($_POST['activation'])) {
		$ok = db_user::activate_user($_SESSION['id']);
		if($ok){
			$_SESSION['report_message'] = "Din användare är nu aktiverad.";
			$redirect = "index.php";
		}
	}	
?>
<div id="wrap">

<div class="login-column">
<div class="login_image">
	<img src="images/dd120.png">
</div>

<form method="post" class="login-form" action="">
	<input type="hidden" name="activation" value="1">
	
	<?php $user_first_name = db_user::get_activation_first_name($_SESSION['id']); ?>

	<p>Hej <?php echo $user_first_name; ?>!</p>

	<p>För att din användare ska aktiveras i det nya medlemssystemet måste du godkänna följande villkor: </p>

	<ul>
		<li>Dina personuppgifter lagras i systemets databas i enlighet med PUL</li>
		<li>Medlemsadministratören kan se dina personuppgifter i databasen</li>
		<li>Ditt för- och efternamn samt din folkbokföringskommun visas för andra medlemmar</li>
	</ul>

	<p>Om du godkänner detta kommer du att få tillgång till systemet och du blir synlig för andra medlemmar i systemet.</p>

	<input type="hidden" name="activation_code" value="<?php echo $_GET['code']; ?>">
	<input type="submit" value="Jag godkänner">
</form>

</div>
</div>

<script type="text/javascript" language="JavaScript">
window.setTimeout(function() { document.forms["login-form"]["username"].focus(); },0);
</script>