<?php
	if (isset($_COOKIE['error'])) {
		echo '<div class="red_message">' . $_COOKIE['error'] . '</div>';
		unset($_COOKIE['error']);
	}
?>
<div id="wrap">

<div class="login-column">
<div>
	<?php \View\index::output_language_buttons(); ?>
</div>
<div class="login_image">
	<img src="images/dd120.png">
</div>

<form method="post" class="login-form" action="index.php?login=1">
<input type="hidden" name="login" value="1">
<p>
<label for "username"><?php __t("Username"); ?></label>
<input type="text" name="username" id="username" tabindex="1">
<br><label for "password"><?php __t("Password"); ?></label>
<input type="password" name="password" id="password" tabindex="2"></p>
<p><label for "rememberme"><?php __t("Remember me"); ?><input type="checkbox" name="rememberme" id="rememberme"></label>
<span><input type="submit" value="<?php __t("Login"); ?>"></span>
</p>
</form>

</div>
</div>

<script type="text/javascript" language="JavaScript">
window.setTimeout(function() { document.forms["login-form"]["username"].focus(); },0);
</script>