<?php

class db_delegate 
{
	public static function is_user_delegate ($user_id)
	{
		$query = "select count(*) from delegate_user where user_id = ?";
		$values = Array($user_id);
		$result = db::select_single_value($query, $values);
		return $result == 1;
	}

	public static function get_delegate_settings ($user_id)
	{
		$query = "select d.id, d.title, d.description 
			from delegate d, delegate_user du 
			where d.id = du.delegate_id and du.user_id = ?";
		$values = Array($user_id);
		return db::select_single_row($query, $values);
	}

	public static function get_available_delegates ($constituency_id, $delegate_id)
	{
		$query = "select d.id as id, d.title as title 
			from delegate d
				join constituency_voter cv on cv.voter_id = d.id
			where cv.constituency_id = ? and d.id <> ?";
		$values = Array($constituency_id, $delegate_id);
		return db::select($query, $values);
	}

	public static function create_delegate ($user_id)
	{
		$user_full_name = db_user::get_user_full_name($user_id);
		$delegate_id = \db_general::create_voter('delegate');
		$delegate_query = "insert into delegate (id, title) values (?, ?)";
		$delegate_values = array($delegate_id, $user_full_name);
		db::insert($delegate_query, $delegate_values);
		$delegate_user_query = "insert into delegate_user (delegate_id, user_id) values (?, ?)";
		$delegate_user_values = Array($delegate_id, $user_id);
		db::insert($delegate_user_query, $delegate_user_values);
		return $delegate_id;
	}

	public static function delete_delegate ($delegate_id)
	{
		self::remove_delegations_for(null, null, $delegate_id);
		$query = "delete from delegate_user where delegate_id = ?";
		$values = array($delegate_id);
		db::delete($query, $values);
		$query = "delete from delegate where id = ?";
		db::delete($query, $values);
		return \db_general::delete_voter($delegate_id);
	}

	public static function get_user_id_from_delegate_id ($delegate_id)
	{
		$query = "select user_id from delegate_user where delegate_id = ?";
		$values = Array($delegate_id);
		return db::select_single_value($query, $values);
	}

	public static function change_acting_as_delegate ($user_id, $value)
	{
		$query = "update user set acting_as_delegate = ? where id = ?";
		$values = Array($value ? 1 : 0, $user_id);
		return db::update($query, $values);
	}

	public static function update_delegate_description($user_id, $description) {
		$delegate_id = self::get_delegate_id_from_user_id($user_id);
		$query = "update delegate set description = ? where id = ?";
		$values = Array($description, $delegate_id);
		return db::update($query, $values);		
	}

	public static function get_delegate_id_from_user_id ($user_id)
	{
		$query = "select du.delegate_id 
					from user u
						left join delegate_user du on du.user_id = u.id
					where u.id = ?";
		$values = Array($user_id);
		return db::select_single_value($query, $values);
	}

	public static function register_delegation ($user_code, $voter_id, $delegate_id, $constituency_id, $priority = 1)
	{
		$values = array();
		$from_where = self::get_delegations_from_to_query_fragment($values, $user_code, $voter_id, null, $constituency_id);
		$sel_query = "select * $from_where";
		$old_delegation = db::select_single_row($sel_query, $values);
		if($old_delegation){
			if ($old_delegation['delegate_id'] == $delegate_id) return true;
			$del_query = "delete $from_where";
			db::delete($del_query, $values);
			self::remove_delegations_for($user_code, $voter_id
				, $old_delegation['delegate_id'], $constituency_id);
		}
		if($delegate_id != "null"){
			$query = "insert into voter_delegate (delegate_id, user_code, voter_id, constituency_id, time_delegate_chosen) values (?, ?, ?, ?, ?)";
			$values = Array($delegate_id, $user_code, $voter_id, $constituency_id, time());
			db::insert($query, $values);
			self::execute_delegate_votes_for_new_delegate($user_code, $voter_id, $delegate_id, $constituency_id);
		}
		return true; 
	}

