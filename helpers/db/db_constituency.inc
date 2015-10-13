<?php

class db_constituency {

	public static function get_constituencies_for_user ($user_id)
	{
		$query = "select c.id as id, c.title as name
					from constituency c, constituency_user cu 
					where c.id = cu.constituency_id and cu.user_id = ? 
					order by c.constituency_level asc, c.id asc";
		$values = Array($user_id);
		return db::select($query, $values);
	}

	public static function get_constituency_ids_for_user ($user_id)
	{
		$query = "select c.id as id
					from constituency c, constituency_user cu 
					where c.id = cu.constituency_id and cu.user_id = ? order by c.id asc";
		$values = Array($user_id);
		return db::select_sequential_array($query, $values);
	}

	public static function get_constituencies_for_delegate ($delegate_id)
	{
		$query = "select c.id as id, c.title as name
					from constituency c, constituency_delegate cd 
					where c.id = cd.constituency_id and cd.delegate_id = ? order by c.id asc";
		$values = Array($delegate_id);
		return db::select($query, $values);
	}

	public static function get_prop_constituency_id ($prop_id)
	{
		$query = "select constituency_id from proposition where id = ?";
		$values = Array($prop_id);
		return db::select_single_value($query, $values);
	}

	public static function get_vote_constituency_id ($vote_id)
	{
		$query = "select constituency_id from vote where id = ?";
		$values = Array($vote_id);
		return db::select_single_value($query, $values);
	}

	public static function get_public_constituency_ids ()
	{
		$query = "select id from constituency where constituency_level = 1";
		$values = Array();
		return db::select($query, $values);
	}

	public static function get_local_region_constituency ($region)
	{
		$query = "select id from constituency where constituency_level = 2 and title = ?";
		$values = Array($region);
		return db::select_single_value($query, $values);
	}

	public static function get_local_county_constituency ($county)
	{
		$query = "select id from constituency where constituency_level = 3 and title = ?";
		$values = Array($county);
		return db::select_single_value($query, $values);
	}

	public static function get_local_county_constituency_for_user ($user_id)
	{
		$query = "select c.id as id from constituency c, constituency_user cu where cu.constituency_id = c.id and c.constituency_level = 3 and cu.user_id = ?";
		$values = Array($user_id);
		return db::select_single_value($query, $values);
	}

	public static function get_local_region_constituency_for_user ($user_id)
	{
		$query = "select c.id as id from constituency c, constituency_user cu where cu.constituency_id = c.id and c.constituency_level = 2 and cu.user_id = ?";
		$values = Array($user_id);
		return db::select_single_value($query, $values);
	}

	public static function add_constituency_access ($user_id, $constituency_id)
	{
		$db_table = "constituency_user";
		$columns = Array("user_id", "constituency_id");
		$values = Array($user_id, $constituency_id);
		$return = db::insert_ignore($db_table, $columns, $values);
		self::update_constituency_member_count($constituency_id);
		return $return;
	}

	public static function remove_constituency_access ($user_id, $constituency_id)
	{
		$user_code = self::get_user_code($user_id);
		self::remove_user_ballots_for_constituency($user_code, $constituency_id);
		self::remove_user_delegations_for_constituency($user_code, $constituency_id);
		$chg_count = self::remove_user_from_constituency($user_id, $constituency_id);
		self::remove_delegate_from_constituency($user_id, $constituency_id);
		self::update_constituency_member_count($constituency_id);
		return $chg_count;
	}

	// !! SECURITY BREACH ALERT! Vote server has access to both user_id and user_code, voter secrecy is being violated !!
	private static function get_user_code ($user_id)
	{
		$post_vars = Array("user_id" => $user_id);
		return crypt_helpers::curl_to_anon_server("give_active_user_code_for_user_id.php", $post_vars);
	}

	private static function remove_user_ballots_for_constituency ($user_code, $constituency_id)
	{
		$query = "delete from ballot where user_code = ? and constituency_id = ?";
		$values = Array($user_code, $constituency_id);
		db::delete($query, $values);
		db_vote::count_ballots_for_active_votes_for_constituency($constituency_id);
	}

	private static function remove_user_delegations_for_constituency ($user_code, $constituency_id)
	{
		$query = "delete from voter_delegate where user_code = ? and constituency_id = ?";
		$values = Array($user_code, $constituency_id);
		return db::delete($query, $values);
	}

