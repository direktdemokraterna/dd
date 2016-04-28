<html>
	<head>
		<?php
		ini_set('display_errors', '1');
			include("init.inc");
			include("helpers/load_css.inc");
			include("helpers/load_js.inc");
		?>
		<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
		<link rel="shortcut icon" href="images/favicon.ico">
		<title>DD Medlemssystem ver <?php echo VERSION ?></title>
	</head>
	<body>
		<?php
			session::update_language();
			session::update_acting_as_delegate();
			navigation_helpers::handle_action_request();
			session::login_logout();
			if(isset($_SESSION['id'])){
				$is_active = db_user::is_user_active($_SESSION['id']);
				if($is_active){
					require("index_logged_in.inc");
				}
				else{
					require("index_inactive.inc");
				}
			}
			else{
				require("index_logged_out.inc");
			}
		?>
	</body>
</html>