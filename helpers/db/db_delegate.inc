<?php

class db_delegate {

	public static function is_user_delegate ($user_id){

		$query = "select count(*) from delegates_users where user_id = ?";
		$values = Array($user_id);

		$result = db::select_single_value($query, $values);

		if($result == 1){
			return true;
		}
		else{
			return false;
		}

	}

	public static function get_delegate_settings ($user_id){

		$query = "select d.id as delegate_id, d.title as title, d.description as description 
			from delegates d, delegates_users du 
			where d.id = du.delegate_id and du.user_id = ?";
		$values = Array($user_id);

		return db::select_single_row($query, $values);

	}

	public static function get_constituencies_for_delegate ($delegate_id){

		$query = "select c.id as id, c.title as title 
			from constituencies c, constituencies_delegates cd 
			where c.id = cd.constituency_id and cd.delegate_id = ?";
		$values = Array($user_id);

		return db::select($query, $values);

	}

	public static function get_delegates_for_constituency ($constituency_id){

		$query = "select d.id as id, d.title as title 
			from delegates d, constituencies_delegates cd 
			where d.id = cd.delegate_id and cd.constituency_id = ?";
		$values = Array($constituency_id);

		return db::select($query, $values);

	}

	public static function create_delegate ($user_id){

		$user_full_name = db_user::get_user_full_name($user_id);

		$db_table = "delegates";
		$columns = Array("title");
		$values = Array($user_full_name);

		$delegate_id = db::insert_ignore($db_table, $columns, $values);

		if($delegate_id){

			$query = "insert into delegates_users (delegate_id, user_id) values (?, ?)";
			$values = Array($delegate_id, $user_id);

			db::insert($query, $values);

			return $delegate_id;

		}
		else{
			return false;
		}

	}

	public static function get_delegate_id_from_user_id ($user_id){

		$query = "select delegate_id from delegates_users where user_id = ?";
		$values = Array($user_id);

		return db::select_single_value($query, $values);

	}

	public static function get_user_id_from_delegate_id ($delegate_id){

		$query = "select user_id from delegates_users where delegate_id = ?";
		$values = Array($delegate_id);

		return db::select_single_value($query, $values);

	}

	public static function start_acting_as_delegate ($user_id){

		$query = "update users set acting_as_delegate = 1 where id = ?";
		$values = Array($user_id);

		return db::update($query, $values);

	}

	public static function stop_acting_as_delegate ($user_id){

		$query = "update users set acting_as_delegate = 0 where id = ?";
		$values = Array($user_id);

		return db::update($query, $values);

	}

	public static function get_constituencies_for_user_and_delegate_activity ($user_id, $delegate_id){

		$query = "select c.id as constituency_id, c.title as constituency_title, 
					(select id from constituencies_delegates cd where cd.constituency_id = c.id and cd.delegate_id = ?) as delegate_active 
					from constituencies c, constituencies_users cu 
					where c.id = cu.constituency_id and cu.user_id = ?";
		$values = Array($delegate_id, $user_id);

		return db::select($query, $values);

	}

	public static function update_delegate_constituencies ($constituency_ids, $user_id){

		$delegate_id = self::get_delegate_id_from_user_id($user_id);

		// Checking constituency access for user behind delegate
		foreach($constituency_ids as $key => $value){
			if(!db_constituency::check_user_constituency_access($user_id, $value)){
				unset($constituency_ids[$key]);
			}
		}

		$not_in_clause = implode(',', array_fill(0, count($constituency_ids), '?'));

		$query = "delete from constituencies_delegates where constituency_id not in (" . $not_in_clause . ") and delegate_id = ?";
		$values = $constituency_ids;
		array_push($values, $delegate_id);

		$deleted = db::delete($query, $values);

		$query = "insert into constituencies_delegates (constituency_id, delegate_id) select ? as constituency_id, ? as delegate_id from dual where not exists (select * from constituencies_delegates where constituency_id = ? and delegate_id = ?) limit 1";
		$inserted = db::insert_ignore_from_array($query, $constituency_ids, $delegate_id);

		return $deleted + $inserted;

	}

