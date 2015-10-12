<?php
namespace View;

class forum_post_helper 
{
	public static function show_topic_breadcrumbs($topic_id) {
		$forum_info = \db_forum::get_forum_from_post($topic_id);
		self::open_div("forum_info");
		self::make_internal_link("Forum", "forum", "show_forums");
		echo " >&nbsp;";
		self::make_internal_link($forum_info['forum_title'], "forum", "show_topics", "id=" . $forum_info['forum_id']);
		self::close_div();
	} 

	public static function show_topic_title($topic_id) {
		$topic_title = \db_forum::get_title($topic_id);
		echo "<h1>" . $topic_title . "</h1>";
	} 

	public static function show_posts($page, $posts, $post_count) {
		$paging_info = Paging_info::create($page, $post_count);
		self::show_paging_row($paging_info);
		foreach($posts as $post_info) 
			self::make_post($post_info, $page);
		self::show_paging_row($paging_info);
	}

	private static function show_paging_row($paging_info) {
		self::open_div("post_count_info");
		self::open_span("post_counter");
		echo "Visar inlägg " . $paging_info->first_showed_post_number . " - " . $paging_info->last_showed_post_number . " av totalt " . $paging_info->post_count;
		self::close_span();
		if ($paging_info->post_count > POSTS_PER_PAGE) {
			self::open_span("post_page_chooser");
			\forum_helpers::output_page_links($paging_info->number_of_pages, $paging_info->page, 
				"index.php?type=forum&action=show_posts&id=" . $_GET['id'] . "&page=");
			self::close_span();
		}
		self::close_div();
	}

	private static function make_post($post_info, $page) {
		self::open_div("single_post_container");
		self::make_post_header($post_info, $page);
		self::make_post_body($post_info);
		echo '<div style="clear: both;"></div>';
		self::close_div();
	}

	private static function make_post_header($post_info, $page) {
		self::open_div("post_top_row");
		echo '<span class="post_date">' . \general_helpers::show_date($post_info['posted_time']) . '</span>';
		self::open_span("post_alternatives");
		self::make_post_actions($post_info);
		self::make_internal_link('#' . $post_info['post_id'], "forum", "show_posts", "id=" . $post_info['post_id'] . '&page=' . $page);
		self::close_span();
		self::close_div();
	}

	private static function make_post_actions($post_info) {
		$post_id = $post_info['post_id'];
		$user_id = $post_info['user_id'];
		if(isset($_SESSION['is_forum_admin']))
			self::make_internal_link("Moderera", "forum_admin", "edit_post", "id=" . $post_id);
		if($user_id == $_SESSION['id']) {
			if($post_info['posted_time'] > (time() - 10*60)) {
				self::make_internal_link("Radera", "forum", "delete", "id=" . $post_id
					, null, "Vill du verkligen radera inlägget?");
				self::make_internal_link("Redigera", "forum", "edit", "id=" . $post_id);
			}
			else{
				self::make_internal_link("Tillägg", "forum", "add", "id=" . $post_id);
			}
		}
		self::make_internal_link("Anmäl", "forum", "report", "id=" . $post_id);
		echo '<a onMouseDown="quote_post(' . $post_id . ')" style="user-select: none;" unselectable="on">Citera</a>&nbsp;'; 
	}

	private static function make_post_body($post_info) {
		self::open_div("post_bottom_row");
		self::make_post_user_tag($post_info);
		self::make_post_content($post_info);
		self::close_div();
	}

	private static function make_post_user_tag($post_info) {
		self::open_div("post_user_info");
		echo '<img src="' . USERIMG_PATH . $post_info['user_image'] . '" class="post_user_image" width="80"><br>';
		self::make_internal_link($post_info['user_full_name'], "member", "view", "id=" . 
			$post_info['post_id'], "user_name_link");
		self::close_div();
	}

	private static function make_post_content($post_info) {
		$post_id = $post_info['post_id'];
		$user_id = $post_info['post_id'];
		self::open_div("post_content");
		echo '<span id="post_content_' . $post_id . '">' . nl2br($post_info['content']) . '</span>';
		if(isset($post_info['last_edited_time'])) {
			echo('<span class="post_last_edited">Ändrades senast ' . 
				strtolower(\general_helpers::show_date($post_info['last_edited_time'])) . '.</span>');			
		}
		self::close_div();
	}

	private static function open_div($class_name) {
		echo('<div class="' . $class_name . '">' . PHP_EOL);
	}

	private static function open_span($class_name) {
		echo('<span class="' . $class_name . '">' . PHP_EOL);
	}

	private static function close_div() {
		echo('</div>' . PHP_EOL);
	}

	private static function close_span() {
		echo('</span>' . PHP_EOL);
	}

	private static function make_internal_link($label, $type, $action, $params = null, $class = null, $confirm = null) {
		$url = 'index.php?type=' . $type . "&action=" . $action . '"' . (empty($params) ? '' : '&' . $params);
		$href = 'href="' . $url . '"';
		$classAttr = ($class ? ' class="' . $class . '"'  : '');
		$onclick = ($confirm ? " return confirm('" . $confirm . "')" : '');
		echo '<a ' . $classAttr . $href . $onclick . '>' . $label . '</a>&nbsp;'; 
	}
}

class Paging_info {
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