	public static function remove_delegations_for ($user_code, $voter_id = null, $delegate_id = null, $constituency_id = null)
	{
		$values = array();
		$from_where = self::get_delegations_from_to_query_fragment($values, $user_code, $voter_id, $delegate_id, $constituency_id);
		$sel_query = "select * $from_where";
		$delegations_to_remove = db::select($sel_query, $values);
		if($delegations_to_remove){
			$del_query = "delete $from_where";
			db::delete($del_query, $values);
			foreach ($delegations_to_remove as $row)
				self::remove_delegated_ballots($row['user_code'], $row['voter_id'], $row['delegate_id'], $row['constituency_id']);
		}
		return true; 
	}

	public static function remove_delegated_ballots($user_code, $voter_id, $delegate_id
		, $constituency_id) 
	{
		\db_vote::remove_ballots($user_code, $voter_id, $delegate_id, $constituency_id);
		\db_prop::remove_prop_ballots($user_code, $voter_id, $delegate_id, $constituency_id);
	}

	private static function get_delegations_from_to_query_fragment (&$values, $user_code, $voter_id = null, $delegate_id = null, $constituency_id = null)
	{
		$from_where = "from voter_delegate where ";
		$conditions = array();
		if ($user_code || $voter_id) {
			$conditions[] .= "(user_code = ? OR voter_id = ?)";
			$values[] = $user_code;
			$values[] = $voter_id;
		}
		if ($delegate_id) {
			$conditions[] .= "delegate_id = ?";
			$values[] = $delegate_id;
		}
		if ($constituency_id) {
			$conditions[] .= "constituency_id = ?";
			$values[] = $constituency_id;
		}
		$from_where .= implode(" and ", $conditions);
		return $from_where;
	}

	public static function get_constituencies_for_user_and_delegate_activity ($user_id, $delegate_id)
	{
		$query = "select c.id as constituency_id, c.title as constituency_title
					,if(cd.voter_id is null, 0, 1) as delegate_active 
					from constituency c
						join constituency_voter cu on c.id = cu.constituency_id
						left join constituency_voter cd on c.id = cd.constituency_id and cd.voter_id = ?
					where cu.voter_id = ?";
		$values = Array($delegate_id, $user_id);
		return db::select($query, $values);
	}

	public static function register_ballot ($vote_id, $delegate_id, $ballot)
	{
		$query = "delete from ballot where vote_id = ? and voter_id = ?";
		$values = Array($vote_id, $delegate_id);
		db::delete($query, $values);
		$constituency_id = db_constituency::get_vote_constituency_id($vote_id);
		$query = "insert into ballot (vote_id, constituency_id, ballot, voter_id, time_ballot_placed) values (?, ?, ?, ?, ?)";
		$values = Array($vote_id, $constituency_id, $ballot, $delegate_id, time());
		$ok = db::insert($query, $values);
		self::register_ballot_for_delegands($delegate_id, $constituency_id, $vote_id, $ballot, $delegate_id, 0);
		db_vote::count_ballots_for_vote($vote_id);
		return $ok;
	}

	public static function cancel_ballot ($vote_id, $delegate_id)
	{
		$delegand_ballots = self::get_delegand_ballots_for_vote($vote_id, $delegate_id);
		$query = "delete from ballot where vote_id = ? and (voter_id = ? or delegate_id = ?)";
		$values = Array($vote_id, $delegate_id, $delegate_id);
		$return = db::delete($query, $values);
		foreach($delegand_ballots as $row)
			if($row['user_code'])
				self::find_and_insert_delegate_vote_for_user($row['user_code'], null, $vote_id);
		db_vote::count_ballots_for_vote($vote_id);
		return $return;
	}

	public static function register_ballot_for_delegands ($delegate_id, $constituency_id, $vote_id, $ballot, $actual_delegate_voter_id, $delegation_level)
	{
		$delegands = self::get_delegands_for_delegate($delegate_id, $constituency_id);
		foreach($delegands as $delegand){			
			$old_ballot = db_vote::get_ballot_from_delegate_or_user($vote_id, $delegand['user_code'], $delegand['voter_id']);

			if(empty($old_ballot) || (isset($old_ballot['delegate_id']) && ($old_ballot['delegation_level'] > $delegation_level || $old_ballot['delegate_id'] == $actual_delegate_voter_id))){

				db_vote::insert_ballot($vote_id, $ballot, $delegand['user_code'], $delegand['voter_id'], $actual_delegate_voter_id, $delegation_level, $delegand['priority']);

				if($delegand['voter_id'] && $delegand['voter_id'] != $delegate_id) // Delegand is another delegate.
					self::register_ballot_for_delegands($delegand['voter_id'], $constituency_id, $vote_id, $ballot, $actual_delegate_voter_id, $delegation_level+1);
			}
		}
	}