	public static function remove_all_delegate_constituencies ($user_id){

		$delegate_id = self::get_delegate_id_from_user_id($user_id);

		$query = "delete from constituencies_delegates where delegate_id = ?";
		$values = Array($delegate_id);

		return db::update($query, $values);

	}

	public static function register_yes_no_ballot ($vote_id, $delegate_id, $alternative){

		$query = "delete from ballots where vote_id = ? and voter_is_delegate_id = ?";
		$values = Array($vote_id, $delegate_id);

		db::delete($query, $values);

		$constituency_id = db_constituency::get_vote_constituency_id($vote_id);

		$query = "insert into ballots (vote_id, constituency_id, ballot_alternative, voter_is_delegate_id, time_ballot_placed) values (?, ?, ?, ?, ?)";
		$values = Array($vote_id, $constituency_id, $alternative, $delegate_id, time());

		$ok = db::insert($query, $values);

		self::register_ballot_for_delegands($delegate_id, $constituency_id, $vote_id, $alternative, null, null, $delegate_id, 0);

		db_vote::count_ballots_for_vote($vote_id);

		if($ok) return true;
		else return false;

	}

	public static function register_prio_ballot ($vote_id, $delegate_id, $prio_ranking){

		$query = "delete from ballots where vote_id = ? and voter_is_delegate_id = ?";
		$values = Array($vote_id, $delegate_id);

		db::delete($query, $values);

		$constituency_id = db_constituency::get_vote_constituency_id($vote_id);

		$query = "insert into ballots (vote_id, constituency_id, prio_ranking, voter_is_delegate_id, time_ballot_placed) values (?, ?, ?, ?, ?)";
		$values = Array($vote_id, $constituency_id, $prio_ranking, $delegate_id, time());

		$ok = db::insert($query, $values);

		self::register_ballot_for_delegands($delegate_id, $constituency_id, $vote_id, null, $prio_ranking, null, $delegate_id, 0);

		db_vote::count_ballots_for_vote($vote_id);

		if($ok) return true;
		else return false;

	}

	public static function register_ballot_for_delegands ($delegate_id, $constituency_id, $vote_id, $ballot_alternative, $prio_ranking, $median_vote_value, $actual_delegate_voter_id, $delegation_level){

		$delegands = self::get_delegands_for_delegate($delegate_id, $constituency_id);

		foreach($delegands as $delegand){
			
			$ballot = db_vote::get_ballot_from_delegate_or_user($vote_id, $delegand['user_code'], $delegand['voter_is_delegate_id']);

			if(empty($ballot)){
				$query = "insert into ballots (vote_id, constituency_id, ballot_alternative, prio_ranking, median_vote_value, user_code, voter_is_delegate_id, delegate_id, delegation_level, delegate_priority, time_ballot_placed) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
				$values = Array($vote_id, $constituency_id, $ballot_alternative, $prio_ranking, $median_vote_value, $delegand['user_code'], $delegand['voter_is_delegate_id'], $actual_delegate_voter_id, $delegation_level, $delegand['priority'], time());

				db::insert($query, $values);

				if($delegand['voter_is_delegate_id']){ // Delegand is another delegate.
					self::register_ballot_for_delegands($delegand['voter_is_delegate_id'], $constituency_id, $vote_id, $ballot_alternative, $prio_ranking, $median_vote_value, $actual_delegate_voter_id, $delegation_level+1);
				}
			}
			elseif(isset($ballot['delegate_id']) && ($ballot['delegation_level'] > $delegation_level || $ballot['delegate_id'] == $actual_delegate_voter_id)){
				$query = "update ballots set ballot_alternative = ?, prio_ranking = ?, median_vote_value = ?, delegate_id = ?, delegation_level = ?, delegate_priority = ?, time_ballot_placed = ? where vote_id = ? and (user_code = ? or voter_is_delegate_id = ?)";
				$values = Array($ballot_alternative, $prio_ranking, $median_vote_value, $actual_delegate_voter_id, $delegation_level, $delegand['priority'], time(), $vote_id, $delegand['user_code'], $delegand['voter_is_delegate_id']);

				db::update($query, $values);

				if($delegand['voter_is_delegate_id']){ // Delegand is another delegate.
					self::register_ballot_for_delegands($delegand['voter_is_delegate_id'], $constituency_id, $vote_id, $ballot_alternative, $prio_ranking, $median_vote_value, $actual_delegate_voter_id, $delegation_level+1);
				}
			}

		}

	}

