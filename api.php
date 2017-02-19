<?php
include("api/forum.inc");

$method = isset($_SERVER['REQUEST_METHOD']) ? $_SERVER['REQUEST_METHOD'] : null;
$path = isset($_SERVER['PATH_INFO']) ? $_SERVER['PATH_INFO'] : null;
$query_string = isset($_SERVER['QUERY_STRING']) ? $_SERVER['QUERY_STRING'] : null;
switch ($path) {
	case '/forum/post/like':
		echo \Api\forum::like_post($_GET["user_id"], $_GET["post_id"]);
		break;
	case '/forum/post/unlike':
		echo \Api\forum::unlike_post($_GET["user_id"], $_GET["post_id"]);
		break;
	default:
		echo "Hej! Jag är ditt personliga REST-API. Jag uppfattade tyvärr inte ditt budskap: " . $path;		
		break;
}
