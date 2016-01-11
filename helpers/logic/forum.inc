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

	public static function make_html_from_post_text($wiki_text) {
		try {
			return self::replace_brackets_with_html_tags($wiki_text);
		}
		catch (\Exception $ex) {
			return "ERROR WHEN PARSING TEXT: " . $ex;
		}
	}

	public static function set_post_content ($post_id, $text, $action = "new")
	{
		$processed_post_content = self::process_post_text($text);
		return empty($processed_post_content)
			? false
			: db_forum::add_content_to_post($post_id, $processed_post_content, $action);
	}

	private static function process_post_text ($text)
	{
		$processed_text = \Logic\text::process_text($text);
		$processed_text = str_replace("[/quote]\r\n\r\n", "[/quote]\r\n", $processed_text);
		try {
			$processed_text = self::replace_brackets_with_html_tags($processed_text);
		}
		catch (\Exception $ex) {
			\Logic\util::report_error(_t("Malformed text in post"));
			return null;
		}
		return $processed_text;
	}

	private static function replace_brackets_with_html_tags($wiki_text) {
		$html_text = \Logic\text::replace_brackets_with_html_tags($wiki_text);
		$html_text = self::replace_quotes($html_text);
		return $html_text;
	}

	private static function replace_quotes($wiki_text)
	{
		$number_of_unnamed_quotes = 0;
		$html_text = $wiki_text;
		$html_text = str_replace("[quote]", "<div class='quote_in_post'>"
			, $html_text, $number_of_unnamed_quotes);	
		$html_text = self::replace_named_open_quotes($html_text, $number_of_named_quotes);	
		$html_text = str_replace("[/quote]", "</div>", $html_text, $number_of_closed_quotes);
		if ($number_of_unnamed_quotes + $number_of_named_quotes != $number_of_closed_quotes)
			throw new \Exception('Malformed quotes, mismatching open and close tags');
		return $html_text;
	}

	private static function replace_named_open_quotes($html_text, &$count) {
		$html_text = preg_replace_callback("/\\[quote=(\d+)\\]/i", 
			function ($matches) {
				return "<div class=\"quote_in_post\"><a class=\"quote_in_post_link\" href=\"index.	php?type=forum&action=show_posts&post_id=$matches[1]#post$matches[1]\">" .
				self::get_name_of_poster($matches[1]) . " skrev:</a><br><br>";
			}, $html_text, -1, $count);
		return $html_text;	
	}

	private static function get_name_of_poster($post_id) {
		$post_info = \db_forum::get_post_info($post_id);
		return $post_info['full_name'];
	}

	private static function get_page_from_post_number($number) {
		return ceil($number / POSTS_PER_PAGE);
	}
	
	private static function insert_post_content($post_id, $post_content) 
	{
		$processed_content = \Logic\text::process_text($post_content);
		$ok = \db_forum::add_content_to_post($post_id, $processed_content);
		if($ok){
			$_SESSION['report_message'] = _t("Post created.");
			$redirect = "index.php?type=forum&action=show_posts&post_id=" . $post_id . "#post" . $post_id;
		}
		else 
			\Logic\util::report_error(_t("The post could not be created."));
	}
}
