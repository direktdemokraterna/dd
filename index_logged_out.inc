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
<label for "username">Användarnamn</label>
<input type="text" name="username" id="username" tabindex="1">
<br><label for "password">Lösenord</label>
<input type="password" name="password" id="password" tabindex="2"></p>
<p><label for "rememberme">Kom ihåg mig<input type="checkbox" name="rememberme" id="rememberme"></label>
<span><button type="submit" value="Login" class="btn-login">Logga in</button></span>
</p>
</form>
</div>
</div>
