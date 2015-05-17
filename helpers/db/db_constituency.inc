<?

class db_constituency {

	public static function get_all_constituencies (){

		$query = "select c.id as id, c.title as name from constituencies c order by access_type, title";
		$values = Array();

		return db::select($query, $values);

	}

	public static function get_constituencies_for_user ($user_id){

		$query = "select c.id as id, c.title as name
					from constituencies c, constituencies_users cu 
					where c.id = cu.constituency_id and cu.user_id = ?";
		$values = Array($user_id);

		return db::select($query, $values);

	}

	public static function get_prop_constituency_id ($prop_id){

		$query = "select constituency_id from propositions where id = ?";
		$values = Array($prop_id);

		return db::select_single_value($query, $values);

	}

	public static function get_vote_constituency_id ($vote_id){

		$query = "select constituency_id from votes where id = ?";
		$values = Array($vote_id);

		return db::select_single_value($query, $values);

	}

	public static function get_public_constituency_ids (){

		$query = "select id from constituencies where access_type = 'public'";
		$values = Array();

		return db::select($query, $values);

	}

	public static function get_local_county_constituency ($county){

		$query = "select id from constituencies where access_type = 'local_county' and title = ?";
		$values = Array($county);

		return db::select_single_value($query, $values);

	}

	public static function get_local_region_constituency ($region){

		$query = "select id from constituencies where access_type = 'local_region' and title = ?";
		$values = Array($region);

		return db::select_single_value($query, $values);

	}

	public static function add_constituency_access ($user_id, $constituency_id){

		$db_table = "constituencies_users";
		$columns = Array("user_id", "constituency_id");
		$values = Array($constituency_id, $forum_id);

		$return = db::insert_ignore($db_table, $columns, $values);

		self::count_constituency_members($constituency_id);
		
		return $return;

	}

	public static function remove_constituency_access ($user_id, $constituency_id){

		$query = "delete from constituencies_users where user_id = ? and constituency_id = ?";
		$values = Array($user_id, $forum_id);

		$return = db::delete($query, $values);

		self::count_constituency_members($constituency_id);
		
		return $return;

	}

	public static function count_constituency_members ($constituency_id){

		$query = "update constituencies set number_of_voters = (select count(*) from constituencies_users where constituency_id = ?) where constituency_id = ?";
		$values = Array($constituency_id, $constituency_id);

		return db::update($query, $values);

	}

	public static function check_user_constituency_access ($user_id, $constituency_id){

		$query = "select id from constituencies_users where user_id = ? and constituency_id = ?";
		$values = Array($user_id, $constituency_id);

		$result = db::select_single_value($query, $values);

		if(empty($result)){
			return false;
		}
		else{
			return true;
		}

	}

	public static function check_delegate_constituency_access ($delegate_id, $constituency_id){

		$query = "select id from constituencies_delegates where delegate_id = ? and constituency_id = ?";
		$values = Array($delegate_id, $constituency_id);

		$result = db::select_single_value($query, $values);

		if(empty($result)){
			return false;
		}
		else{
			return true;
		}

	}

	public static function get_constituency_forum_id ($constituency_id){

		$query = "select forum_id from constituencies where id = ?";
		$values = Array($constituency_id);

		return db::select_single_value($query, $values);

	}

	public static function add_constituency_to_delegate ($user_id, $delegate_id, $constituency_id){

		if(self::check_user_constituency_access($user_id, $constituency_id)){

			$db_table = "constituencies_delegates";
			$columns = Array("constituency_id", "delegate_id");
			$values = Array($constituency_id, $delegate_id);

			return db::insert_ignore($db_table, $columns, $values);

		}
		else{
			return false;
		}

	}

	public static function remove_constituency_from_delegate ($delegate_id, $constituency_id){

		$query = "delete from constituencies_delegates where delegate_id = ? and constituency_id = ?";
		$values = Array($delagate_id, $constituency_id);

		$reply = db::delete($query, $values);

		if($reply){

			$query = "delete from voters_delegates where delegate_id = ? and constituency_id = ?";
			$values = Array($delagate_id, $constituency_id);

			db::delete($query, $values);

		}

	}

	public static function check_that_constituency_exists ($constituency_id){

		$query = "select count(*) from constituencies where id = ?";
		$values = Array($constituency_id);

		$reply = db::select_single_value($query, $values);

		if($reply==0) return false;
		else return true;

	}


}