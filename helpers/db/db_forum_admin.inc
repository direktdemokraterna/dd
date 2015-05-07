<?

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
var_dump($users);
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

}