	public static function register_prop_ballot ($prop_id, $delegate_id, $support_type){

		$query = "delete from propositions_support where prop_id = ? and voter_is_delegate_id = ?";
		$values = Array($prop_id, $delegate_id);

		db::delete($query, $values);

		$constituency_id = db_constituency::get_prop_constituency_id($prop_id);

		$query = "insert into propositions_support (prop_id, constituency_id, prio_ranking, voter_is_delegate_id, time_ballot_placed) values (?, ?, ?, ?, ?)";
		$values = Array($vote_id, $constituency_id, $prio_ranking, $delegate_id, time());

		$ok = db::insert($query, $values);

		self::register_ballot_for_delegands($delegate_id, $constituency_id, $vote_id, null, $prio_ranking, null, $delegate_id, 0);

		db_vote::count_ballots_for_vote($vote_id);

		if($ok) return true;
		else return false;

	}

	public static function get_delegands_for_delegate ($delegate_id, $constituency_id){

		$query = "select user_code, voter_is_delegate_id, priority from voters_delegates where delegate_id = ? and constituency_id = ?";
		$values = Array($delegate_id, $constituency_id);

		return db::select($query, $values);

	}

	public static function list_delegates_for_user_constituencies ($user_id, $page = 0, $limit = LIST_ITEMS_PER_PAGE, $order_by = "timestamp_created desc", $where_filter = "1=1"){
// NOTE: This db function does not utilise full parametrised input due to bug in current MySQL that doesn't allow parametrised input in limit clause. Variables are instead sanitised by casting as int. When this bug is resolved, this function can be corrected. 

		$page = (int)($page-1) * $limit;
		$limit = (int)$limit;

		$query = "select d.id as id, d.title as title from delegates d where exists (select * from constituencies_delegates cd, constituencies_users cu where cd.delegate_id = d.id and cd.constituency_id = cu.constituency_id and cu.user_id = ? and " . $where_filter . ") order by " . $order_by . " limit " . $page . ", " . $limit;
		$values = Array($user_id);

		return db::select($query, $values);

	}

	public static function list_delegates_for_user_constituencies_count ($user_id, $where_filter = "1=1"){

		$query = "select count(*) from delegates d where exists (select * from constituencies_delegates cd, constituencies_users cu where cd.delegate_id = d.id and cd.constituency_id = cu.constituency_id and cu.user_id = ? and " . $where_filter . ")";
		$values = Array($user_id);

		return db::select_single_value($query, $values);

	}

	public static function get_delegate_info ($delegate_id){

		$query = "select title, description from delegates where id = ?";
		$values = Array($delegate_id);

		return db::select_single_row($query, $values);

	}

	public static function list_delegate_ballots ($delegate_id, $page = 0, $limit = LIST_ITEMS_PER_PAGE_SHORT, $where_filter = "1=1"){
// NOTE: This db function does not utilise full parametrised input due to bug in current MySQL that doesn't allow parametrised input in limit clause. Variables are instead sanitised by casting as int. When this bug is resolved, this function can be corrected. 

		$page = (int)($page-1) * $limit;
		$limit = (int)$limit;

		$query = "select v.id as vote_id, v.title as title, v.type as type, b.ballot_alternative as ballot_alternative, b.median_vote_value as median_value, b.prio_ranking as 			prio_ranking, b.delegate_id as delegate_id, (select title from delegates d where d.id = b.delegate_id) as delegate_name 
				from ballots b, votes v 
				where b.vote_id = v.id and b.voter_is_delegate_id = ? and " . $where_filter . " 
				order by v.timestamp_created desc limit " . $page . ", " . $limit;
		$values = Array($delegate_id);

		return db::select($query, $values);

	}

