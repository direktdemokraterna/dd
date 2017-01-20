<?php 
include("../init.inc");
session::update_language();

if(isset($_POST['reset_token']) && isset($_POST['password'])) {
	$ok = \Logic\resetpassword::change_password($_POST['reset_token'], $_POST['password']);

	if ($ok) {
		$system_message = "Ditt lösenord är nu bytt. Gå till <a href=\"../index.php\">inloggningssidan</a> för att logga in.";
	} else {
		$system_message = "Något gick fel, ditt lösenord kunde inte ändras. Pröva igen <a href=\"index.php?reset_token=" . $_POST['reset_token'] . "\">här</a> eller försök få tag på någon som har insyn i systemet om problemet kvarstår.";
	}
}
elseif (isset($_POST['user_email'])) {
    $send_activation_code_result = \Logic\resetpassword::send_reset_token($_POST['user_email']);

	if ($send_activation_code_result) {
        $system_message = "Ett mejl med återställningskod har skickats till den angivna adressen. Följ instruktionerna i mejlet för att byta ditt lösenord.";
	} else {
		$system_message = "Det gick inte att skicka återställningsmejl. Var god försök igen eller kontakta någon admin för hjälp.";
	}
}

?><!DOCTYPE html>
<html>
<head>
    <link href="../helpers/css/reset.css" rel="stylesheet" type="text/css">
    <link href="../helpers/css/index.css" rel="stylesheet" type="text/css">
	<link href="../helpers/css/login.css" rel="stylesheet" type="text/css">
    <link href="../helpers/font-awesome-4.3.0/css/font-awesome.min.css" rel="stylesheet" type="text/css">
	<meta charset="UTF-8" />
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<link rel="shortcut icon" href="images/favicon.ico">
	<title>DD Medlemssystem ver <?php echo VERSION ?></title>
</head>
<body>

<div id="wrap">
<div class="login-column">
<div>
	<?php \View\index::output_language_buttons(); ?>
</div>
<div class="login_image">
	<img src="../images/dd120.png">
</div>

<br>

<h1 style="font-size: 24px; font-family: Lato, sans-serif; font-weight: 700; margin-bottom: 30px; "><?php __t("Reset password"); ?></h1>
<script src="//code.jquery.com/jquery-1.11.3.min.js"></script>
<script src="../helpers/js/constituency.js"></script>
<script src="../helpers/js/session.js"></script>
<script>
    function validateForm() {
        var password = document.forms["change_password"]["password"].value;
        if (password.length < 8) {
            alert("<?php __t("The password must be at least 8 characters."); ?>");
            return false;
        }
    }
</script>

    <?php if(isset($system_message)) : ?>
	<?php echo $system_message; ?>
<?php elseif(!empty($_GET['reset_token']) && !isset($_POST['password'])) : ?>
	<?php if(\Logic\resetpassword::is_valid_reset_token($_GET['reset_token'])) : ?>
		<form name="change_password" method="post" action="" class="login-form" onsubmit="return validateForm()">
			<p><?php __t("Enter a new password to reset your password."); ?></p>

			<input type="hidden" name="reset_token" value="<?php echo $_GET['reset_token']; ?>">
            <label for="password"><?php __t("New password"); ?></label>
			<input type="password" name="password" id="password" value="" placeholder="<?php __t("New password"); ?>" required autofocus>
			<input type="submit" value="<?php __t("Reset password"); ?>">
		</form>
	<?php else : ?>
        <?php __t("The reset token is invalid"); ?>
	<?php endif; ?>
<?php else : ?>
	<form method="post" action="" class="login-form">
		<p><?php __t("Enter the email address you want to reset the password for. An email with a reset token will be sent to that address. With help of that token you can then change the password for your user."); ?></p><br>
		<label for="user_email"><?php __t("Email"); ?></label>
		<input type="text" name="user_email" id="user_email" value="" autofocus required><br>
        <button type="submit" value="<?php __t("Send"); ?>"><?php __t("Send"); ?></button>
	</form>
<?php endif; ?>


</div>
</div>

</body>
</html>