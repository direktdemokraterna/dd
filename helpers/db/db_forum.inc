<?php

class db_forum {

	public static function get_last_posts (){

		$query = "select p.id as post_id, p.title as post_title, p.posted_time as posted_time, u.id as user_id, concat(u.first_name, ' ', u.last_name) as user_full_name, 
					f.id as forum_id, f.title as forum_title, c.id as cat_id, c.title as cat_title, (select id from posts t where t.id = p.topic_id) as topic_id 
					from posts p, users u, categories c, forums f 
					where p.user_id = u.id and p.forum_id = f.id and f.category_id = c.id order by p.posted_time desc limit 10";
		$values = Array();

		return db::select($query, $values);

	}

	public static function list_forums (){

		$query = "select c.id as cat_id, c.title as cat_name, f.id as forum_id, f.title as forum_name, f.description as description, f.last_posted_time as last_posted_time, f.					last_posted_post as last_posted_id, f.number_of_topics as number_of_topics, f.number_of_posts as number_of_posts
					from forums f, categories c, forums_users fu 
					where c.id = f.category_id and f.id = fu.forum_id and fu.user_id = ?";
		$values = Array($_SESSION['id']);

		return db::select($query, $values);

	}

	public static function get_post_info ($post_id){

		$query = "select p.id as post_id, p.title as title, u.id as user_id, concat(u.first_name, ' ', u.last_name) as full_name, p.forum_id as forum_id, p.topic_id as topic_id, p.			posted_time as posted_time
					from posts p, users u where u.id = p.user_id and p.id = ?";
		$values = Array($post_id);

		return db::select_single_row($query, $values);

	}

	public static function get_full_post_info ($post_id, $user_id){

		$query = "select p.id as post_id, p.title as title, p.content as content, p.user_id as user_id, concat(u.first_name, ' ', u.last_name) as user_full_name, p.posted_time 		as posted_time, p.last_edited_time as last_edited_time, p.forum_id as forum_id, u.image as user_image
					from posts p, users u 
					where u.id = p.user_id and p.id = ? and exists (select * from forums_users where forum_id = p.forum_id and user_id = ?)";
		$values = Array($post_id, $user_id);

		return db::select_single_row($query, $values);

	}

	public static function get_public_forum_ids (){

		$query = "select id from forums where access_type = 'public'";
		$values = Array();

		return db::select($query, $values);

	}

	public static function get_forum_info ($forum_id){

		$query = "select f.* from forums f, forums_users fu where fu.user_id = " . $_SESSION['id'] . " and fu.forum_id = f.id and f.id = ?";
		$values = Array($forum_id);

		return db::select_single_row($query, $values);

	}

	public static function list_topics ($forum_id, $access_user_id, $page = 1, $limit = 50){
// NOTE: This db function does not utilise full parametrised input due to bug in current MySQL that doesn't allow parametrised input in limit clause. Variables are instead sanitised by casting as int. When this bug is resolved, this function can be corrected. 

		$page = (int)($page-1) * $limit;
		$limit = (int)$limit;

		$query = "select p.id as topic_id, p.title as topic_title, u.id as topic_user_id, concat(u.first_name, ' ', u.last_name) as topic_user_full_name, 
					(select count(*) from posts p2 where p2.topic_id = p.id) as number_of_posts, 
					(select count(distinct user_id) from posts p3 where p3.topic_id = p.id) as number_of_participants, 
					(select p4.posted_time from posts p4 where p4.topic_id = p.id order by p4.posted_time desc limit 1) as last_posted_time, 
					(select u2.id from posts p5, users u2 where p5.user_id = u2.id and p5.topic_id = p.id order by p5.posted_time desc limit 1) as last_user_id, 
					(select concat(u3.first_name, ' ', u3.last_name) from posts p6, users u3 where p6.user_id = u3.id and p6.topic_id = p.id order by p6.posted_time desc limit 1) as last_user_full_name
					from posts p, users u, forums_users fu 
					where p.user_id = u.id and p.is_topic = 1 and p.forum_id = ? 
					and fu.user_id = ? and fu.forum_id = p.forum_id 
					order by last_posted_time desc limit " . $page . ", " . $limit;
		$values = Array($forum_id, $access_user_id);

		return db::select($query, $values);

	}

	public static function check_access ($user_id, $forum_id){

		$query = "select * from forums_users where user_id = ? and forum_id = ?";
		$values = Array($user_id, $forum_id);

		$check = db::select_single_value($query, $values);

		if($check) return true;
		else return false;

	}

	public static function new_topic ($user_id, $forum_id, $title){

		$query = "insert into posts (user_id, forum_id, title, is_topic, posted_time) values (?, ?, ?, ?, ?)";
		$values = Array($user_id, $forum_id, htmlspecialchars($title, ENT_COMPAT,'ISO-8859-1', true), 1, time());

		$insert_id = db::insert($query, $values);

		$query = "update posts set topic_id = id where id = ?";
		$values = Array($insert_id);

		db::update($query, $values);

		self::update_forum_post_count($forum_id);

		self::update_user_post_count($user_id);

		return $insert_id;

	}

