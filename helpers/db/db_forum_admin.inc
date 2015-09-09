<?php

class db_forum_admin {
	
	public static function add_category ($title, $description){

		$query = "insert into categories (title, description) values (?, ?)";
		$values = Array($title, $description);

		return db::insert($query, $values);

	}

	public static function list_categories (){

		$query = "select * from categories";
		$values = Array();

		return db::select($query, $values);

	}

	public static function update_category ($title, $description, $cat_id){

		$query = "update categories set title = ?, description = ? where id = ?";
		$values = Array($title, $description, $cat_id);

		return db::update($query, $values);

	}

	public static function get_category_info ($cat_id){

		$query = "select * from categories where id = ?";
		$values = Array($cat_id);

		return db::select_single_row($query, $values);

	}

	public static function list_sub_forums ($cat_id){

		$query = "select f.id as forum_id, f.title as forum_name, f.description as description, p.posted_time as last_posted_time, p.id as last_posted_id, p.title as post_title, u.id 			as user_id, concat(u.first_name, ' ', u.last_name) as full_name, f.number_of_topics as number_of_topics, f.number_of_posts as number_of_posts
					from forums f, posts p, users u where p.id = f.last_posted_post and u.id = p.user_id and 
					f.category_id = ?";
		$values = Array($cat_id);

		return db::select($query, $values);

	}

	public static function add_forum ($cat_id, $title, $description, $access_type){

		$query = "insert into forums (category_id, title, description, access_type) values (?, ?, ?, ?)";
		$values = Array($cat_id, $title, $description, $access_type);

		$forum_id = db::insert($query, $values);

		if($access_type == "public"){
			$users = db_user::get_all_user_ids();
			$query = "insert into forums_users (forum_id, user_id) values (" . $forum_id . ", ?)";
			db::insert_all($query, $users);
		}

		return $forum_id;

	}

	public static function list_forums (){

		$query = "select * from forums";
		$values = Array();

		return db::select($query, $values);

	}

	public static function update_forum ($cat_id, $title, $description, $forum_id){

		$query = "update forums set category_id = ?, title = ?, description = ? where id = ?";
		$values = Array($cat_id, $title, $description, $forum_id);

		return db::update($query, $values);

	}

	public static function get_forum_info ($forum_id){

		$query = "select * from forums where id = ?";
		$values = Array($forum_id);

		return db::select_single_row($query, $values);

	}

	public static function add_forum_access ($user_id, $forum_id){

		$db_table = "forums_users";
		$columns = Array("user_id", "forum_id");
		$values = Array($user_id, $forum_id);

		return db::insert_ignore($db_table, $columns, $values);

	}

	public static function remove_forum_access ($user_id, $forum_id){

		$query = "delete from forums_users where user_id = ? and forum_id = ?";
		$values = Array($user_id, $forum_id);

		return db::delete($query, $values);

	}

	public static function get_all_forums_and_if_user_belongs ($user_id){

		$query = "select f.id as forum_id, f.title as forum_name, (if (exists (select * from forums_users fu where fu.forum_id = f.id and fu.user_id = ?), 1, 0)) as user_access from forums f";
		$values = Array($user_id);

		return db::select($query, $values);

	}

	public static function update_forums_for_user ($forum_ids, $user_id){

		$not_in_clause = implode(',', array_fill(0, count($forum_ids), '?'));

		$query = "delete from forums_users where forum_id not in (" . $not_in_clause . ") and user_id = ?";
		$values = $forum_ids;
		array_push($values, $user_id);

		$deleted = db::delete($query, $values);

		$query = "insert into forums_users (forum_id, user_id) select ? as forum_id, ? as user_id from dual where not exists (select * from forums_users where forum_id = ? and user_id = ?) limit 1";
		$inserted = db::insert_ignore_from_array($query, $forum_ids, $user_id);

		return $deleted + $inserted;

	}

	public static function drop_local_forums_for_user ($user_id){

		$query = "delete fu from forums_users fu 
					left join forums f on f.id = fu.forum_id
					where (f.access_type = 'local_region' or f.access_type = 'local_county') and fu.forum_id = f.id and fu.user_id = ?";
		$values = Array($user_id);

		return db::delete($query, $values);

	}

	public static function get_all_topics_for_forum ($forum_id){

		$query = "select id, title from posts where is_topic = 1 and forum_id = ?";
		$values = Array($forum_id);

		return db::select($query, $values);

	}

	public static function get_all_forums (){

		$query = "select id, title from forums";
		$values = Array();

		return db::select($query, $values);

	}

	public static function move_post ($post_id, $topic_id){

		$query = "update posts set topic_id = ? where id = ?";
		$values = Array($topic_id, $post_id);

		return db::update($query, $values);

	}

	public static function create_topic_from_post ($post_id, $title){

		$user_id = db_forum::get_user_id_from_post($post_id);
		$forum_id = db_forum::get_forum_id_from_post_id($post_id);

		$query = "update posts set is_topic = 1, topic_id = ?, title = ? where id = ?";
		$values = Array($post_id, general_helpers::clean($title), $post_id);

		$return = db::update($query, $values);

		db_forum::update_user_post_count($user_id);
		db_forum::update_forum_post_count($forum_id);

		return $return;

	}

	public static function move_topic ($topic_id, $forum_id){

		$old_forum_id = db_forum::get_forum_id_from_post_id($topic_id);

		$query = "update posts set forum_id = ? where topic_id = ?";
		$values = Array($forum_id, $topic_id);

		$return = db::update($query, $values);

		db_forum::update_forum_post_count($old_forum_id);
		db_forum::update_forum_post_count($forum_id);

		return $return;
	}

	public static function delete_post ($post_id){

		$user_id = db_forum::get_user_id_from_post($post_id);
		$forum_id = db_forum::get_forum_id_from_post_id($post_id);

		$query = "delete from posts where id = ?";
		$values = Array($post_id);

		$return = db::delete($query, $values);

		db_forum::update_user_post_count($user_id);
		db_forum::update_forum_post_count($forum_id);

		return $return;

	}

	public static function delete_topic ($topic_id){

		$forum_id = db_forum::get_forum_id_from_post_id($topic_id);
		$user_ids = self::get_user_ids_from_topic($topic_id);

		$query = "delete from posts where topic_id = ?";
		$values = Array($topic_id);

		$return = db::delete($query, $values);

		db_forum::update_forum_post_count($forum_id);
		foreach($user_ids as $user_id) {
			db_forum::update_user_post_count($user_id);
		}

		return $return;
	}

	public static function get_user_ids_from_topic ($topic_id){

		$query = "select distinct user_id from posts where topic_id = ?";
		$values = Array($topic_id);

		return db::select($query, $values);

	}

	public static function edit_title ($title, $topic_id){

		$query = "update posts set title = ? where topic_id = ?";
		$values = Array($title, $topic_id);

		return db::update($query, $values);

	}

	public static function edit_content ($content, $post_id){

		$query = "update posts set content = ? where id = ?";
		$values = Array($content, $post_id);

		return db::update($query, $values);

	}

}