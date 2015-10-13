<?php

class db_helpers {

	public static function get_counties (){

		$query = "select kommun from kommuner order by kommun asc";
		$values = Array();

		return db::select($query, $values);

	}

	public static function get_regions (){

		$query = "select distinct lan from kommuner order by lan asc";
		$values = Array();

		return db::select($query, $values);

	}

	public static function get_region_from_county ($county){

		$query = "select lan from kommuner where kommun = ?";
		$values = Array($county);

		return db::select_single_value($query, $values);

	}

	public static function get_counties_for_region ($region){

		$query = "select kommun from kommuner where lan = ?";
		$values = Array($region);

		return db::select($query, $values);

	}

	public static function insert_error_message ($user_id, $message, $color = "green"){

		$query = "insert into error_messages (user_id, message, color, timestamp) values (?, ?, ?, ?)";
		$values = Array($user_id, $message, $color, time());

		return db::insert($query, $values);

	}

	public static function retrieve_error_message ($user_id){

		$query = "select * from error_messages where user_id = ?";
		$values = Array($user_id);

		$return = db::select($query, $values);

		$query = "delete from error_messages where user_id = ?";
		$values = Array($user_id);

		db::delete($query, $values);

		return $return;

	}

	public static function get_public_forum_ids (){

		$query = "select id from forum where access_type = 'public'";
		$values = Array();

		return db::select($query, $values);

	}

	public static function get_local_county_forum ($county){

		$query = "select id from forum where access_type = 'local_county' and title = ?";
		$values = Array($county);

		return db::select_single_value($query, $values);

	}

	public static function get_local_region_forum ($region){

		$query = "select id from forum where access_type = 'local_region' and title = ?";
		$values = Array($region);

		return db::select_single_value($query, $values);

	}

	public static function get_public_constituency_ids (){

		$query = "select id from constituency where consistuency_level = 1";
		$values = Array();

		return db::select($query, $values);

	}

	public static function get_local_county_constituency ($county){

		$query = "select id from constituency where consistuency_level = 3 and title = ?";
		$values = Array($county);

		return db::select_single_value($query, $values);

	}

	public static function get_local_region_constituency ($region){

		$query = "select id from constituency where consistuency_level = 2 and title = ?";
		$values = Array($region);

		return db::select_single_value($query, $values);

	}

	public static function add_constituency_access ($user_id, $constituency_id){

		$db_table = "constituency_user";
		$columns = Array("user_id", "constituency_id");
		$values = Array($constituency_id, $forum_id);

		$return = db::insert_ignore($db_table, $columns, $values);

		self::count_constituency_members($constituency_id);
		
		return $return;

	}

	public static function remove_constituency_access ($user_id, $constituency_id){

		$query = "delete from constituency_user where user_id = ? and constituency_id = ?";
		$values = Array($user_id, $forum_id);

		$return = db::delete($query, $values);

		self::count_constituency_members($constituency_id);
		
		return $return;

	}

	public static function count_constituency_members ($constituency_id){

		$query = "update constituency set number_of_voters = (select count(*) from constituency_user where constituency_id = ?) where constituency_id = ?";
		$values = Array($constituency_id, $constituency_id);

		return db::update($query, $values);

	}

	public static function check_user_constituency_access ($user_id, $constituency_id){

		$query = "select id from constituency_user where user_id = ? and constituency_id = ?";
		$values = Array($user_id, $constituency_id);

		$result = db::select_single_value($query, $values);

		if(empty($result)){
			return false;
		}
		else{
			return true;
		}

	}

	public static function get_constituency_forum_id ($constituency_id){

		$query = "select forum_id from constituency where id = ?";
		$values = Array($constituency_id);

		return db::select_single_value($query, $values);

	}

}

?>