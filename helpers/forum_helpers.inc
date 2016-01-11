<?php

class forum_helpers 
{
	public static function make_html_from_post_text($wiki_text) {
		try {
			$html_text = self::replace_brackets_with_html_tags($wiki_text);
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
		$processed_text = \View\general::process_text($text);
		$processed_text = str_replace("[/quote]\r\n\r\n", "[/quote]\r\n", $processed_text);
		try {
			self::replace_brackets_with_html_tags($text);
		}
		catch (\Exception $ex) {
			\Logic\util::report_error(_t("Malformed text in post"));
			return null;
		}
		return $processed_text;
	}

	private static function replace_brackets_with_html_tags($wiki_text) {
		$html_text = \View\general::replace_brackets_with_html_tags($wiki_text);
		$html_text = self::replace_quotes($html_text);
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
}