	public static function get_posts ($topic_id, $access_user_id, $page = 1, $limit = POSTS_PER_PAGE){
// NOTE: This db function does not utilise full parametrised input due to bug in current MySQL that doesn't allow parametrised input in limit clause. Variables are instead sanitised by casting as int. When this bug is resolved, this function can be corrected. 

		$page = (int)($page-1) * $limit;
		$limit = (int)$limit;

		$query = "select p.id as post_id, p.title as title, p.content as content, p.user_id as user_id, concat(u.first_name, ' ', u.last_name) as user_full_name, p.posted_time 		as posted_time, p.last_edited_time as last_edited_time, u.image as user_image
					from posts p, users u, forums_users fu
					where p.user_id = u.id and p.topic_id = ? 
					and fu.user_id = ? and fu.forum_id = p.forum_id 
					order by posted_time asc limit " . $page . ", " . $limit;
		$values = Array($topic_id, $access_user_id);

		return db::select($query, $values);

	}

	public static function update_forum_post_count ($forum_id){

		$query = "update forums set last_posted_time = (select posted_time from posts where forum_id = ? order by posted_time desc limit 1), last_posted_post = (select id from posts where forum_id = ? order by posted_time desc limit 1), number_of_topics = (select count(*) from posts where is_topic = 1 and forum_id = ?), number_of_posts = (select count(*) from posts where forum_id = ?) where id = ?";
		$values = Array($forum_id, $forum_id, $forum_id, $forum_id, $forum_id);

		return db::update($query, $values);

	}

	public static function get_title ($post_id){

		$query = "select title from posts where id = ?";
		$values = Array($post_id);

		return db::select_single_value($query, $values);

	}

	public static function get_user_id_from_post ($post_id){

		$query = "select user_id from posts where id = ?";
		$values = Array($post_id);

		return db::select_single_value($query, $values);

	}

	public static function get_forum_from_post ($post_id){

		$query = "select f.id as forum_id, f.title as forum_title from posts p, forums f where p.forum_id = f.id and p.id = ?";
		$values = Array($post_id);

		return db::select_single_row($query, $values);

	}

	public static function get_forum_id_from_post_id ($post_id){

		$query = "select forum_id from posts where id = ?";
		$values = Array($post_id);

		return db::select_single_value($query, $values);

	}

	public static function get_post_count ($post_id){

		$query = "select count(*) from posts where topic_id = ?";
		$values = Array($post_id);

		return db::select_single_value($query, $values);

	}

	public static function get_post_count_by_user ($user_id, $access_user_id){

		$query = "select count(*) from posts p, forums_users fu where p.user_id = ? and fu.user_id = ? and fu.forum_id = p.forum_id";
		$values = Array($user_id, $access_user_id);

		return db::select_single_value($query, $values);

	}

	public static function get_forum_from_post_id ($topic_id){

		$query = "select forum_id from posts where id = ?";
		$values = Array($topic_id);

		return db::select_single_value($query, $values);

	}

	public static function new_post ($user_id, $topic_id){

		$topic_info = self::get_post_info($topic_id);

		$query = "insert into posts (user_id, topic_id, forum_id, title, is_topic, posted_time) values (?, ?, ?, ?, ?, ?)";
		$values = Array($user_id, $topic_id, $topic_info['forum_id'], $topic_info['title'], 0, time());

		$insert_id = db::insert($query, $values);

		self::update_forum_post_count($topic_info['forum_id']);

		self::update_user_post_count($user_id);

		return $insert_id;

	}

	public static function new_report ($post_id, $user_id, $argument){

		$query = "insert into post_reports (post_id, reporter_id, time_report_filed, argument) values (?, ?, ?, ?)";
		$values = Array($post_id, $user_id, time(), $argument);

		return db::insert($query, $values);

	}

	public static function get_topic ($post_id){

		$query = "select topic_id from posts where id = ?";
		$values = Array($post_id);

		return db::select_single_value($query, $values);

	}

	public static function get_number_of_posts ($topic_id){

		$query = "select count(*) from posts where topic_id = ?";
		$values = Array($topic_id);

		return db::select_single_value($query, $values);

	}

	public static function delete_post ($post_id){

		$post_info = self::get_post_info($post_id);

		$query = "delete from posts where id = ?";
		$values = Array($post_id);

		$return = db::delete($query, $values);

		self::update_forum_post_count($post_info['forum_id']);

		self::update_user_post_count($post_info['user_id']);

		return $return;

	}

	public static function count_posts_before_post_id ($topic_id, $post_id){

		$query = "select count(*) from posts where topic_id = ? and id < ?";
		$values = Array($topic_id, $post_id);

		return db::select_single_value($query, $values);

	}

	public static function check_quote_validity ($post_id, $quote_text){

		$query = "select * from posts where id = ? and content like ?";
		$values = Array($post_id, '%' . $quote_text . '%');

		$return = db::select($query, $values);

		if(empty($return)){
			return false;
		}
		else{
			return true;
		}

	}

