<?php
namespace View;

class forum 
{
	public static function show_post_breadcrumbs($post_info) 
	{
		self::start_topic_breadcrumbs($post_info['post_id']);
		__space(2);
		__link($post_info['title'], "forum", "show_posts", "post_id=" . $_GET['id']);
		echo '</div>';
	} 

	public static function show_topic_breadcrumbs($post_id) 
	{
		self::start_topic_breadcrumbs($post_id);
		echo '</div>';
	} 

	public static function output_category_selector($selected_category = null) {
		$category_options = \db_general::make_hash(\db_forum_admin::list_categories(), 'id', 'title');
		\View\controls::output_labeled_selector("category", _t("Category"), $category_options, $selected_category);
	}	

	public static function output_topic_list($topics, $page, $topic_count) {
		echo '<div class="principal_list">';
		self::output_topic_paging_row($page, $topic_count);
		self::output_topic_list_top_row();
		foreach($topics as $row) 
			self::output_topic_list_row($row);
		self::output_topic_paging_row($page, $topic_count);
		echo '</div>';
	}

	private static function output_topic_paging_row($page, $list_count) {
		\View\controls::output_paging_row($page, $list_count, _t("topic"));
	}

	private static function output_topic_list_top_row() {
		echo '<div class="topic_list_top_row">';
		echo '<span class="subject_column">' 
			. _t("Topic") . '</span><span class="numerical_column">' 
			. _t("Participants") . '</span><span class="numerical_column">' 
			. _t("Posts") . '</span><span class="last_post_column">' 
			. _t("Latest post") . '</span>';
		echo '<div style="clear: both;"></div>';
		echo '</div>';
	}

	private static function output_topic_list_row($row) {
		$number_of_pages = ceil($row['number_of_posts'] / POSTS_PER_PAGE);
		echo '<div class="topic_list_row">';
		echo '<span class="subject_column">';
		__link($row['topic_title'], 'forum', 'show_posts', 'topic_id=' . $row['topic_id']);
		if($number_of_pages > 1) 
			__link("($number_of_pages)", 'forum', 'sho_posts', 'id=' . $row['topic_id'] 
				. '&page=' . $number_of_pages);
		__br();
		echo '<span class="list_sub_text">' . _t("Started by: ");
		echo \View\member::link($row, 'topic_user_id', 'topic_user_full_name');
		echo '</span>';
		echo '</span>';
		echo '<span class="numerical_column">' . $row['number_of_participants'] . '</span>';
		echo '<span class="numerical_column">' . $row['number_of_posts'] . '</span>';
		echo '<span class="last_post_column">';
		echo \general_helpers::show_date($row['last_posted_time']);
		__br();
		echo '<span class="list_sub_text">' . _t("By: ") . \View\member::link($row, 'last_user_id', 'last_user_full_name');
		echo '</span>';
		echo '</span>';
		echo '<div style="clear: both;"></div>';
		echo '</div>';		
	}

	private static function start_topic_breadcrumbs($post_id) 
	{
		$forum_info = \db_forum::get_forum_from_post($post_id);
		general::open_div("forum_info");
		__link(_t("Forums"), "forum", "show_forums");
		echo _space() . '>' . _space();
		__link($forum_info['forum_title'], "forum", "show_topics", "id=" . $forum_info['forum_id']);
	} 

	public static function show_topic_title($topic_id) 
	{
		$topic_title = \db_forum::get_title($topic_id);
		__h1($topic_title);
	} 

	public static function show_posts($page, $posts, $post_count) 
	{
		self::output_post_paging_row($page, $post_count);
		foreach($posts as $post_info)
			self::output_post($post_info);			
		self::output_post_paging_row($page, $post_count);
	}

	private static function output_post_paging_row($page, $post_count) {
		\View\controls::output_paging_row($page, $post_count, _t("post"));
	}

	public static function output_post($post_info, $show_action_buttons = true) 
	{
		$post_element_id = self::make_post_element_id($post_info['post_id']);
		general::open_div("single_post_container anchor", $post_element_id);
		self::make_post_header($post_info, $show_action_buttons);
		self::make_post_body($post_info);
		echo '<div style="clear: both;"></div>';
		general::close_div();
	}