	public static function register_prop_ballot ($prop_id, $delegate_id, $support)
	{
		$query = "delete from proposition_support where proposition_id = ? and voter_id = ?";
		$values = Array($prop_id, $delegate_id);
		db::delete($query, $values);
		$constituency_id = db_constituency::get_prop_constituency_id($prop_id);
		$query = "insert into proposition_support (proposition_id, constituency_id, voter_id, support, time_ballot_placed) values (?, ?, ?, ?, ?)";
		$values = Array($prop_id, $constituency_id, $delegate_id, $support, time());
		$ok = db::insert($query, $values);
		self::register_prop_ballot_for_delegands($delegate_id, $constituency_id, $prop_id, $support, $delegate_id, 0);
		db_prop::count_prop_support($prop_id);
		return $ok;
	}

	public static function cancel_prop_ballot ($prop_id, $delegate_id)
	{
		$delegand_ballots = self::get_delegand_ballots_for_prop($prop_id, $delegate_id);
		$query = "delete from proposition_support where proposition_id = ? and (voter_id = ? or delegate_id = ?)";
		$values = Array($prop_id, $delegate_id, $delegate_id);
		$return = db::delete($query, $values);
		foreach($delegand_ballots as $row)
			if($row['user_code'])
				$new_ballot = self::find_and_insert_delegate_prop_vote_for_user($row['user_code'], null, $prop_id);
		db_prop::count_prop_support($prop_id);
		return $return;
	}

	public static function register_prop_ballot_for_delegands ($delegate_id, $constituency_id, $prop_id, $support, $actual_delegate_voter_id, $delegation_level)
	{
		$delegands = self::get_delegands_for_delegate($delegate_id, $constituency_id);
		foreach($delegands as $delegand)
			self::update_votes_for_delegand($delegand, $constituency_id, $prop_id, $support, $actual_delegate_voter_id, $delegation_level);
	}

	private static function update_votes_for_delegand($delegand, $constituency_id, $prop_id, $support, $actual_delegate_voter_id, $delegation_level) 
	{
		$ballot = db_prop::get_prop_ballot_from_delegate_or_user($prop_id, $delegand['user_code'], $delegand['voter_id']);
		if(empty($ballot))
			self::insert_vote_for_delegand($prop_id, $constituency_id, $support, $delegand, $actual_delegate_voter_id, $delegation_level);
		elseif(self::this_delegate_is_same_or_higher_priority_than_current($ballot, $delegation_level, $actual_delegate_voter_id))
			self::replace_vote_for_delegand($support, $actual_delegate_voter_id, $delegation_level, $delegand, $prop_id);
		else return;	
		self::propagate_vote_to_delegands_delegands($delegand, $constituency_id, $prop_id, $support, $actual_delegate_voter_id, $delegation_level);
	}

	private static function this_delegate_is_same_or_higher_priority_than_current($ballot, $delegation_level, $actual_delegate_voter_id) 
	{
		return isset($ballot['delegate_id']) && ($ballot['delegation_level'] > $delegation_level 
			|| $ballot['delegate_id'] == $actual_delegate_voter_id);
	}

	private static function insert_vote_for_delegand($prop_id, $constituency_id, $support, $delegand, $actual_delegate_voter_id, $delegation_level) 
	{
		$query = "insert into proposition_support (proposition_id, constituency_id, support, user_code, voter_id, delegate_id, delegation_level, delegate_priority, time_ballot_placed) values (?, ?, ?, ?, ?, ?, ?, ?, ?)";
		$values = Array($prop_id, $constituency_id, $support, $delegand['user_code'], $delegand['voter_id'], $actual_delegate_voter_id, $delegation_level, $delegand['priority'], time());
		db::insert($query, $values);
	}

