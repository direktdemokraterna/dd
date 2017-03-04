<?php
include("../includes/api/forum.inc");

$method = isset($_SERVER['REQUEST_METHOD']) ? $_SERVER['REQUEST_METHOD'] : null;
$path = isset($_SERVER['PATH_INFO']) ? $_SERVER['PATH_INFO'] : null;
$query_string = isset($_SERVER['QUERY_STRING']) ? $_SERVER['QUERY_STRING'] : null;
session_start();
if ($_SESSION['csrf_token'] !== $_POST['csrf_token']) {
    http_response_code(401);
    echo json_encode(["error" => "CSRF-fel"]);
}
switch ($path) {
	case '/forum/post/like':
		$new_likes = \Api\forum::like_post($_GET["user_id"], $_GET["post_id"], $_GET["flavor"]);
		echo json_encode($new_likes);
		break;
	case '/forum/post/unlike':
		$new_likes = \Api\forum::unlike_post($_GET["user_id"], $_GET["post_id"]);
		echo json_encode($new_likes);
		break;
	default:
		echo "Hej! Jag är ditt personliga REST-API. Jag uppfattade tyvärr inte ditt budskap: " . $path;		
		break;
}
