<?php
namespace Logic;

class forum 
{
	public static function is_recent_post($post_info) 
	{
		return $post_info['posted_time'] > (time() - 10*60);
	}

	public static function insert_post($topic_id, $post_content) 
	{
		$forum_id = \db_forum::get_forum_from_post_id($topic_id);
		$check_access = \db_forum::check_access($_SESSION['id'], $forum_id);
		if($check_access){
			$post_insert_id = \db_forum::new_post($_SESSION['id'], $topic_id);
			self::insert_post_content($post_insert_id, $post_content);
		}
		else
			\Logic\util::report_error("You don't have access to that forum.");
	}

	private static function insert_post_content($post_id, $post_content) 
	{
		$processed_content = \forum_helpers::process_text($post_content);
		$ok = \db_forum::add_content_to_post($post_id, $processed_content);
		if($ok){
			$_SESSION['report_message'] = "Post created.";
			$redirect = "index.php?type=forum&action=show_posts&post_id=" . $post_id . "#post" . $post_id;
		}
		else 
			\Logic\util::report_error("The post could not be created.");
	}
}
