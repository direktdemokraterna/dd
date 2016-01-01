<html><head>
	<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
	<link rel="shortcut icon" href="images/favicon.ico">
	<title>DD - Nya versionen - Setup</title>
</head>
<body>
<div style="margin: 100px;">
<?php
	$pk_foreign_key_path = '../helpers/keys/dd_anon/';
	$pk_filename = $pk_foreign_key_path . 'dd_anon_public_key.txt';
	if (!file_exists($pk_foreign_key_path))
    	mkdir($pk_foreign_key_path, 0777, true);
	file_put_contents($pk_filename, '-- KEY MISSING --');
	include("../init.inc");
	$post_vars = array('key' => DD_PUBLIC_KEY);
	$reply = crypt_helpers::curl_to_anon_server("receive_public_key.php", $post_vars, false);
	if ($reply != 'success')
		throw new \Exception('Failed to send dd_public_key: ' . $reply);
	$dd_anon_public_key = crypt_helpers::curl_to_anon_server("retrieve_public_key.php", null, false);
	if (!file_put_contents($pk_filename, $dd_anon_public_key))
		throw new \Exception('Failed to store public key from dd_anon: ' . $dd_anon_public_key);
	echo 'The system is now ready to run';
?>
</div>
</body>
</html>