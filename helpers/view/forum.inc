<?php
namespace View;

class forum 
{
	public static function output_back_link() {
		switch ($_GET['from_action']) {
			case 'search':
				\View\general::output_internal_link("Tillbaka till sökresultat",
					$_GET['type'], $_GET['from_action']);
				echo '<br>';
			default:
				throw new \Exception("Unknown from_action: " . $_GET('from_action'));
		}
	}

	public static function show_topic_breadcrumbs($topic_id) 
	{
		$forum_info = \db_forum::get_forum_from_post($topic_id);
		general::open_div("forum_info");
		general::output_internal_link("Forum", "forum", "show_forums");
		echo "&nbsp;>&nbsp;";
		general::output_internal_link($forum_info['forum_title'], "forum", "show_topics", "id=" . $forum_info['forum_id']);
		general::close_div();
	} 

	public static function show_topic_title($topic_id) 
	{
		$topic_title = \db_forum::get_title($topic_id);
		echo "<h1>" . $topic_title . "</h1>";
	} 

	public static function show_posts($url_without_page, $page, $posts, $post_count) 
	{
		$paging_info = Paging_info::create($page, $post_count);
		self::show_paging_row($url_without_page, $paging_info);
		foreach($posts as $post_info)
			self::output_post($post_info);			
		self::show_paging_row($url_without_page, $paging_info);
	}

	private static function show_paging_row($url_without_page, $paging_info) 
	{
		general::open_div("post_count_info");
		general::open_span("post_counter");
		echo "Visar inlägg " . $paging_info->first_showed_post_number . " - " . $paging_info->last_showed_post_number . " av totalt " . $paging_info->post_count;
		general::close_span();
		if ($paging_info->post_count > POSTS_PER_PAGE) {
			general::open_span("post_page_chooser");
			\forum_helpers::output_page_links($paging_info->number_of_pages, $paging_info->page, 
				$url_without_page . "&page=");
			general::close_span();
		}
		general::close_div();
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
			general::output_internal_link("Moderera", "forum_admin", "edit_post", "id=" . $post_id);
			echo '&nbsp;';
		}
		if($user_id == $_SESSION['id']) {
			if(\Logic\forum::is_recent_post($post_info)) {
				general::output_internal_link("Radera", "forum", "delete", "id=" . $post_id
					, null, "Vill du verkligen radera inlägget?");
				echo '&nbsp;';
				general::output_internal_link("Redigera", "forum", "edit", "id=" . $post_id);
				echo '&nbsp;';
			}
			else{
				general::output_internal_link("Tillägg", "forum", "add", "id=" . $post_id);
				echo '&nbsp;';
			}
		}
		general::output_internal_link("Anmäl", "forum", "report", "id=" . $post_id);
		echo '&nbsp;';
		echo '<a onMouseDown="quote_post(' . $post_id . ')" style="user-select: none;" unselectable="on">Citera</a>&nbsp;'; 
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
		general::output_internal_link($post_info['user_full_name'], "member", "view", "id=" . 
			$post_info['user_id'], "user_name_link");
		general::close_div();
	}

	private static function make_post_content($post_info) 
	{
		$post_id = $post_info['post_id'];
		general::open_div("post_content");
		echo '<span>' . \View\general::make_html_from_wiki_text($post_info['content']) . '</span>';
		if(isset($post_info['last_edited_time']))
			echo('<span class="post_last_edited">Ändrades senast ' . 
				strtolower(\general_helpers::show_date($post_info['last_edited_time'])) . '.</span>');			
		general::close_div();
	}

	private static function make_post_content_bbcode($post_info) 
	{
		$post_id = $post_info['post_id'];
		echo '<input type="hidden" id="post_content_' . $post_id . '" value="' . 
		self::escape_double_quotes($post_info['content']) . '"/>';
	}

	private static function escape_double_quotes($text) {
		$text = str_replace("\"", "&quot;", $text);
		return $text;
	}

	private static function output_topic_link_for_post($post_info)
	{
		$is_first_post = $post_info['topic_id'] == $post_info['post_id'];
		echo $is_first_post ? ' trådstart: ' : ' som svar till: ';
		general::output_internal_link($post_info['title'], "forum", "show_posts", "topic_id=" . 
			$post_info['topic_id'] . self::get_from_action_for_url());
		echo '&nbsp;';
	}

	public static function make_post_reference_link($post_id) 
	{
		$post_element_id = self::make_post_element_id($post_id);
		general::output_internal_link('#' . $post_id, "forum", "show_posts", "post_id=" . 
			$post_id . self::get_from_action_for_url()	. '#' . $post_element_id);
		echo '&nbsp;';
	}

	public static function output_text_editor($name, $title, $target_id, $content, $submit_text, $tab_index = 1) {
		$form_name = $name . '_form';
		$content_name = $name . '_content';
		$submit_name = $name . '_content';
		echo '<form method="post" action="" id="' . $form_name . '" class="text-editor">';
		echo '<fieldset>';
		echo '<legend>' . $title . '</legend>';
		echo '<input type="hidden" name="target_id" value="' . $target_id . '">';
		echo '<div id="format_buttons_div">';
		echo '<input type="button" id="format_buttons_b" accesskey="b" title="Fet" value="b" onClick="make_bold(\'' . $content_name . '\')">';
		echo '<input type="button" id="format_buttons_i" accesskey="i" title="Kursiv" value="i" onClick="make_italic(\'' . $content_name . '\')">';
		echo '<input type="button" id="format_buttons_u" accesskey="u" title="Understruken" value="u" onClick="make_underline(\'' . $content_name . '\')">';
		echo '</div>';
		echo '<textarea name="' . $content_name . '" id="' . $content_name . '" tabindex="' . $tab_index . '">' . 
		 $content . '</textarea><br>';
		echo '<input type="submit" id="' . $submit_name . '" value="' . $submit_text . '" tabindex="' . ($tab_index + 1) . '">';
		echo '</fieldset>';
		echo '</form>';
	}

	private static function get_from_action_for_url() {
		return \View\general::get_from_action_for_url(array('search'));
	}
}

class Paging_info 
{
	public $page;
	public $post_count;
	public $number_of_pages;
	public $first_showed_post_number;
	public $last_showed_post_number;

	public static function create($page, $post_count) {
		$instance = new Paging_info();
		$instance->page = $page;
		$instance->post_count = $post_count;
		$instance->number_of_pages = ceil($post_count / POSTS_PER_PAGE);
		$instance->first_showed_post_number = 1 + ($page - 1) * POSTS_PER_PAGE;
		$instance->last_showed_post_number = min($page * POSTS_PER_PAGE, $post_count);
		return $instance;
	}
}
?>
