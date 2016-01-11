<?php
namespace Logic;

class forum 
{
	public static function is_recent_post($post_info) 
	{
		return $post_info['posted_time'] > (time() - EDIT_POST_TIME_WINDOW_IN_MINUTES*60);
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
			\Logic\util::report_error(_t("You don't have access to that forum."));
	}

	public static function update_county_region_forum_access ($user_id, $county_id)
	{
		$county_forum_id = db_forum::get_local_county_forum($county_id);
		$region_id = db_constituency::get_region_id_from_county_id($county_id);
		$region_forum_id = db_forum::get_local_region_forum($region_id);
		db_forum_admin::drop_local_forums_for_user($user_id);
		db_forum_admin::add_forum_access($user_id, $county_forum_id);
		db_forum_admin::add_forum_access($user_id, $region_forum_id);
	}

	public static function get_requested_topic() {
		return isset($_GET['topic_id']) 
			? $_GET['topic_id']
			: db_forum::get_topic($_GET['post_id']);
	}

	public static function get_requested_page($topic_id) {
		if(isset($_GET['page'])) {
			if ($_GET['page'] == "last"){
				$number_of_posts_in_topic = db_forum::get_number_of_posts($topic_id);
				return self::get_page_from_post_number($number_of_posts_in_topic);
			}
			return $_GET['page'];
		}
		if(isset($_GET['post_id'])){
			$posts_before_this_post = db_forum::count_posts_before_post_id($topic_id, $_GET['post_id']);
			return self::get_page_from_post_number($posts_before_this_post+1);
		}
		return 1;
	}

	private static function get_page_from_post_number($number) {
		return ceil($number / POSTS_PER_PAGE);
	}
	
	private static function insert_post_content($post_id, $post_content) 
	{
		$processed_content = \View\general::process_text($post_content);
		$ok = \db_forum::add_content_to_post($post_id, $processed_content);
		if($ok){
			$_SESSION['report_message'] = _t("Post created.");
			$redirect = "index.php?type=forum&action=show_posts&post_id=" . $post_id . "#post" . $post_id;
		}
		else 
			\Logic\util::report_error(_t("The post could not be created."));
	}
}
