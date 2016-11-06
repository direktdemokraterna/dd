<?php 
include("../init.inc");
session::update_language();

if(isset($_POST['activation_code'])){
	$ok = db_user::activate_user($_POST['activation_code']);

	if($ok){
		$system_message = "Din användare är nu aktiverad. Gå till <a href=\"../index.php\">inloggningssidan</a> för att logga in.";
	}
	else{
		$system_message = "Något gick fel, din användare kunde inte aktiveras. Pröva igen <a href=\"index.php?code=" . $_POST['activation_code'] . "\">här</a> eller försök få tag på någon som har insyn i systemet om problemet kvarstår.";
	}
}
elseif(isset($_POST['user_email'])){
	$email_exists = db_user::check_if_email_exists($_POST['user_email']);

	if($email_exists){
		$activation_code = db_user::get_activation_code_from_email($_POST['user_email']);

		if($activation_code){
			$mail_title = "Aktivera din användare i Direktdemokraternas nya medlemssystem";
			$link_to_activation_page = 
			$mail_content = "Detta mejl skickas till dig eftersom du begärt att få en aktiveringskod för att kunna aktivera din användare i Direktdmeokraternas nya medlemssystem.<br>\n<br>\nKlicka på nedanstående länk för att komma till aktiveringssidan:<br>\n";
			$mail_result = general_helpers::admin_mail($_POST['user_email'], $mail_title, $mail_content);

			if($mail_result == "success"){
				$system_message = "Ett mejl med aktiveringskod har skickats till den angivna adressen. Följ instruktionerna i mejlet för att aktivera ditt konto.";
			}
			else{
				$system_message = "Adressen du angav finns i systemet men något gick fel när mejlet skulle skickas. Gå tillbaka till föregående sida och försök igen eller försök få tag på någon som har insyn i systemet om problemet kvarstår.";
			}
		}
		else{
			$system_message = "Det verkar som om användaren med den mejladressen redan är aktiverad. Gå till <a href=\"../index.php\">inloggningssidan</a> och försök logga in där.";
		}
	}
	else{
		$system_message = "Den mejladressen finns inte registrerad i systemet. Pröva igen <a href=\"index.php?code=" . $_POST['activation_code'] . "\">här</a> eller försök få tag på någon som har insyn i systemet om problemet kvarstår.";
	}
}

?>
<html><head>

<link href="../helpers/css/index.css" rel="stylesheet" type="text/css">
<link href="../helpers/css/login.css" rel="stylesheet" type="text/css">

<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<link rel="shortcut icon" href="images/favicon.ico">

<title>DD Medlemssystem ver <?php echo VERSION ?></title>

</head>

<body>

<div class="wrap">
<div class="login-column">
<div>
	<?php \View\index::output_language_buttons(); ?>
</div>
<div class="login_image">
	<img src="../images/dd120.png">
</div>

<br>

<h1 style="font-size: 24px; font-family: Lato, sans-serif; font-weight: 700; margin-bottom: 30px; ">Aktivera medlem
</h1>
<script src="http://code.jquery.com/jquery-1.11.3.min.js"></script>
<script src="../helpers/js/constituency.js"></script>
<script src="../helpers/js/session.js"></script>

<?php if(isset($system_message)) : ?>
	<?php echo $system_message; ?>
<?php elseif(!empty($_GET['code'])) : ?>
	<?php $user_first_name = db_user::get_first_name_from_activation_code($_GET['code']); ?>
	
	<?php if(!empty($user_first_name)) : ?>
		<form method="post" action="" class="standard-form">
			<p>Hej <?php echo $user_first_name; ?>!</p>

			<p>För att din användare ska aktiveras i det nya medlemssystemet måste du godkänna följande villkor: </p>

			<ul>
				<li>Ditt för- och efternamn samt din folkbokföringskommun visas för andra medlemmar</li>
				<li>Dina övriga personuppgifter lagras i systemets databas men kan bara ses av medlemsadministratören</li>
			</ul>

			<p>Efter att du godkänt detta kommer du att tas till inloggningssidan där du kan logga in med det användarnamn och lösenord som du haft i det tidigare medlemssystemet (WordPress). </p>

			<input type="hidden" name="activation_code" value="<?php echo $_GET['code']; ?>">
			<input type="submit" value="Jag godkänner">
		</form>
	<?php else : ?>
		Aktiveringskoden verkar inte höra ihop med någon användare i systemet. Kanske har du redan blivit aktiverad eller så är koden helt enkelt fel.
	<?php endif; ?>
<?php else : ?>
	<form method="post" action="" class="standard-form">
		<p>Fyll i den mejladress som finns registrerad i systemet för dig i fältet här under. Ett mejl med en aktiveringskod kommer att skickas till den adressen och med hjälp av den kan du sedan aktivera din användare och börja använda det nya systemet.</p>
		<label for "user_email">Mejladress</label>
		<input type="text" name="user_email" id="user_email" value="">
		<input type="submit" value="Skicka">'
	</form>
<?php endif; ?>


<script type="text/javascript" language="JavaScript">
window.setTimeout(function() { document.forms["login-form"]["first_name"].focus(); },0);
</script>

</div>
</div>

</body>
</html>