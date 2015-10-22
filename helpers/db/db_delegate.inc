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
		$query = "select d.id as delegate_id, d.title as title, d.description as description 
			from delegate d, delegate_user du 
			where d.id = du.delegate_id and du.user_id = ?";
		$values = Array($user_id);
		return db::select_single_row($query, $values);
	}

	public static function get_constituencies_for_delegate ($delegate_id)
	{
		$query = "select c.id as id, c.title as title 
			from constituency c, constituency_delegate cd 
			where c.id = cd.constituency_id and cd.delegate_id = ?";
		$values = Array($user_id);
		return db::select($query, $values);
	}

	public static function get_available_delegates_for_constituency ($constituency_id)
	{
		$query = "select d.id as id, d.title as title 
			from delegate d, constituency_delegate cd 
			where d.id = cd.delegate_id 
			and cd.constituency_id = ?";
		$values = Array($constituency_id);
		return db::select($query, $values);
	}

	public static function create_delegate ($user_id)
	{
		$user_full_name = db_user::get_user_full_name($user_id);
		$db_table = "delegate";
		$columns = Array("title");
		$values = Array($user_full_name);
		$delegate_id = db::insert_ignore($db_table, $columns, $values);
		if($delegate_id){
			$query = "insert into delegate_user (delegate_id, user_id) values (?, ?)";
			$values = Array($delegate_id, $user_id);
			db::insert($query, $values);
			return $delegate_id;
		}
		return false;
	}

	public static function get_delegate_id_from_user_id ($user_id)
	{
		$query = "select delegate_id from delegate_user where user_id = ?";
		$values = Array($user_id);
		return db::select_single_value($query, $values);
	}

	public static function get_user_id_from_delegate_id ($delegate_id)
	{
		$query = "select user_id from delegate_user where delegate_id = ?";
		$values = Array($delegate_id);
		return db::select_single_value($query, $values);
	}

	public static function start_acting_as_delegate ($user_id)
	{
		$query = "update user set acting_as_delegate = 1 where id = ?";
		$values = Array($user_id);
		return db::update($query, $values);
	}

	public static function stop_acting_as_delegate ($user_id)
	{
		$query = "update user set acting_as_delegate = 0 where id = ?";
		$values = Array($user_id);
		return db::update($query, $values);
	}

	public static function get_constituencies_for_user_and_delegate_activity ($user_id, $delegate_id)
	{
		$query = "select c.id as constituency_id, c.title as constituency_title, 
					(select id from constituency_delegate cd where cd.constituency_id = c.id and cd.delegate_id = ?) as delegate_active 
					from constituency c, constituency_user cu 
					where c.id = cu.constituency_id and cu.user_id = ?";
		$values = Array($delegate_id, $user_id);
		return db::select($query, $values);
	}

	public static function update_delegate_constituencies ($constituency_ids, $user_id)
	{
		$delegate_id = self::get_delegate_id_from_user_id($user_id);

		// Checking constituency access for user behind delegate
		foreach($constituency_ids as $key => $value)
			if(!db_constituency::check_user_constituency_access($user_id, $value))
				unset($constituency_ids[$key]);
		$not_in_clause = implode(',', array_fill(0, count($constituency_ids), '?'));
		$query = "delete from constituency_delegate where constituency_id not in (" . $not_in_clause . ") and delegate_id = ?";
		$values = $constituency_ids;
		array_push($values, $delegate_id);
		$deleted = db::delete($query, $values);
		$query = "insert into constituency_delegate (constituency_id, delegate_id) select ? as constituency_id, ? as delegate_id from dual where not exists (select * from constituency_delegate where constituency_id = ? and delegate_id = ?) limit 1";
		$inserted = db::insert_ignore_from_array($query, $constituency_ids, $delegate_id);
		return $deleted + $inserted;
	}

	public static function remove_all_delegate_constituencies ($user_id)
	{
		$delegate_id = self::get_delegate_id_from_user_id($user_id);
		$query = "delete from constituency_delegate where delegate_id = ?";
		$values = Array($delegate_id);
		return db::update($query, $values);
	}

	public static function register_ballot ($vote_id, $delegate_id, $ballot)
	{
		$query = "delete from ballot where vote_id = ? and voter_is_delegate_id = ?";
		$values = Array($vote_id, $delegate_id);
		db::delete($query, $values);
		$constituency_id = db_constituency::get_vote_constituency_id($vote_id);
		$query = "insert into ballot (vote_id, constituency_id, ballot, voter_is_delegate_id, time_ballot_placed) values (?, ?, ?, ?, ?)";
		$values = Array($vote_id, $constituency_id, $ballot, $delegate_id, time());
		$ok = db::insert($query, $values);
		self::register_ballot_for_delegands($delegate_id, $constituency_id, $vote_id, $ballot, $delegate_id, 0);
		db_vote::count_ballots_for_vote($vote_id);
		return $ok;
	}

	public static function cancel_ballot ($vote_id, $delegate_id)
	{
		$delegand_ballots = self::get_delegand_ballots_for_vote($vote_id, $delegate_id);
		$query = "delete from ballot where vote_id = ? and (voter_is_delegate_id = ? or delegate_id = ?)";
		$values = Array($vote_id, $delegate_id, $delegate_id);
		$return = db::delete($query, $values);
		foreach($delegand_ballots as $row)
			if($row['user_code'])
				$new_ballot = self::find_and_insert_delegate_vote_for_user($row['user_code'], null, $vote_id);
		db_vote::count_ballots_for_vote($vote_id);
		return $return;
	}

	public static function register_ballot_for_delegands ($delegate_id, $constituency_id, $vote_id, $ballot, $actual_delegate_voter_id, $delegation_level)
	{
		$delegands = self::get_delegands_for_delegate($delegate_id, $constituency_id);
		foreach($delegands as $delegand){			
			$old_ballot = db_vote::get_ballot_from_delegate_or_user($vote_id, $delegand['user_code'], $delegand['voter_is_delegate_id']);

			if(empty($old_ballot) || (isset($old_ballot['delegate_id']) && ($old_ballot['delegation_level'] > $delegation_level || $old_ballot['delegate_id'] == $actual_delegate_voter_id))){

				db_vote::insert_ballot($vote_id, $ballot, $delegand['user_code'], $delegand['voter_is_delegate_id'], $actual_delegate_voter_id, $delegation_level, $delegand['priority']);

				if($delegand['voter_is_delegate_id']) // Delegand is another delegate.
					self::register_ballot_for_delegands($delegand['voter_is_delegate_id'], $constituency_id, $vote_id, $ballot, $actual_delegate_voter_id, $delegation_level+1);
			}
		}
	}

	public static function register_prop_ballot ($prop_id, $delegate_id, $support_type)
	{
		$query = "delete from proposition_support where proposition_id = ? and voter_is_delegate_id = ?";
		$values = Array($prop_id, $delegate_id);
		db::delete($query, $values);
		$constituency_id = db_constituency::get_prop_constituency_id($prop_id);
		$query = "insert into proposition_support (proposition_id, constituency_id, voter_is_delegate_id, support_type, time_ballot_placed) values (?, ?, ?, ?, ?)";
		$values = Array($prop_id, $constituency_id, $delegate_id, $support_type, time());
		$ok = db::insert($query, $values);
		self::register_prop_ballot_for_delegands($delegate_id, $constituency_id, $prop_id, $support_type, $delegate_id, 0);
		db_prop::count_prop_support($prop_id);
		return $ok;
	}

	public static function cancel_prop_ballot ($prop_id, $delegate_id)
	{
		$delegand_ballots = self::get_delegand_ballots_for_prop($prop_id, $delegate_id);
		$query = "delete from proposition_support where proposition_id = ? and (voter_is_delegate_id = ? or delegate_id = ?)";
		$values = Array($prop_id, $delegate_id, $delegate_id);
		$return = db::delete($query, $values);
		foreach($delegand_ballots as $row)
			if($row['user_code'])
				$new_ballot = self::find_and_insert_delegate_prop_vote_for_user($row['user_code'], null, $prop_id);
		db_prop::count_prop_support($prop_id);
		return $return;
	}

	public static function register_prop_ballot_for_delegands ($delegate_id, $constituency_id, $prop_id, $support_type, $actual_delegate_voter_id, $delegation_level)
	{
		$delegands = self::get_delegands_for_delegate($delegate_id, $constituency_id);
		foreach($delegands as $delegand){
			$ballot = db_prop::get_prop_ballot_from_delegate_or_user($prop_id, $delegand['user_code'], $delegand['voter_is_delegate_id']);
			if(empty($ballot)){
				$query = "insert into proposition_support (proposition_id, constituency_id, support_type, user_code, voter_is_delegate_id, delegate_id, delegation_level, delegate_priority, time_ballot_placed) values (?, ?, ?, ?, ?, ?, ?, ?, ?)";
				$values = Array($prop_id, $constituency_id, $support_type, $delegand['user_code'], $delegand['voter_is_delegate_id'], $actual_delegate_voter_id, $delegation_level, $delegand['priority'], time());
				db::insert($query, $values);
				if($delegand['voter_is_delegate_id']) // Delegand is another delegate.
					self::register_prop_ballot_for_delegands($delegand['voter_is_delegate_id'], $constituency_id, $prop_id, $support_type, $actual_delegate_voter_id, $delegation_level+1);
			}
			elseif(isset($ballot['delegate_id']) && ($ballot['delegation_level'] > $delegation_level || $ballot['delegate_id'] == $actual_delegate_voter_id)){
				$query = "update proposition_support set support_type = ?, delegate_id = ?, delegation_level = ?, delegate_priority = ?, time_ballot_placed = ? where proposition_id = ? and (user_code = ? or voter_is_delegate_id = ?)";
				$values = Array($support_type, $actual_delegate_voter_id, $delegation_level, $delegand['priority'], time(), $prop_id, $delegand['user_code'], $delegand['voter_is_delegate_id']);
				db::update($query, $values);
				if($delegand['voter_is_delegate_id']){ // Delegand is another delegate.
					self::register_prop_ballot_for_delegands($delegand['voter_is_delegate_id'], $constituency_id, $prop_id, $support_type, $actual_delegate_voter_id, $delegation_level+1);
				}
			}
		}
	}

	public static function get_delegands_for_delegate ($delegate_id, $constituency_id)
	{
		$query = "select user_code, voter_is_delegate_id, priority from voter_delegate where delegate_id = ? and constituency_id = ?";
		$values = Array($delegate_id, $constituency_id);
		return db::select($query, $values);
	}

	public static function list_delegates_for_user_constituencies ($user_id, $page = 1, $limit = LIST_ITEMS_PER_PAGE, $order_by = "timestamp_created desc", $where_filter = "1=1"){
		$limit_clause = db_general::get_limit_clause($page, $limit);
		$query = "select d.id as id, d.title as title from delegate d where exists (select * from constituency_delegate cd, constituency_user cu where cd.delegate_id = d.id and cd.constituency_id = cu.constituency_id and cu.user_id = ? and " . $where_filter . ") order by " . $order_by . " " . $limit_clause;
		$values = Array($user_id);
		return db::select($query, $values);
	}

	public static function list_delegates_for_user_constituencies_count ($user_id, $where_filter = "1=1")
	{
		$query = "select count(*) from delegate d where exists (select * from constituency_delegate cd, constituency_user cu where cd.delegate_id = d.id and cd.constituency_id = cu.constituency_id and cu.user_id = ? and " . $where_filter . ")";
		$values = Array($user_id);
		return db::select_single_value($query, $values);
	}

	public static function get_delegate_info ($delegate_id)
	{
		$query = "select title, description from delegate where id = ?";
		$values = Array($delegate_id);
		return db::select_single_row($query, $values);
	}

	public static function list_delegate_ballots ($delegate_id, $page = 1, $limit = LIST_ITEMS_PER_PAGE_SHORT, $where_filter = "1=1"){
		$limit_clause = db_general::get_limit_clause($page, $limit);
		$query = "select v.id as vote_id, v.title as title, v.type as type, b.ballot as ballot, b.delegate_id as delegate_id, (select title from delegate d where d.id = b.delegate_id) as delegate_name 
				from ballot b, vote v 
				where b.vote_id = v.id and b.voter_is_delegate_id = ? and " . $where_filter . " 
				order by v.timestamp_created desc " . $limit_clause;
		$values = Array($delegate_id);
		return db::select($query, $values);
	}

	public static function get_delegate_ballot_for_vote ($vote_id, $delegate_id)
	{
		$query = "select * from ballot where vote_id = ? and voter_is_delegate_id = ?";
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
		$query = "select * from proposition_support where proposition_id = ? and voter_is_delegate_id = ?";
		$values = Array($prop_id, $delegate_id);
		return db::select_single_row($query, $values);
	}

	public static function list_delegate_ballots_count ($delegate_id, $where_filter = "1=1")
	{
		$query = "select count(*)
				from ballot b, vote v 
				where b.vote_id = v.id and b.voter_is_delegate_id = ? and b.delegate_id is null and " . $where_filter;
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
		$query = "select b.voter_is_delegate_id as voter_id, b.ballot as ballot, b.delegate_id as delegate_id, (select d.title from delegate d where b.delegate_id = d.id) as delegate_name from ballot b where b.vote_id = ? and b.voter_is_delegate_id = ?";
		$values = Array($vote_id, $delegate_id);
		return db::select_single_row_associative($query, $values);
	}

	public static function get_ballot_for_prop ($prop_id, $delegate_id)
	{
		$query = "select ps.voter_is_delegate_id as voter_id, ps.support_type as support_type, ps.delegate_id as delegate_id, (select d.title from delegate d where ps.delegate_id = d.id) as delegate_name from proposition_support ps where ps.proposition_id = ? and ps.voter_is_delegate_id = ?";
		$values = Array($prop_id, $delegate_id);
		return db::select_single_row($query, $values);
	}

	public static function get_delegations_for_multiple_constituencies ($constituencies)
	{
		$in_clause = implode(',', array_fill(0, count($constituencies), '?'));
		$query = "select vd.user_code as user_code, vd.constituency_id as constituency_id, vd.delegate_id as delegate_id, d.title as delegate_name 
					from voter_delegate vd, delegate d 
					where vd.delegate_id = d.id and vd.voter_is_delegate_id is null and vd.constituency_id in (" . $in_clause . ")";
		$values = Array();
		foreach($constituencies as $row)
			$values[] = $row['id'];
		return db::select($query, $values);
	}

	public static function register_delegation_ballot ($user_code, $delegand_id, $delegate_id, $constituency_id, $priority = 1)
	{
		$query = "select * from voter_delegate where (user_code = ? or voter_is_delegate_id = ?) and constituency_id = ?";
		$values = Array($user_code, $delegand_id, $constituency_id);
		$result = db::select_single_row($query, $values);
		if(!empty($result)){
			$query = "delete from voter_delegate where (user_code = ? or voter_is_delegate_id = ?) and constituency_id = ?";	
			$values = Array($user_code, $delegand_id, $constituency_id);
			db::delete($query, $values);
			if($delegate_id == "null"){
				self::remove_delegate_votes($user_code, $delegand_id, $result['delegate_id'], $constituency_id);
			}
		}
		if($delegate_id != "null"){
			$query = "insert into voter_delegate (delegate_id, user_code, voter_is_delegate_id, constituency_id, time_delegate_chosen) values (?, ?, ?, ?, ?)";
			$values = Array($delegate_id, $user_code, $delegand_id, $constituency_id, time());
			db::insert($query, $values);
			self::execute_delegate_votes_for_new_delegate($user_code, $delegand_id, $delegate_id, $constituency_id);
		}
		return true; 
	}

	public static function remove_delegate_votes ($user_code, $delegand_id, $delegate_id, $constituency_id)
	{
		$query = "delete from ballot where (user_code = ? or voter_is_delegate_id = ?) and delegate_id = ? and constituency_id = ?";
		$values = Array($user_code, $delegand_id, $delegate_id, $constituency_id);
		return db::delete($query, $values);
	}

	public static function get_delegate_ballots_for_vote ($vote_id)
	{
		$query = "select b.voter_is_delegate_id as voter_is_delegate_id, b.ballot as ballot, b.delegate_id as delegate_id, 
					(select d.title from delegate d where b.delegate_id = d.id) as delegate_name 
					from ballot b 
					where b.voter_is_delegate_id is not null and b.vote_id = ?";
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
		$query = "select v.id as id from vote v where v.constituency_id = ? and not exists (select * from ballot b where (b.user_code = ? or b.voter_is_delegate_id = ?) and b.vote_id = v.id and b.delegate_id is null)";
		$values = Array($constituency_id, $user_code, $delegand_id);
		return db::select($query, $values);
	}

	public static function get_delegate_delegates ($delegand_id)
	{
		$query = "select d.id as delegate_id, d.title as delegate_title, c.id as constituency_id, c.title as constituency_title, vd.time_delegate_chosen as time_delegate_chosen
			from voter_delegate vd, delegate d, constituency c
			where vd.delegate_id = d.id and vd.constituency_id = c.id and vd.voter_is_delegate_id = ?";
		$values = Array($delegand_id);
		return db::select($query, $values);
	}

	public static function get_delegates_delegate_for_constituency ($delegand_id, $constituency_id)
	{
		$query = "select d.id as delegate_id, d.title as delegate_title, vd.time_delegate_chosen as time_delegate_chosen
			from voter_delegate vd, delegate d
			where vd.delegate_id = d.id and vd.voter_is_delegate_id = ? and vd.constituency_id = ?";
		$values = Array($delegand_id, $constituency_id);
		return db::select_single_row($query, $values);
	}

	public static function number_of_delegate_ballots_for_vote ($vote_id)
	{
		$query = "select count(*) from ballot where voter_is_delegate_id is not null and delegate_id is null and vote_id = ?";
		$values = Array($vote_id);
		return db::select_single_value($query, $values);
	}

	public static function find_and_insert_delegate_vote_for_user ($user_code, $voter_is_delegate_id, $vote_id)
	{
		$constituency_id = db_constituency::get_vote_constituency_id($vote_id);
		$processed_delegates = Array(); // To spot and break out ot circle delegations.
		$delegation_level = 0;
		$delegate_id = $user_code ? $user_code : $voter_is_delegate_id;
		while(!in_array($delegate_id, $processed_delegates)){
			$query = "select delegate_id from voter_delegate where (user_code = ? or voter_is_delegate_id = ?) and constituency_id = ?";
			$values = Array($user_code, $voter_is_delegate_id, $constituency_id);
			$delegate_id = db::select_single_value($query, $values);
			if(!$delegate_id)
				return false;
			$delegate_vote = self::get_delegate_ballot_for_vote($vote_id, $delegate_id);
			if(!empty($delegate_vote)){
				db_vote::insert_ballot($vote_id, $delegate_vote['ballot'], $user_code, $voter_is_delegate_id, $delegate_id, $delegation_level, 1);
				return true;
			}
			$processed_delegates[] = $delegate_id;
			$delegation_level++;
		}
		return false;
	}

	public static function find_and_insert_delegate_prop_vote_for_user ($user_code, $voter_is_delegate_id, $prop_id)
	{
		$constituency_id = db_constituency::get_prop_constituency_id($prop_id);
		$processed_delegates = Array(); // To spot and break out ot circle delegations.
		$delegation_level = 0;
		$delegate_id = $user_code ? $user_code : $voter_is_delegate_id;
		while(!in_array($delegate_id, $processed_delegates)){
			$query = "select delegate_id from voter_delegate where (user_code = ? or voter_is_delegate_id = ?) and constituency_id = ?";
			$values = Array($user_code, $voter_is_delegate_id, $constituency_id);
			$delegate_id = db::select_single_value($query, $values);
			if(!$delegate_id)
				return false;
			$delegate_vote = self::get_delegate_prop_ballot_for_prop($prop_id, $delegate_id);
			if(!empty($delegate_vote)){
				db_vote::insert_prop_ballot($prop_id, $delegate_vote['support_type'], $user_code, $voter_is_delegate_id, $delegate_id, $delegation_level, 1);
				return true;
			}
			$processed_delegates[] = $delegate_id;
			$delegation_level++;
		}
		return false;
	}
}