	public static function get_delegate_ballot_for_vote ($vote_id, $delegate_id){

		$query = "select ballot_alternative, median_vote_value, prio_ranking 
				from ballots where vote_id = ? and voter_is_delegate_id = ? and delegate_id is null";
		$values = Array($vote_id, $delegate_id);

		return db::select_single_row($query, $values);

	}

	public static function list_delegate_ballots_count ($delegate_id, $where_filter = "1=1"){

		$query = "select count(*)
				from ballots b, votes v 
				where b.vote_id = v.id and b.voter_is_delegate_id = ? and b.delegate_id is null and " . $where_filter;
		$values = Array($delegate_id);

		return db::select_single_value($query, $values);

	}

	public static function get_complete_list_of_user_delegations (){

		$query = "select vd.user_code as user_code, vd.constituency_id as constituency_id, vd.delegate_id as delegate_id, 
					(select d.title from delegates d where vd.delegate_id = d.id) as delegate_name 
					from voters_delegates vd 
					where user_code is not null";
		$values = Array($vote_id);

		return db::select($query, $values);

	}

	public static function get_ballot_for_vote ($vote_id, $delegate_id){

		$query = "select b.voter_is_delegate_id as voter_id, b.ballot_alternative as ballot_alternative, b.prio_ranking as prio_ranking, b.median_vote_value as median_vote_value, b.delegate_id as delegate_id, (select d.title from delegates d where b.delegate_id = d.id) as delegate_name from ballots b where b.vote_id = ? and b.voter_is_delegate_id = ?";
		$values = Array($vote_id, $delegate_id);

		return db::select_single_row($query, $values);

	}

	public static function update_delegand_ballots_for_vote ($vote_id, $constituency_id){

		$query = "select distinct vd.user_code as user_code from voters_delegates vd where vd.constituency_id = ? and not exists (select * from ballots b where b.vote_id = ? and b.user_code = vd.user_code)";
		$values = Array($delegate_id, $constituency_id);

		return db::select($query, $values);

	}

	public static function get_delegations_for_multiple_constituencies ($constituencies){

		$in_clause = implode(',', array_fill(0, count($constituencies), '?'));


		$query = "select vd.user_code as user_code, vd.constituency_id as constituency_id, vd.delegate_id as delegate_id, d.title as delegate_name 
					from voters_delegates vd, delegates d 
					where vd.delegate_id = d.id and vd.voter_is_delegate_id is null and vd.constituency_id in (" . $in_clause . ")";
		$values = Array();
		foreach($constituencies as $row){
			$values[] = $row['id'];
		}

		return db::select($query, $values);

	}

	public static function register_delegation_ballot ($user_code, $delegand_id, $delegate_id, $constituency_id, $priority = 1){

		$query = "select * from voters_delegates where (user_code = ? or voter_is_delegate_id = ?) and constituency_id = ?";
		$values = Array($user_code, $delegand_id, $constituency_id);

		$result = db::select_single_row($query, $values);

		if(!empty($result)){

			$query = "delete from voters_delegates where (user_code = ? or voter_is_delegate_id = ?) and constituency_id = ?";	
			$values = Array($user_code, $delegand_id, $constituency_id);

			db::delete($query, $values);

			if($delegate_id == "null"){
				self::remove_delegate_votes($user_code, $delegand_id, $result['delegate_id'], $constituency_id);
			}

		}

		if($delegate_id != "null"){
			$query = "insert into voters_delegates (delegate_id, user_code, voter_is_delegate_id, constituency_id, time_delegate_chosen) values (?, ?, ?, ?, ?)";
			$values = Array($delegate_id, $user_code, $delegand_id, $constituency_id, time());

			db::insert($query, $values);

			self::execute_delegate_votes_for_new_delegate($user_code, $delegand_id, $delegate_id, $constituency_id);
		}

		return true; 

	}

