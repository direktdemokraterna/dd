<?

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

		$query = "insert into constituencies_delegates (constituency_id, delegate_id) select * from (select ? as constituency_id, ? as delegate_id) as tmp where not exists (select * from constituencies_delegates where constituency_id = ? and delegate_id = ?) limit 1";
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

		self::register_yes_no_ballot_for_delegands($delegate_id, $constituency_id, $vote_id, $alternative, $delegate_id, 0);

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

		//self::register_yes_no_ballot_for_delegands($delegate_id, $constituency_id, $vote_id, $alternative, $delegate_id, 0);

		db_vote::count_ballots_for_vote($vote_id);

		if($ok) return true;
		else return false;

	}

	public static function register_yes_no_ballot_for_delegands ($delegate_id, $constituency_id, $vote_id, $alternative, $actual_delegate_voter_id, $delegation_level){

		$delegands = self::get_delegands_for_delegate($delegate_id, $constituency_id);

		foreach($delegands as $delegand){
			if($delegand['voter_is_delegate_id']){ // Delegand is another delegate.
				$ballot = db_vote::get_ballot_from_voter_is_delegate_id($vote_id, $delegand['voter_is_delegate_id']);
				if(empty($ballot)){
					$query = "insert into ballots (vote_id, ballot_alternative, voter_is_delegate_id, delegate_id, delegation_level, delegate_priority, time_ballot_placed) values (?, ?, ?, ?, ?, ?)";
					$values = Array($vote_id, $alternative, $delegand['voter_is_delegate_id'], $actual_delegate_voter_id, $delegation_level, $delegand['priority'], time());

					db::insert($query, $values);

					self::register_yes_no_ballot_for_delegands($delegand['voter_is_delegate_id'], $constituency_id, $vote_id, $alternative, $actual_delegate_voter_id, $delegation_level+1);
				}
				elseif(isset($ballot['delegate_id'])){
					if($ballot['delegation_level'] > $delegation_level || ($ballot['delegation_level'] == $delegation_level && $ballot['priority'] >= $delegand['priority'])){
						$query = "update ballots set ballot_alternative = ?, delegate_id = ?, delegation_level = ?, delegate_priority = ?, time_ballot_placed = ? where vote_id = ? and voter_is_delegate_id = ?";
						$values = Array($alternative, $actual_delegate_voter_id, $delegation_level, $delegand['priority'], time(), $vote_id, $delegand['voter_is_delegate_id']);

						db::update($query, $values);

						self::register_yes_no_ballot_for_delegands($delegand['voter_is_delegate_id'], $constituency_id, $vote_id, $alternative, $actual_delegate_voter_id, $delegation_level+1);
					}
				}
			}

			else{ // Delegand is a normal user.
				$ballot = db_vote::get_ballot_from_user_code($vote_id, $delegand['user_code']);
				if(empty($ballot)){
					$query = "insert into ballots (vote_id, ballot_alternative, user_code, delegate_id, delegation_level, delegate_priority, time_ballot_placed) values (?, ?, ?, ?, ?, ?)";
					$values = Array($vote_id, $alternative, $delegand['user_code'], $actual_delegate_voter_id, $delegation_level, $delegand['priority'], time());

					db::insert($query, $values);
				}
				elseif(isset($ballot['delegate_id'])){
					if($ballot['delegation_level'] > $delegation_level || ($ballot['delegation_level'] == $delegation_level && $ballot['priority'] >= $delegand['priority'])){
						$query = "update ballots set ballot_alternative = ?, delegate_id = ?, delegation_level = ?, delegate_priority = ?, time_ballot_placed = ? where vote_id = ? and user_code = ?";
						$values = Array($alternative, $actual_delegate_voter_id, $delegation_level, $delegand['priority'], time(), $vote_id, $delegand['user_code']);

						db::update($query, $values);
					}
				}
			}
		}

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

		$query = "select v.id as vote_id, v.title as title, v.type as type, b.ballot_alternative as ballot_alternative, b.median_vote_value as median_value, b.prio_ranking as 			prio_ranking 
				from ballots b, votes v 
				where b.vote_id = v.id and b.voter_is_delegate_id = ? and b.delegate_id is null and " . $where_filter . " 
				order by v.timestamp_created desc limit " . $page . ", " . $limit;
		$values = Array($delegate_id);

		return db::select($query, $values);

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

		$query = "select b.voter_is_delegate_id as voter_id, b.prio_ranking as prio_ranking, b.delegate_id as delegate_id, (select d.title from delegates d where b.delegate_id = d.id) as delegate_name from ballots b where b.vote_id = ? and b.voter_is_delegate_id = ?";
		$values = Array($vote_id, $delegate_id);

		return db::select_single_row($query, $values);

	}







	public static function update_delegand_ballots_for_vote ($vote_id, $constituency_id){

		$query = "select distinct vd.user_code as user_code from voters_delegates vd where vd.constituency_id = ? and not exists (select * from ballots b where b.vote_id = ? and b.user_code = vd.user_code)";
		$values = Array($delegate_id, $constituency_id);

		return db::select($query, $values);

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