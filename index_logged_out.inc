<div id="wrap">

<div id="login-column">

<div id="login_image">
	<img src="images/dd120.png">
</div>

<form method="post" id="login-form" action="index.php?login=1">
<input type="hidden" name="login" value="1">
<p>
<label for "username">Användarnamn</label>
<input type="text" name="username" id="username" tabindex="1">
<br><label for "password">Lösenord</label>
<input type="password" name="password" id="password" tabindex="2"></p>
<p><label for "rememberme">Kom ihåg mig<input type="checkbox" name="rememberme" id="rememberme"></label>
<span><input type="submit" value="Logga in"></span>
</p>
</form>

</div>
</div>

<script type="text/javascript" language="JavaScript">
window.setTimeout(function() { document.forms["login-form"]["username"].focus(); },0);
</script>