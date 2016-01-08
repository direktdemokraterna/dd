<?php

class db_constituency 
{
	public static function get_constituencies_for_voter ($voter_id)
	{
		$query = "select c.id as id, c.title as name
					from constituency c 
						join constituency_voter cv on c.id = cv.constituency_id
					where cv.voter_id = ? 
					order by c.constituency_level asc, c.id asc";
		$values = Array($voter_id);
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

	public static function get_local_region_constituency_for_user ($user_id)
	{
		return self::get_local_constituency_on_level_for_user(2, $user_id);
	}

	public static function get_local_county_constituency_for_user ($user_id)
	{
		return self::get_local_constituency_on_level_for_user(3, $user_id);
	}

	public static function add_constituency_access ($voter_id, $constituency_id)
	{
		$query = "insert into constituency_voter (voter_id, constituency_id) values (?, ?)";
		$values = array($voter_id, $constituency_id);
		db::insert($query, $values);
		self::update_constituency_member_count($constituency_id);
		return 1; // number of updates made
	}

	public static function remove_constituency_access($voter_id, $constituency_id = null) {
		$values = array();
		$from_where = self::get_constituency_access_from_where_fragment($values, $voter_id, $constituency_id);
		$sel_query = "select constituency_id " . $from_where;
		$affected_constituencies = db::select($sel_query, $values);
		if ($affected_constituencies) {
			$del_query = "delete " . $from_where;
			db::delete($del_query, $values);
			foreach ($affected_constituencies as $row)
				self::update_constituency_member_count($row['constituency_id']);
		}
		return count($affected_constituencies);
	}

	private static function get_constituency_access_from_where_fragment(&$values, $voter_id, $constituency_id = null) {
		$from_where = "from constituency_voter
		where voter_id = ?";
		$values[] = $voter_id;
		if ($constituency_id) {
			$from_where .= " and constituency_id = ?";
			$values[] = $constituency_id;
		}
		return $from_where;
	}

	public static function update_constituency_member_count ($constituency_id)
	{
		$query = "update constituency set number_of_voters = (select count(*) 
					from constituency_voter cv join user u on cv.voter_id = u.id 
					where constituency_id = ?) 
				where id = ?";
		$values = Array($constituency_id, $constituency_id);
		return db::update($query, $values);
	}

	public static function check_voter_constituency_access ($voter_id, $constituency_id)
	{
		$query = "select voter_id from constituency_voter where voter_id = ? and constituency_id = ?";
		$values = Array($voter_id, $constituency_id);
		$result = db::select_single_value($query, $values);
		return !empty($result);
	}

	public static function get_constituency_forum_id ($constituency_id){
		$query = "select forum_id from constituency where id = ?";
		$values = Array($constituency_id);
		return db::select_single_value($query, $values);
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

	public static function get_all_constituencies_and_if_voter_belongs ($voter_id)
	{
		$query = "select c.id as constituency_id, c.title as constituency_name
					, if(cv.voter_id is null, 0, 1) as voter_access 
				from constituency c
					left join constituency_voter cv on cv.constituency_id = c.id and cv.voter_id = ?";
		$values = Array($voter_id);
		return db::select($query, $values);
	}

	public static function get_constituency_ids_for_voter ($voter_id)
	{
		$query = "select c.id as id
					from constituency c 
						join constituency_voter cv on c.id = cv.constituency_id
					where cv.voter_id = ? order by c.id asc";
		$values = Array($voter_id);
		return db::select_sequential_array($query, $values);
	}

	public static function get_all_constituencies ($page = 1, $limit = LIST_ITEMS_PER_PAGE, 
		$order_by = "constituency_level asc, title asc", $where_filter = "1=1"){
		$limit_clause = db_general::get_limit_clause($page, $limit);
		$query = "select c.id as id, c.title as name from constituency c where " 
		. $where_filter . " order by " . $order_by . " " . $limit_clause;
		$values = Array();
		return db::select($query, $values);
	}

	public static function get_all_constituencies_count ($where_filter = "1=1"){
		$query = "select count(*) from constituency where " . $where_filter;
		$values = Array();
		return db::select_single_value($query, $values);
	}

	public static function get_counties ()
	{
		$query = "select id, title from constituency
					where constituency_level = 3
					 order by title asc";
		$values = Array();
		return db::select($query, $values);
	}

	public static function get_counties_with_regions ()
	{
		$query = "select c.id county_id, c.title county_name, r.id region_id from constituency c
					join constituency r on r.id = c.parent_id
					where c.constituency_level = 3
					 order by c.title asc";
		$values = Array();
		return db::select($query, $values);
	}

	public static function get_regions ()
	{
		$query = "select id, title from constituency
					where constituency_level = 2
					 order by title asc";
		$values = Array();
		return db::select($query, $values);
	}

	public static function get_region_id_from_county_id ($county_id)
	{
		$query = "select cr.id from constituency cr
					join constituency cc on cc.parent_id = cr.id
					where cc.id = ? and cc.constituency_level = 3";
		$values = Array($county_id);
		return db::select_single_value($query, $values);
	}		

	public static function get_region_from_county ($county_id)
	{
		$query = "select parent_id from constituency where id = ?";
		$values = Array($county_id);
		return db::select_single_value($query, $values);
	}

	public static function get_counties_for_region ($region_id)
	{
		$query = "select id, title from constituency cc	where parent_id = ?";
		$values = Array($region_id);
		return db::select($query, $values);
	}

	private static function get_local_constituency_on_level_for_user ($level, $user_id)
	{
		$query = "select c.id as id 
					from constituency c 
						join constituency_voter cv on c.id = cv.constituency_id
					where c.constituency_level = ? and cv.voter_id = ?";
		$values = Array($level, $user_id);
		return db::select_single_value($query, $values);
	}
}