<?php

class db_forum 
{
	public static function get_posts ($topic_id, $access_user_id, $page = 1, $limit = POSTS_PER_PAGE){
		$limit_clause = db_general::get_limit_clause($page, $limit);
		$query = "select p.id as post_id, p.title as title, p.content as content, p.user_id as user_id, concat(u.first_name, ' ', u.last_name) as user_full_name, p.posted_time as posted_time, p.last_edited_time as last_edited_time, u.image as user_image
					from post p, user u, forum_user fu
					where p.user_id = u.id and p.topic_id = ? 
					and fu.user_id = ? and fu.forum_id = p.forum_id 
					order by posted_time asc " . $limit_clause;
		$values = Array($topic_id, $access_user_id);
		return db::select($query, $values);
	}

	public static function get_last_posts ($num_posts = 10)
	{
		$limit_posts = (int) $num_posts;
		$query = "select p.id as post_id, p.title as post_title, p.posted_time as posted_time, u.id as user_id, concat(u.first_name, ' ', u.last_name) as user_full_name, 
					f.id as forum_id, f.title as forum_title, c.id as cat_id, c.title as cat_title, (select id from post t where t.id = p.topic_id) as topic_id 
					from post p, user u, category c, forum f, forum_user fu 
					where p.user_id = u.id and p.forum_id = f.id and f.category_id = c.id and f.id = fu.forum_id and fu.user_id = ? order by p.posted_time desc limit ".$limit_posts;
		$values = Array($_SESSION['id']);
		return db::select($query, $values);
	}

	public static function get_post_info ($post_id)
	{
		$query = "select p.id as post_id, p.title as title, u.id as user_id, concat(u.first_name, ' ', u.last_name) as full_name, p.forum_id as forum_id, p.topic_id as topic_id, p.posted_time as posted_time
					from post p, user u where u.id = p.user_id and p.id = ?";
		$values = Array($post_id);
		return db::select_single_row($query, $values);
	}

	public static function get_full_post_info ($post_id, $user_id)
	{
		$query = "select p.id as post_id, p.title as title, p.content as content, p.user_id as user_id, concat(u.first_name, ' ', u.last_name) as user_full_name, p.posted_time 		as posted_time, p.last_edited_time as last_edited_time, p.forum_id as forum_id, u.image as user_image
					from post p, user u 
					where u.id = p.user_id and p.id = ? and exists (select * from forum_user where forum_id = p.forum_id and user_id = ?)";
		$values = Array($post_id, $user_id);
		return db::select_single_row($query, $values);
	}

	public static function list_forums ()
	{
		$query = "select c.id as cat_id, c.title as cat_name, f.id as forum_id, f.title as forum_name, f.description as description, f.last_posted_time as last_posted_time, f.					last_posted_post as last_posted_id, f.number_of_topics as number_of_topics, f.number_of_posts as number_of_posts
					from forum f, category c, forum_user fu 
					where c.id = f.category_id and f.id = fu.forum_id and fu.user_id = ?
					order by field(f.access_type, 'public', 'workgroup', 'local_region', 'local_county'), f.category_id asc, f.id asc";
		$values = Array($_SESSION['id']);
		return db::select($query, $values);
	}

	public static function get_public_forum_ids ()
	{
		$query = "select id from forum where access_type = 'public'";
		$values = Array();
		return db::select($query, $values);
	}

	public static function get_forum_info ($forum_id)
	{
		$query = "select f.* from forum f, forum_user fu where fu.user_id = " . $_SESSION['id'] . " and fu.forum_id = f.id and f.id = ?";
		$values = Array($forum_id);
		return db::select_single_row($query, $values);
	}

	public static function get_topic_count ($forum_id)
	{
		$query = "select count(*) from post
					where is_topic = 1 and forum_id = ?";
		$values = Array($forum_id);
		return db::select_single_value($query, $values);
	}

	public static function list_topics ($forum_id, $access_user_id, $page = 1
		, $limit = LIST_ITEMS_PER_PAGE)
	{
		$limit_clause = db_general::get_limit_clause($page, $limit);
		$query = "select p.id as topic_id, p.title as topic_title, u.id as topic_user_id, concat(u.first_name, ' ', u.last_name) as topic_user_full_name, 
					tmi.number_of_posts as number_of_posts, 
					tmi.number_of_participants as number_of_participants, 
					tmi.last_posted_time as last_posted_time, 
					tmi.last_user_id as last_user_id, 
					(select concat(u3.first_name, ' ', u3.last_name) from user u3 where u3.id = last_user_id limit 1) as last_user_full_name
					from post p, user u, forum_user fu, topic_meta_info tmi
					where p.user_id = u.id and p.is_topic = 1 and p.forum_id = ? 
					and fu.user_id = ? and fu.forum_id = p.forum_id 
					and p.id = tmi.topic_id 
					order by last_posted_time desc " . $limit_clause;
		$values = Array($forum_id, $access_user_id);
		return db::select($query, $values);
	}

