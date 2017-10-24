<!DOCTYPE html>
<html>
	<head>
		<?php
			ini_set('display_errors', '1');
            require("init.inc");
            require("helpers/load_css.inc");
            require("helpers/load_js.inc");
		?>
		<meta charset="UTF-8" />
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
		<meta name="apple-mobile-web-app-capable" content="yes">
		<meta name="apple-mobile-web-app-title" content="DD Medlem">
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
		<link rel="apple-touch-icon" href="images/touch-icon.png">
		<link rel="shortcut icon" href="images/favicon.ico">
		<title>Direktdemokraterna Medlemssystem. Version <?php echo VERSION ?></title>
	</head>
	<body>
		<?php
			session::update_acting_as_delegate();
			general_helpers::remove_notices();
			navigation_helpers::handle_action_request();
			session::login_logout();
			if(isset($_SESSION['id'])){
				$is_active = db_user::is_user_active($_SESSION['id']);
				if($is_active){
					require("./includes/index_logged_in.inc");
				}
				else{
					require("./includes/index_inactive.inc");
				}
			}
			else{
				require("./includes/index_logged_out.inc");
			}
		?>
	</body>
</html>