<?php 
include("helpers/init.inc");
include("execute_scripts/execute_scripts.inc");
?>
<html><head>
<?php
include("helpers/load_css.inc");
include("helpers/load_js.inc");
if(isset($_GET['login']) || isset($_GET['logout']) || (!isset($_SESSION['id']) && isset($_COOKIE['user_token']) && isset($_COOKIE['user_id']))){
	include("helpers/login_logout.inc");
}
?>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<link rel="shortcut icon" href="images/favicon.ico">
<title>DD - Nya versionen</title>
</head>

<body>

<?php
	if(isset($_SESSION['id'])){
		require("index_logged_in.inc");
	}
	else{
		require("index_logged_out.inc");
	}
?>

</body>
</html>