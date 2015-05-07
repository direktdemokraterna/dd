<?php 

include("helpers/init.inc");

if($_GET['type']=="forum" && $_GET['action']=="show_posts"){
	include("execute_scripts/forum/sort_posts_and_topics.inc");
}
elseif($_GET['type']=="forum" && $_GET['action']=="delete"){
	include("execute_scripts/forum/delete_post.inc");
}

if($_POST){
	include("execute_scripts/execute_scripts.inc");
}

?>
<html><head>

<?php
if(isset($_GET['login']) || isset($_GET['logout']) || (!isset($_SESSION['id']) && isset($_COOKIE['user_token']) && isset($_COOKIE['user_id']))){
	include("helpers/login_logout.inc");
}
?>

<?php include("helpers/load_css.inc"); ?>
<?php include("helpers/load_js.inc"); ?>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<link rel="shortcut icon" href="images/favicon.ico">

<title>DD - Nya versionen</title>

<script>

</script>

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