	private static function replace_vote_for_delegand($support, $actual_delegate_voter_id, $delegation_level, $delegand, $prop_id) 
	{
		$query = "update proposition_support set support = ?, delegate_id = ?, delegation_level = ?, delegate_priority = ?, time_ballot_placed = ? where proposition_id = ? and (user_code = ? or voter_id = ?)";
		$values = Array($support, $actual_delegate_voter_id, $delegation_level, $delegand['priority'], time(), $prop_id, $delegand['user_code'], $delegand['voter_id']);
		db::update($query, $values);
	}

	private static function propagate_vote_to_delegands_delegands($delegand, $constituency_id, $prop_id, $support, $actual_delegate_voter_id, $delegation_level) {
		if($delegand['voter_id']){ // Delegand is another delegate.
			self::register_prop_ballot_for_delegands($delegand['voter_id'], $constituency_id, $prop_id, $support, $actual_delegate_voter_id, $delegation_level+1);
		}
	}

	public static function get_delegands_for_delegate ($delegate_id, $constituency_id)
	{
		$query = "select user_code, voter_id, priority from voter_delegate where delegate_id = ? and constituency_id = ?";
		$values = Array($delegate_id, $constituency_id);
		return db::select($query, $values);
	}

	public static function get_delegates_for_user_constituencies ($voter_id, $page = 1, $sort = 0, $where_filter, $filter_values)
	{
		$where_filter[] = "cd.voter_id = d.id";
		$limit_clause = db_general::get_limit_clause($page, LIST_ITEMS_PER_PAGE);
		$where_clause = self::create_delegates_for_user_constituencies_where_clause($where_filter);
		$order_by_clause = "order by " . self::get_order_by($sort);
		$visible_columns = implode(", ", self::$delegates_visible_columns);
		$query = "select d.id, $visible_columns 
				from delegate d 
				" . $where_clause . "
				" . $order_by_clause . "
				" . $limit_clause;
		return db::select($query, $filter_values);
	}

	private static function get_order_by ($sort = 0)
	{
		return db_general::get_order_by(self::$delegates_visible_columns, 1, $sort);
	}

	private static $delegates_visible_columns =
		array("d.title", "d.description"
			, "(select count(*) from voter_delegate vd where vd.delegate_id = d.id) as delegand_count");

	public static function get_delegates_for_user_constituencies_count ($where_filter, $filter_values)
	{
		$where_clause = self::create_delegates_for_user_constituencies_where_clause($where_filter);
		$query = "select count(*) from delegate d 
				" . $where_clause;
		return db::select_single_value($query, $filter_values);
	}

	private static function create_delegates_for_user_constituencies_where_clause ($where_filter)
	{
		$where_filter[] = "cd.voter_id = d.id";
		return "where exists 
				(
					select * from constituency_voter cd
						join constituency_voter cv on cd.constituency_id = cv.constituency_id
					where " . implode(" and ", $where_filter) . "
				)";
	}

	public static function get_delegate_info ($delegate_id)
	{
		$query = "select d.title, d.description, du.user_id 
			from delegate d
				join delegate_user du on du.delegate_id = d.id
			where d.id = ?";
		$values = Array($delegate_id);
		return db::select_single_row($query, $values);
	}

	public static function list_delegate_ballots ($delegate_id, $page = 1, $limit = LIST_ITEMS_PER_PAGE_SHORT, $where_filter = "1=1"){
		$limit_clause = db_general::get_limit_clause($page, $limit);
		$query = "select v.id as vote_id, v.title as title, v.type as type, b.ballot as ballot, b.delegate_id as delegate_id, (select title from delegate d where d.id = b.delegate_id) as delegate_name 
				from ballot b, vote v 
				where b.vote_id = v.id and b.voter_id = ? and " . $where_filter . " 
				order by v.timestamp_created desc " . $limit_clause;
		$values = Array($delegate_id);
		return db::select($query, $values);
	}

