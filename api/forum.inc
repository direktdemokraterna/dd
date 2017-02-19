<?php
	namespace Api;

	include("/helpers/util.inc");
	include("/config.inc");
	include("/helpers/db/db.inc");
	include("/helpers/db/db_forum.inc");

	class forum {
		public static function like_post($user_id, $post_id) {
			$like_count = \db_forum::like_post($user_id, $post_id);
			return $like_count;
		}

		public static function unlike_post($user_id, $post_id) {
			$like_count = \db_forum::unlike_post($user_id, $post_id);
			return $like_count;
		}
	}
?>