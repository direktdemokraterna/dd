<html>
	<head>
		<?php
			include("helpers/init.inc");
			include("helpers/load_css.inc");
			include("helpers/load_js.inc");
			include("helpers/session.inc");
		?>
		<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
		<link rel="shortcut icon" href="images/favicon.ico">
		<title>DD - Nya versionen</title>
	</head>
	<body>
		<?php
			session::update_language();
			navigation_helpers::handle_action_request();
			session::login_logout();
			require(isset($_SESSION['id']) ? "index_logged_in.inc" : "index_logged_out.inc");
		?>
	</body>
</html>