	public static function check_access ($user_id, $forum_id)
	{
		$query = "select * from forum_user where user_id = ? and forum_id = ?";
		$values = Array($user_id, $forum_id);
		$check = db::select_single_value($query, $values);
		return $check;
	}

	public static function get_post_count ($post_id)
	{
		$query = "select count(*) from post where topic_id = ?";
		$values = Array($post_id);
		return db::select_single_value($query, $values);
	}

	public static function update_forum_post_count ($forum_id)
	{
		$query = "update forum set last_posted_time = (select posted_time from post where forum_id = ? order by posted_time desc limit 1), last_posted_post = (select id from post where forum_id = ? order by posted_time desc limit 1), number_of_topics = (select count(*) from post where is_topic = 1 and forum_id = ?), number_of_posts = (select count(*) from post where forum_id = ?) where id = ?";
		$values = Array($forum_id, $forum_id, $forum_id, $forum_id, $forum_id);
		return db::update($query, $values);
	}

	public static function get_title ($post_id)
	{
		$query = "select title from post where id = ?";
		$values = Array($post_id);
		return db::select_single_value($query, $values);
	}

	public static function get_user_id_from_post ($post_id)
	{
		$query = "select user_id from post where id = ?";
		$values = Array($post_id);
		return db::select_single_value($query, $values);
	}

	public static function get_forum_from_post ($post_id)
	{
		$query = "select f.id as forum_id, f.title as forum_title from post p, forum f where p.forum_id = f.id and p.id = ?";
		$values = Array($post_id);
		return db::select_single_row($query, $values);
	}

	public static function get_forum_id_from_post_id ($post_id)
	{
		$query = "select forum_id from post where id = ?";
		$values = Array($post_id);
		return db::select_single_value($query, $values);
	}

	public static function get_post_count_by_user ($user_id, $access_user_id)
	{
		$query = "select count(*) from post p, forum_user fu where p.user_id = ? and fu.user_id = ? and fu.forum_id = p.forum_id";
		$values = Array($user_id, $access_user_id);
		return db::select_single_value($query, $values);
	}

	public static function get_forum_from_post_id ($post_id)
	{
		$query = "select forum_id from post where id = ?";
		$values = Array($post_id);
		return db::select_single_value($query, $values);
	}

	public static function new_topic ($user_id, $forum_id, $title, $content = "")
	{
		$query = "insert into post (user_id, forum_id, title, is_topic, posted_time, content) values (?, ?, ?, ?, ?, ?)";
		$values = Array($user_id, $forum_id, general_helpers::clean($title), 1, time(), $content);
		$insert_id = db::insert($query, $values);
		if ($insert_id) {
			$query = "update post set topic_id = id where id = ?";
			$values = Array($insert_id);
			db::update($query, $values);
			self::update_post_count($forum_id, $user_id);

			$query = "insert into topic_meta_info (topic_id) values (?)";
			$values = Array($insert_id);
			db::insert($query, $values);
			self::update_topic_meta_info($insert_id);
		}
		return $insert_id;
	}

	public static function update_topic_meta_info ($insert_id)
	{
		$query = "select count(*) from post where topic_id = ?";
		$values = Array($insert_id);
		$number_of_posts = db::select_single_value($query, $values);

		$query = "select count(distinct user_id) from post where topic_id = ?"; 
		$values = Array($insert_id);
		$number_of_participants = db::select_single_value($query, $values);
					
		$query = "select posted_time from post where topic_id = ? order by posted_time desc limit 1"; 
		$values = Array($insert_id);
		$last_posted_time = db::select_single_value($query, $values);
		
		$query = "select user_id from post where topic_id = ? order by posted_time desc limit 1";
		$values = Array($insert_id);
		$last_user_id = db::select_single_value($query, $values);

		$query = "update topic_meta_info set number_of_posts = ?, number_of_participants = ?, last_posted_time = ?, last_user_id = ? where topic_id = ?";
		$values = Array($number_of_posts, $number_of_participants, $last_posted_time, $last_user_id, $insert_id);
		return db::update($query, $values);
	}