	private static function make_post_header($post_info, $show_action_buttons) 
	{
		$post_id = $post_info['post_id'];
		$post_element_id = self::make_post_element_id($post_id);
		general::open_div("post_top_row");
		echo '<span class="post_date">' . \general_helpers::show_date($post_info['posted_time']);
		if(in_array($_GET['action'], array("posts_by_user", "search"))){
			self::output_topic_link_for_post($post_info);
		}
		echo '</span>';
		general::open_span("post_alternatives");
		if ($show_action_buttons)
			self::make_post_actions($post_info);
		self::make_post_reference_link($post_id);
		general::close_span();
		general::close_div();
	}

	private static function make_post_element_id($post_id) 
	{
		return 'post' . $post_id;		
	}

	private static function make_post_actions($post_info) 
	{
		$post_id = $post_info['post_id'];
		$user_id = $post_info['user_id'];
		if(isset($_SESSION['is_forum_admin'])) {
			__link(_t("Moderate"), "forum_admin", "edit_post", "id=" . $post_id);
			__space();
		}
		if($user_id == $_SESSION['id']) {
			if(\Logic\forum::is_recent_post($post_info)) {
				__link(_t("Delete"), "forum", "delete", "id=$post_id"
					, null, _t("Do you really want to delete the post?"));
				__space();
				__link(_t("Edit"), "forum", "edit", "id=" . $post_id);
				__space();
			}
			else{
				__link(_t("Addition"), "forum", "add", "id=" . $post_id);
				__space();
			}
		}
		__link(_t("Report"), "forum", "report", "id=" . $post_id);
		__space();
		echo '<a onMouseDown="quote_post(' . $post_id . ')" style="user-select: none;" unselectable="on">' . _t('Quote') . '</a>&nbsp;'; 
	}

	private static function make_post_body($post_info) 
	{
		general::open_div("post_bottom_row");
		self::make_post_user_tag($post_info);
		self::make_post_content($post_info);
		self::make_post_content_bbcode($post_info);
		general::close_div();
	}

	private static function make_post_user_tag($post_info) 
	{
		general::open_div("post_user_info");
		echo '<img src="' . USERIMG_PATH . $post_info['user_image'] . '" class="post_user_image" width="80"><br>';
		__link($post_info['user_full_name'], "member", "view", "id=" . 
			$post_info['user_id'], "user_name_link");
		general::close_div();
	}

	private static function make_post_content($post_info) 
	{
		$post_id = $post_info['post_id'];
		general::open_div("post_content");
		$html = \Logic\forum::make_html_from_post_text($post_info['content']);
		__span($html);
		if(isset($post_info['last_edited_time']))
			__span(_t('Last changed ') . 
				strtolower(\general_helpers::show_date($post_info['last_edited_time']))
				, "post_last_edited");
		general::close_div();
	}

	private static function make_post_content_bbcode($post_info) 
	{
		$post_id = $post_info['post_id'];
		__hidden("post_content_$post_id", self::escape_double_quotes($post_info['content']));
	}

	private static function escape_double_quotes($text) {
		$text = str_replace("\"", "&quot;", $text);
		return $text;
	}

	private static function output_topic_link_for_post($post_info)
	{
		$is_first_post = $post_info['topic_id'] == $post_info['post_id'];
		echo $is_first_post ? _t(' thread start: ') : ' ' . _t('reply to: ');
		__link($post_info['title'], "forum", "show_posts", "topic_id=" . 
			$post_info['topic_id'] . \View\general::get_from_action_for_url(array('search')));
		__space();
	}

	public static function make_post_reference_link($post_id) 
	{
		$post_element_id = self::make_post_element_id($post_id);
		__link('#' . $post_id, "forum", "show_posts", "post_id=" . 
			$post_id . \View\general::get_from_action_for_url(array('search')) 
			. '#' . $post_element_id);
		__space();
	}
}
?>