	public static function remove_delegate_votes ($user_code, $delegand_id, $delegate_id, $constituency_id){

		$query = "delete from ballots where (user_code = ? or voter_is_delegate_id = ?) and delegate_id = ? and constituency_id = ?";
		$values = Array($user_code, $delegand_id, $delegate_id, $constituency_id);

		return db::delete($query, $values);

	}

	public static function get_delegate_ballots_for_vote ($vote_id){

		$query = "select b.voter_is_delegate_id as voter_is_delegate_id, b.ballot_alternative as alternative, b.prio_ranking as prio_ranking, b.median_vote_value as value, b.delegate_id as delegate_id, 
					(select d.title from delegates d where b.delegate_id = d.id) as delegate_name 
					from ballots b 
					where b.voter_is_delegate_id is not null and b.vote_id = ?";
		$values = Array($vote_id);

		return db::select($query, $values);

	}

	public static function execute_delegate_votes_for_new_delegate ($user_code, $delegand_id, $delegate_id, $constituency_id){

		$relevant_votes = db_delegate::get_votes_with_no_direct_ballots($constituency_id, $user_code, $delegand_id);

		foreach ($relevant_votes as $row) {
			$delegate_ballot = self::get_ballot_for_vote($row['id'], $delegate_id);
			self::register_ballot_for_delegands($delegate_id, $constituency_id, $row['id'], $delegate_ballot['ballot_alternative'], $delegate_ballot['prio_ranking'], $delegate_ballot['median_vote_value'], $delegate_id, 1);
		}

	}

	public static function get_votes_with_no_direct_ballots ($constituency_id, $user_code, $delegand_id){

		$query = "select v.id as id from votes v where v.constituency_id = ? and not exists (select * from ballots b where (b.user_code = ? or b.voter_is_delegate_id = ?) and b.vote_id = v.id and b.delegate_id is null)";
		$values = Array($constituency_id, $user_code, $delegand_id);

		return db::select($query, $values);


	}

	public static function get_delegate_delegates ($delegand_id){

		$query = "select d.id as delegate_id, d.title as delegate_title, c.id as constituency_id, c.title as constituency_title, vd.time_delegate_chosen as time_delegate_chosen
			from voters_delegates vd, delegates d, constituencies c
			where vd.delegate_id = d.id and vd.constituency_id = c.id and vd.voter_is_delegate_id = ?";
		$values = Array($delegand_id);

		return db::select($query, $values);

	}

	public static function get_delegates_delegate_for_constituency ($delegand_id, $constituency_id){

		$query = "select d.id as delegate_id, d.title as delegate_title, vd.time_delegate_chosen as time_delegate_chosen
			from voters_delegates vd, delegates d
			where vd.delegate_id = d.id and vd.voter_is_delegate_id = ? and vd.constituency_id = ?";
		$values = Array($delegand_id, $constituency_id);

		return db::select_single_row($query, $values);

	}

/*
"update ballots b 
	left join delegate_ballots db
		on b.vote_id = db.vote_id
	left join voters_delegates vd 
		on vd.user_code = b.user_code and b.constituency_id = vd.constituency_id 
	set b.ballot_alternative = db.ballot_alternative, b.vote_alternative_id = db.vote_alternative_id, b.priority = db.priority, b.median_vote_value = db.median_vote_value, b.delegate_id = vd.delegate_id, b.delegate_priority = vd.priority, time_ballot_placed = ? 
	where (b.delegate_id is not null and b.delegate_priority > vd.priority) or (b.delegate_id = vd.delegate_id and (b.ballot_alternative != db.ballot_alternative or b.vote_alternative_id != db.vote_alternative_id or b.priority != db.priority or b.median_vote_value != db.median_vote_value))"
*/



}