	public static function get_delegate_ballot_for_vote ($vote_id, $delegate_id)
	{
		$query = "select * from ballot where vote_id = ? and voter_id = ?";
		$values = Array($vote_id, $delegate_id);
		return db::select_single_row($query, $values);
	}

	public static function get_delegand_ballots_for_vote ($vote_id, $delegate_id)
	{
		$query = "select * from ballot where vote_id = ? and delegate_id = ?";
		$values = Array($vote_id, $delegate_id);
		return db::select($query, $values);
	}

	public static function get_delegand_ballots_for_prop ($prop_id, $delegate_id)
	{
		$query = "select * from proposition_support where proposition_id = ? and delegate_id = ?";
		$values = Array($prop_id, $delegate_id);
		return db::select($query, $values);
	}

	public static function get_delegate_prop_ballot_for_prop ($prop_id, $delegate_id)
	{
		$query = "select * from proposition_support where proposition_id = ? and voter_id = ?";
		$values = Array($prop_id, $delegate_id);
		return db::select_single_row($query, $values);
	}

	public static function list_delegate_ballots_count ($delegate_id, $where_filter = "1=1")
	{
		$query = "select count(*)
				from ballot b, vote v 
				where b.vote_id = v.id and b.voter_id = ? and b.delegate_id is null and " . $where_filter;
		$values = Array($delegate_id);
		return db::select_single_value($query, $values);
	}

	public static function get_complete_list_of_user_delegations ()
	{
		$query = "select vd.user_code as user_code, vd.constituency_id as constituency_id, vd.delegate_id as delegate_id, 
					(select d.title from delegate d where vd.delegate_id = d.id) as delegate_name 
					from voter_delegate vd 
					where user_code is not null";
		$values = Array($vote_id);
		return db::select($query, $values);
	}

	public static function get_ballot_for_vote ($vote_id, $delegate_id)
	{
		$query = "select b.voter_id as voter_id, b.ballot as ballot, b.delegate_id as delegate_id, (select d.title from delegate d where b.delegate_id = d.id) as delegate_name from ballot b where b.vote_id = ? and b.voter_id = ?";
		$values = Array($vote_id, $delegate_id);
		return db::select_single_row($query, $values);
	}

	public static function get_ballot_for_prop ($prop_id, $delegate_id)
	{
		$query = "select ps.voter_id as voter_id, ps.support, ps.delegate_id, (select d.title from delegate d where ps.delegate_id = d.id) as delegate_name 
		from proposition_support ps where ps.proposition_id = ? and ps.voter_id = ?";
		$values = Array($prop_id, $delegate_id);
		return db::select_single_row($query, $values);
	}

	public static function get_delegations_for_multiple_constituencies ($constituencies
		, $for_delegate_id = 0)
	{
		if (!$constituencies) return array();
		$in_clause = implode(',', array_fill(0, count($constituencies), '?'));
		$query = "select vd.user_code, vd.voter_id, vd.constituency_id, vd.delegate_id, d.title as delegate_name 
			from voter_delegate vd, delegate d 
			where vd.delegate_id = d.id 
			and vd.voter_id " . ($for_delegate_id ? " = " . $for_delegate_id : "is null") 
			. " and vd.constituency_id in (" . $in_clause . ")";
		$values = Array();
		foreach($constituencies as $row)
			$values[] = $row['id'];
		return db::select($query, $values);
	}

	public static function get_delegate_ballots_for_vote ($vote_id)
	{
		$query = "select b.voter_id as voter_id, b.ballot as ballot, b.delegate_id as delegate_id, 
					(select d.title from delegate d where b.delegate_id = d.id) as delegate_name 
					from ballot b 
					where b.voter_id is not null and b.vote_id = ?";
		$values = Array($vote_id);
		return db::select($query, $values);
	}

	public static function execute_delegate_votes_for_new_delegate ($user_code, $delegand_id, $delegate_id, $constituency_id)
	{
		$relevant_votes = db_delegate::get_votes_with_no_direct_ballots($constituency_id, $user_code, $delegand_id);
		foreach ($relevant_votes as $row) {
			$delegate_ballot = self::get_ballot_for_vote($row['id'], $delegate_id);
			self::register_ballot_for_delegands($delegate_id, $constituency_id, $row['id'], $delegate_ballot['ballot'], $delegate_id, 1);
		}
	}

