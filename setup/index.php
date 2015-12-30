<html><head>
	<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
	<link rel="shortcut icon" href="images/favicon.ico">
	<title>DD - Nya versionen</title>
</head>
<body>
<div style="margin: 100px;">
<?php
	include("../init.inc");
	$post_vars = array('key' => DD_PUBLIC_KEY);
	$reply = crypt_helpers::curl_to_anon_server("receive_public_key.php", $post_vars, false);
	echo $reply == 'success'
		? 'The system is now ready to run'
		: 'Something went wrong during setup: ' . $reply;
?>
</div>
</body>
</html>