	public static function add_content_to_post ($post_id, $content, $edit = "new"){

		if($edit == "new"){
			$query = "update posts set content = ? where id = ?";
			$values = Array($content, $post_id);
		}
		elseif($edit == "edit"){
			$query = "update posts set content = ?, last_edited_time = ? where id = ?";
			$values = Array($content, time(), $post_id);
		}
		elseif($edit == "add"){
			$query = "update posts set content = concat(content, ?), last_edited_time = ? where id = ?";
			$values = Array($content, time(), $post_id);
		}

		return db::update($query, $values);

	}

	public static function update_user_post_count ($user_id){

		$query = "update users set number_of_posts = (select count(*) from posts where user_id = ?), number_of_topics = (select count(*) from posts where is_topic = 1 and user_id = ?)  where id = ?";
		$values = Array($user_id, $user_id, $user_id);

		return db::update($query, $values);

	}

	public static function get_posts_by_user ($user_id, $access_user_id, $page = 1, $limit = POSTS_PER_PAGE){
// NOTE: This db function does not utilise full parametrised input due to bug in current MySQL that doesn't allow parametrised input in limit clause. Variables are instead sanitised by casting as int. When this bug is resolved, this function can be corrected. 

		$page = (int)($page-1) * $limit;
		$limit = (int)$limit;

		$query = "select p.id as post_id, p.title as title, p.content as content, p.user_id as user_id, concat(u.first_name, ' ', u.last_name) as user_full_name, p.posted_time 				as posted_time, p.last_edited_time as last_edited_time, p.topic_id as topic_id, u.image as user_image
					from posts p, users u, forums_users fu 
					where p.user_id = u.id and p.user_id = ? 
					and fu.user_id = ? and fu.forum_id = p.forum_id 
					order by posted_time asc limit " . $page . ", " . $limit;
		$values = Array($user_id, $access_user_id);

		return db::select($query, $values);

	}

	public static function get_topics_by_user ($user_id, $access_user_id, $page = 1, $limit = POSTS_PER_PAGE){
// NOTE: This db function does not utilise full parametrised input due to bug in current MySQL that doesn't allow parametrised input in limit clause. Variables are instead sanitised by casting as int. When this bug is resolved, this function can be corrected. 

		$page = (int)($page-1) * $limit;
		$limit = (int)$limit;

		$query = "select p.id as topic_id, p.title as topic_title, u.id as topic_user_id, concat(u.first_name, ' ', u.last_name) as topic_user_full_name, 
					(select count(*) from posts p2 where p2.topic_id = p.id) as number_of_posts, 
					(select count(distinct user_id) from posts p3 where p3.topic_id = p.id) as number_of_participants, 
					(select p4.posted_time from posts p4 where p4.topic_id = p.id order by p4.posted_time desc limit 1) as last_posted_time, 
					(select u2.id from posts p5, users u2 where p5.user_id = u2.id and p5.topic_id = p.id order by p5.posted_time desc limit 1) as last_user_id, 
					(select concat(u3.first_name, ' ', u3.last_name) from posts p6, users u3 where p6.user_id = u3.id and p6.topic_id = p.id order by p6.posted_time desc limit 1) as last_user_full_name
					from posts p, users u, forums_users fu 
					where p.user_id = u.id and p.user_id = ? and is_topic = 1 
					and fu.user_id = ? and fu.forum_id = p.forum_id 
					order by posted_time desc limit " . $page . ", " . $limit;
		$values = Array($user_id, $access_user_id);

		return db::select($query, $values);

	}

	public static function search_posts ($search, $access_user_id, $page = 1, $limit = POSTS_PER_PAGE){
// NOTE: This db function does not utilise full parametrised input due to bug in current MySQL that doesn't allow parametrised input in limit clause. Variables are instead sanitised by casting as int. When this bug is resolved, this function can be corrected. 

		$page = (int)($page-1) * $limit;
		$limit = (int)$limit;

		$query = "select p.id as post_id, p.title as title, p.content as content, p.user_id as user_id, concat(u.first_name, ' ', u.last_name) as user_full_name, p.posted_time 				as posted_time, p.last_edited_time as last_edited_time, p.topic_id as topic_id, u.image as user_image
					from posts p, users u, forums_users fu 
					where p.user_id = u.id and fu.user_id = ? and fu.forum_id = p.forum_id 
					and match(p.title, p.content) against(? in boolean mode)
					order by posted_time asc limit " . $page . ", " . $limit;
		$values = Array($access_user_id, $search);

		return db::select($query, $values);

	}

	public static function get_post_count_from_search ($search, $access_user_id){

		$query = "select count(*) from posts p, forums_users fu where fu.user_id = ? and fu.forum_id = p.forum_id and match(p.title, p.content) against(? in boolean mode)";
		$values = Array($access_user_id, $search);

		return db::select_single_value($query, $values);

	}

}