	public static function get_votes_with_no_direct_ballots ($constituency_id, $user_code, $delegand_id)
	{
		$query = "select v.id as id from vote v where v.constituency_id = ? and not exists (select * from ballot b where (b.user_code = ? or b.voter_id = ?) and b.vote_id = v.id and b.delegate_id is null)";
		$values = Array($constituency_id, $user_code, $delegand_id);
		return db::select($query, $values);
	}

	public static function get_delegate_delegates ($delegand_id)
	{
		$query = "select d.id as delegate_id, d.title as delegate_title, c.id as constituency_id, c.title as constituency_title, vd.time_delegate_chosen as time_delegate_chosen
			from voter_delegate vd, delegate d, constituency c
			where vd.delegate_id = d.id and vd.constituency_id = c.id and vd.voter_id = ?";
		$values = Array($delegand_id);
		return db::select($query, $values);
	}

	public static function get_delegates_delegate_for_constituency ($delegand_id, $constituency_id)
	{
		$query = "select d.id as delegate_id, d.title as delegate_title, vd.time_delegate_chosen as time_delegate_chosen
			from voter_delegate vd, delegate d
			where vd.delegate_id = d.id and vd.voter_id = ? and vd.constituency_id = ?";
		$values = Array($delegand_id, $constituency_id);
		return db::select_single_row($query, $values);
	}

	public static function number_of_delegate_ballots_for_vote ($vote_id)
	{
		$query = "select count(*) from ballot where voter_id is not null and delegate_id is null and vote_id = ?";
		$values = Array($vote_id);
		return db::select_single_value($query, $values);
	}

	public static function find_and_insert_delegate_vote_for_user ($user_code, $voter_id, $vote_id)
	{
		$constituency_id = db_constituency::get_vote_constituency_id($vote_id);
		$processed_delegates = Array(); // To spot and break out ot circle delegations.
		$delegation_level = 0;
		$delegate_id = $user_code ? $user_code : $voter_id;
		while(!in_array($delegate_id, $processed_delegates)){
			$query = "select delegate_id from voter_delegate where (user_code = ? or voter_id = ?) and constituency_id = ?";
			$values = Array($user_code, $voter_id, $constituency_id);
			$delegate_id = db::select_single_value($query, $values);
			if(!$delegate_id)
				return false;
			$delegate_vote = self::get_delegate_ballot_for_vote($vote_id, $delegate_id);
			if(!empty($delegate_vote)){
				db_vote::insert_ballot($vote_id, $delegate_vote['ballot'], $user_code, $voter_id, $delegate_id, $delegation_level, 1);
				return true;
			}
			$processed_delegates[] = $delegate_id;
			$delegation_level++;
		}
		return false;
	}

	public static function find_and_insert_delegate_prop_vote_for_user ($user_code, $voter_id, $prop_id)
	{
		$constituency_id = db_constituency::get_prop_constituency_id($prop_id);
		$processed_delegates = Array(); // To spot and break out ot circle delegations.
		$delegation_level = 0;
		$delegate_id = $user_code ? $user_code : $voter_id;
		while(!in_array($delegate_id, $processed_delegates)){
			$query = "select delegate_id from voter_delegate where (user_code = ? or voter_id = ?) and constituency_id = ?";
			$values = Array($user_code, $voter_id, $constituency_id);
			$delegate_id = db::select_single_value($query, $values);
			if(!$delegate_id)
				return false;
			$delegate_vote = self::get_delegate_prop_ballot_for_prop($prop_id, $delegate_id);
			if(!empty($delegate_vote)){
				//todo: insert_prop_ballot doesn't exist yet
				db_vote::insert_prop_ballot($prop_id, $delegate_vote['support'], $user_code, $voter_id, $delegate_id, $delegation_level, 1);
				return true;
			}
			$processed_delegates[] = $delegate_id;
			$delegation_level++;
		}
		return false;
	}
}