	public static function new_post ($user_id, $topic_id, $content = "")
	{
		$topic_info = self::get_post_info($topic_id);
		$query = "insert into post (user_id, topic_id, forum_id, title, is_topic, posted_time, content) values (?, ?, ?, ?, ?, ?, ?)";
		$values = Array($user_id, $topic_id, $topic_info['forum_id'], $topic_info['title'], 0, time(), $content);
		$insert_id = db::insert($query, $values);
		if ($insert_id){
			self::update_post_count($topic_info['forum_id'], $user_id);
			self::update_topic_meta_info($topic_id);
		}
		return $insert_id;
	}

	private static function update_post_count ($forum_id, $user_id)
	{
		self::update_forum_post_count($forum_id);
		self::update_user_post_count($user_id);
	}

	public static function new_report ($post_id, $user_id, $argument)
	{
		$query = "insert into post_report (post_id, reporter_id, time_report_filed, argument) values (?, ?, ?, ?)";
		$values = Array($post_id, $user_id, time(), $argument);
		return db::insert($query, $values);
	}

	public static function get_topic ($post_id)
	{
		$query = "select topic_id from post where id = ?";
		$values = Array($post_id);
		return db::select_single_value($query, $values);
	}

	public static function get_number_of_posts ($topic_id)
	{
		$query = "select count(*) from post where topic_id = ?";
		$values = Array($topic_id);
		return db::select_single_value($query, $values);
	}

	public static function delete_post ($post_id)
	{
		$post_info = self::get_post_info($post_id);
		$query = "delete from post where id = ?";
		$values = Array($post_id);
		$return = db::delete($query, $values);
		self::update_forum_post_count($post_info['forum_id']);
		self::update_user_post_count($post_info['user_id']);
		self::update_topic_meta_info($post_info['topic_id']);
		return $return;
	}

	public static function count_posts_before_post_id ($topic_id, $post_id)
	{
		$query = "select count(*) from post where topic_id = ? and id < ?";
		$values = Array($topic_id, $post_id);
		return db::select_single_value($query, $values);
	}

	public static function add_content_to_post ($post_id, $content, $edit = "new")
	{
		$is_add = $edit == "add";
		$is_new = $edit == "new";
		$new_content_expression = $is_add
			? "concat(content, ?)"
			: "?"; //new, update
		$last_edited_expression = $is_new
			? ""
			: ", last_edited_time = ?"; //add, update
		$query = "update post set content = " 
			. $new_content_expression 
			. $last_edited_expression
			. " where id = ?";
		$values = $is_add
			? Array($content, $post_id)
			: Array($content, time(), $post_id);
		return db::update($query, $values);
	}

	public static function update_user_post_count ($user_id)
	{
		$query = "update user set number_of_posts = (select count(*) from post where user_id = ?), number_of_topics = (select count(*) from post where is_topic = 1 and user_id = ?)  where id = ?";
		$values = Array($user_id, $user_id, $user_id);
		return db::update($query, $values);
	}

	public static function get_posts_by_user ($user_id, $access_user_id, $page = 1, $limit = POSTS_PER_PAGE)
	{
		$limit_clause = db_general::get_limit_clause($page, $limit);
		$query = "select p.id as post_id, p.title as title, p.content as content, p.user_id as user_id, concat(u.first_name, ' ', u.last_name) as user_full_name, p.posted_time 				as posted_time, p.last_edited_time as last_edited_time, p.topic_id as topic_id, u.image as user_image
					from post p, user u, forum_user fu 
					where p.user_id = u.id and p.user_id = ? 
					and fu.user_id = ? and fu.forum_id = p.forum_id 
					order by posted_time asc " . $limit_clause;
		$values = Array($user_id, $access_user_id);
		return db::select($query, $values);
	}

	public static function get_topics_by_user ($user_id, $access_user_id, $page = 1, $limit = POSTS_PER_PAGE)
	{
		$limit_clause = db_general::get_limit_clause($page, $limit);
		$query = "select p.id as topic_id, p.title as topic_title, u.id as topic_user_id, concat(u.first_name, ' ', u.last_name) as topic_user_full_name, 
					(select count(*) from post p2 where p2.topic_id = p.id) as number_of_posts, 
					(select count(distinct user_id) from post p3 where p3.topic_id = p.id) as number_of_participants, 
					(select p4.posted_time from post p4 where p4.topic_id = p.id order by p4.posted_time desc limit 1) as last_posted_time, 
					(select u2.id from post p5, user u2 where p5.user_id = u2.id and p5.topic_id = p.id order by p5.posted_time desc limit 1) as last_user_id, 
					(select concat(u3.first_name, ' ', u3.last_name) from post p6, user u3 where p6.user_id = u3.id and p6.topic_id = p.id order by p6.posted_time desc limit 1) as last_user_full_name
					from post p, user u, forum_user fu 
					where p.user_id = u.id and p.user_id = ? and is_topic = 1 
					and fu.user_id = ? and fu.forum_id = p.forum_id 
					order by posted_time desc " . $limit_clause;
		$values = Array($user_id, $access_user_id);
		return db::select($query, $values);
	}

