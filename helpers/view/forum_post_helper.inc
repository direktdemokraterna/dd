<?php
namespace View;
class forum_post_helper 
{
	public static function make_post($post_info, $page) {
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
		self::make_internal_link('#' . $post_info['post_id'], "forum", "show_posts", "id=" . $_GET['id'] . '&page=' . $page);
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
		self::make_internal_link($post_info['user_full_name'], "member", "view", "id=" . $post_info['post_id'], "user_name_link");
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
?>