	private static function remove_user_from_constituency ($user_id, $constituency_id)
	{
		$query = "delete from constituency_user where user_id = ? and constituency_id = ?";
		$values = Array($user_id, $constituency_id);
		return db::delete($query, $values);
	}

	private static function remove_delegate_from_constituency ($user_id, $constituency_id)
	{
		if(db_delegate::is_user_delegate($user_id)){
			$delegate_id = db_delegate::get_delegate_id_from_user_id($user_id);
			self::remove_constituency_from_delegate($delegate_id, $constituency_id);
		}
	}

	public static function update_constituency_member_count ($constituency_id)
	{
		$query = "update constituency set number_of_voters = (select count(*) 
			from constituency_user where constituency_id = ?) where id = ?";
		$values = Array($constituency_id, $constituency_id);
		return db::update($query, $values);
	}

	public static function check_user_constituency_access ($user_id, $constituency_id)
	{
		$query = "select id from constituency_user where user_id = ? and constituency_id = ?";
		$values = Array($user_id, $constituency_id);
		$result = db::select_single_value($query, $values);
		return !empty($result);
	}

	public static function check_delegate_constituency_access ($delegate_id, $constituency_id)
	{
		$query = "select id from constituency_delegate where delegate_id = ? and constituency_id = ?";
		$values = Array($delegate_id, $constituency_id);
		$result = db::select_single_value($query, $values);
		return !empty($result);
	}

	public static function get_constituency_forum_id ($constituency_id){
		$query = "select forum_id from constituency where id = ?";
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
		return false;
	}

	public static function remove_constituency_from_delegate ($delegate_id, $constituency_id)
	{
		$query = "delete from constituency_delegate where delegate_id = ? and constituency_id = ?";
		$values = Array($delegate_id, $constituency_id);
		$reply = db::delete($query, $values);
		if($reply){
			$query = "delete from voter_delegate where delegate_id = ? and constituency_id = ?";
			$values = Array($delagate_id, $constituency_id);
			db::delete($query, $values);
		}
		return $reply;
	}

	public static function check_that_constituency_exists ($constituency_id)
	{
		$query = "select count(*) from constituency where id = ?";
		$values = Array($constituency_id);
		$reply = db::select_single_value($query, $values);
		return $reply > 0;
	}

	public static function get_constituency_name ($constituency_id)
	{
		$query = "select title as name from constituency where id = ?";
		$values = Array($constituency_id);
		return db::select_single_value($query, $values);
	}

	public static function get_all_constituencies_and_if_user_belongs ($user_id)
	{
		$query = "select c.id as constituency_id, c.title as constituency_name, (if (exists (select * from constituency_user cu where cu.constituency_id = c.id and cu.user_id = ?), 1, 0)) as user_access from constituency c";
		$values = Array($user_id);
		return db::select($query, $values);
	}

	public static function update_constituencies_for_user ($constituency_ids, $user_id)
	{
		$chg_cnt = 0;
		$old_constituencies = self::get_constituency_ids_for_user($user_id);
		$added_constituencies = array_diff($constituency_ids, $old_constituencies);
		$removed_constituencies = array_diff($old_constituencies, $constituency_ids);
		foreach($added_constituencies as $added_constituency){
			$chg_cnt += self::add_constituency_access($user_id, $added_constituency);
		}
		foreach($removed_constituencies as $removed_constituency){
			$chg_cnt += self::remove_constituency_access($user_id, $removed_constituency);
		}
		return $chg_cnt;
	}

	// NOTE: This db function does not utilise full parametrised input due to bug in current MySQL that doesn't allow parametrised input in limit clause. Variables are instead sanitised by casting as int. When this bug is resolved, this function can be corrected. 
	public static function get_all_constituencies ($page = 1, $limit = LIST_ITEMS_PER_PAGE, 
		$order_by = "constituency_level asc, title asc", $where_filter = "1=1"){
		$page = (int)($page-1) * $limit;
		$limit = (int)$limit;
		$query = "select c.id as id, c.title as name from constituency c where " 
		. $where_filter . " order by " . $order_by . " limit " . $page . ", " . $limit;
		$values = Array();
		return db::select($query, $values);
	}

	public static function get_all_constituencies_count ($where_filter = "1=1"){
		$query = "select count(*) from constituency where " . $where_filter;
		$values = Array();
		return db::select_single_value($query, $values);
	}
}