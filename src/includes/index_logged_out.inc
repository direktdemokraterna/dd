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
                <label for="username">Användarnamn</label>
                <input type="text" name="username" id="username" tabindex="1" autofocus required>
                <br><label for="password">Lösenord</label>
                <input type="password" name="password" id="password" tabindex="2" required>
                <label for="rememberme">Kom ihåg mig<input type="checkbox" name="rememberme" id="rememberme"></label>
                <span><button type="submit" value="Login" class="btn-login">Logga in</button></span>
        </form>
        <p class="reset-password small">
            <label>Glömt lösenordet?</label><i class="fa fa-key" aria-hidden="true"></i><a href="aterstall-losenord" id="reset_password">Återställ lösenord</a>
        </p>
        <p class="register-account small"> 
            <label>Inget DD-konto?</label><i class="fa fa-sign-in" aria-hidden="true"></i><a href="bli-medlem" id="register">Skapa DD-konto</a>
        </p>
    </div>
</div>