	public static function get_topics_by_user_count ($user_id, $access_user_id)
	{
		$query = "select count(*)
					from post p, user u, forum_user fu 
					where p.user_id = u.id and p.user_id = ? and is_topic = 1 
					and fu.user_id = ? and fu.forum_id = p.forum_id";
		$values = Array($user_id, $access_user_id);
		return db::select_single_value($query, $values);
	}

	public static function search_posts ($search, $access_user_id, $page = 1, $limit = POSTS_PER_PAGE){
		$limit_clause = db_general::get_limit_clause($page, $limit);
		$query = "select p.id as post_id, p.title as title, p.content as content, p.user_id as user_id, concat(u.first_name, ' ', u.last_name) as user_full_name, p.posted_time 				as posted_time, p.last_edited_time as last_edited_time, p.topic_id as topic_id, u.image as user_image
					from post p, user u, forum_user fu 
					where p.user_id = u.id and fu.user_id = ? and fu.forum_id = p.forum_id 
					and match(p.title, p.content) against(? in boolean mode)
					order by posted_time asc " . $limit_clause;
		$values = Array($access_user_id, $search);
		return db::select($query, $values);
	}

	public static function get_post_count_from_search ($search, $access_user_id)
	{
		$query = "select count(*) from post p, forum_user fu where fu.user_id = ? and fu.forum_id = p.forum_id and match(p.title, p.content) against(? in boolean mode)";
		$values = Array($access_user_id, $search);
		return db::select_single_value($query, $values);
	}

	public static function get_local_county_forum ($county_id)
	{
		$query = "select f.id 
			from forum f
				join constituency c on c.title = f.title
			where f.access_type = 'local_county' and c.id = ?";
		$values = Array($county_id);
		return db::select_single_value($query, $values);
	}

	public static function get_local_region_forum ($region_id)
	{
		$query = "select f.id 
			from forum f
				join constituency c on c.title = f.title
			where f.access_type = 'local_region' and c.id = ?";
		$values = Array($region_id);
		return db::select_single_value($query, $values);
	}

	public static function check_quote_validity ($post_id, $quote_text)
	{
		$query = "select * from post where id = ? and content like ?";
		$values = Array($post_id, '%' . $quote_text . '%');
		return !empty(db::select($query, $values));
	}

	public static function like_post ($user_id, $post_id, $flavor)
	{
		$query = "insert into user_like_post (user_id, post_id, flavor) values (?, ?, ?)";
		$values = Array($user_id, $post_id, $flavor);
		db::insert($query, $values);
		return self::get_post_like_info($user_id, $post_id);
	}	

	public static function unlike_post ($user_id, $post_id)
	{
		$query = "delete from user_like_post where user_id = ? and post_id = ?";
		$values = Array($user_id, $post_id);
		db::delete($query, $values);
		return self::get_post_like_info($user_id, $post_id);
	}

	public static function get_post_like_info($user_id, $post_id) {
		$critical_count = self::get_post_likes_flavor($post_id, 'critical');
		$neutral_count = self::get_post_likes_flavor($post_id, 'neutral');
		$supportive_count = self::get_post_likes_flavor($post_id, 'supportive');
		$total = $critical_count + $neutral_count + $supportive_count;
		$flavor = self::get_dominant_flavor($critical_count, $neutral_count, $supportive_count);
		$user_like = self::get_user_like_post($user_id, $post_id);
		return (object)array('flavor' => $flavor, 'count' => $total, 'user_like' => $user_like);
	}

	private static function get_user_like_post ($user_id, $post_id)
	{
		$query = "select count(*) from user_like_post where user_id = ? and post_id = ?";
		$values = Array($user_id, $post_id);
		return db::select_single_value($query, $values);
	}

	private static function get_dominant_flavor($critical_count, $neutral_count, $supportive_count){
		if ($critical_count > $supportive_count * 2)
			return 'critical';
		if ($supportive_count > $critical_count * 2)
			return 'supportive';
		return 'neutral';
	}

	private static function get_post_likes_flavor($post_id, $flavor) {
		$query = "select count(*) from user_like_post where post_id = ? and flavor = ?";
		$values = Array($post_id, $flavor);
		return db::select_single_value($query, $values);
	}
}