<?php
	namespace Api;

	include("helpers/util.inc");
	include("../../config.inc");
	include("helpers/db/db.inc");
	include("helpers/db/db_forum.inc");

	class forum {
		public static function like_post($user_id, $post_id, $flavor) {
		    if (!preg_match('/critical|neutral|supportive/', $flavor)) {
                http_response_code(400);
		        return ["error" => "Invalid input"];
            }
			$new_likes = \db_forum::like_post($user_id, $post_id, $flavor);
			return $new_likes;
		}

		public static function unlike_post($user_id, $post_id) {
			$new_likes = \db_forum::unlike_post($user_id, $post_id);
			return $new_likes;
		}
	}
?>