<?

class db_vote {

	public static function get_vote_id_from_prop_id ($prop_id){

		$query = "select id from votes where from_proposition_id = ?";
		$values = Array($prop_id);

		return db::select_single_value($query, $values);

	}

	public static function make_vote_from_prop ($prop_id){

		$prop_data = db_prop::get_prop_info($prop_id);

		$timestamp_delegate_ended = time() + STANDARD_VOTE_LENGTH / 2;
		$timestamp_ended = time() + STANDARD_VOTE_LENGTH;

		$query = "insert into votes (type, from_proposition_id, timestamp_created, timestamp_delegate_ended, timestamp_ended, constituency_id, title, description, forum_topic_id) values (?, ?, ?, ?, ?, ?, ?, ?, ?)";
		$values = Array($prop_data['type'], $prop_id, time(), $timestamp_delegate_ended, $timestamp_ended, $prop_data['constituency_id'], $prop_data['title'], $prop_data['description'], $prop_data['forum_topic_id']);

		$ok = db::insert($query, $values);

		if($ok){
			$query = "update propositions set status = 'affirmed', timestamp_ended = ? where id = ?";
			$values = Array(time(), $prop_id);

			db::update($query, $values);
		}

		return $ok;

	}

	public static function get_vote_info ($vote_id){

		$query = "select v.id as vote_id, v.title as title, v.description as description, (select u.id from users u, propositions p where u.id = p.created_by_user and v.from_proposition_id = p.id) as user_id, (select concat(u.first_name, ' ', u.last_name) from users u, propositions p where u.id = p.created_by_user and v.from_proposition_id = p.id) as user_full_name, v.type as type, v.timestamp_created as timestamp_created, v.timestamp_delegate_ended as timestamp_delegate_ended, v.timestamp_ended as timestamp_ended, v.forum_topic_id as forum_topic_id, c.id as constituency_id, c.title as constituency_name, c.number_of_voters as number_of_voters, v.number_of_alternatives as number_of_alternatives, v.number_of_ballots as number_of_ballots, v.number_of_direct_ballots as number_of_direct_ballots, v.from_proposition_id as from_proposition_id, (select timestamp_created from propositions p where v.from_proposition_id = p.id) as proposition_created, v.status as status  
			from votes v, users u, constituencies c 
			where c.id = v.constituency_id and v.id = ?";
		$values = Array($vote_id);

		return db::select_single_row($query, $values);

	}

	public static function get_vote_ballots ($vote_id){

		$query = "select b.user_code as user_code, va.alternative_title as alternative, b.delegate_id as delegate_id, (select title from delegates d where d.id = b.delegate_id) as delegate_name 
			from ballots b, votes_alternatives va 
			where b.vote_alternative_id = va.id and b.vote_id = ?";
		$values = Array($vote_id);

		return db::select($query, $values);

	}

	public static function register_yes_no_ballot ($vote_id, $user_code, $alternative){

		$query = "delete from ballots where vote_id = ? and user_code = ?";
		$values = Array($vote_id, $user_code);

		db::delete($query, $values);

		$constituency_id = db_constituency::get_vote_constituency_id($vote_id);

		$query = "insert into ballots (vote_id, constituency_id, ballot_alternative, user_code, time_ballot_placed) values (?, ?, ?, ?, ?)";
		$values = Array($vote_id, $constituency_id, $alternative, $user_code, time());

		$return = db::insert($query, $values);

		self::count_ballots_for_vote($vote_id);

		return $return;

	}

	public static function register_median_ballot ($vote_id, $user_code, $value){

		$query = "delete from ballots where vote_id = ? and user_code = ?";
		$values = Array($vote_id, $user_code);

		db::delete($query, $values);

		$constituency_id = db_constituency::get_vote_constituency_id($vote_id);

		$query = "insert into ballots (vote_id, constituency_id, median_vote_value, user_code, time_ballot_placed) values (?, ?, ?, ?, ?)";
		$values = Array($vote_id, $constituency_id, $value, $user_code, time());

		$return = db::insert($query, $values);

		self::count_ballots_for_vote($vote_id);

		return $return;

	}

	public static function register_prio_vote_ballot ($vote_id, $user_code, $prio_ranking){

		$query = "delete from ballots where vote_id = ? and user_code = ?";
		$values = Array($vote_id, $user_code);

		db::delete($query, $values);

		$constituency_id = db_constituency::get_vote_constituency_id($vote_id);

		// Ordering JSON prio ranking so that highest rank is top and lowest rank bottom
		$prio_ranking_array = json_decode($prio_ranking, true);
		arsort($prio_ranking_array, SORT_NUMERIC);
		$sorted_prio_ranking = json_encode($prio_ranking_array);

		$query = "insert into ballots (vote_id, constituency_id, prio_ranking, user_code, time_ballot_placed) values (?, ?, ?, ?, ?)";
		$values = Array($vote_id, $constituency_id, $sorted_prio_ranking, $user_code, time());

		$return = db::insert($query, $values);

		self::count_ballots_for_vote($vote_id);

		return $return;

	}

	public static function get_vote_alternative_from_title ($vote_id, $alternative_title){

		$query = "select id from votes_alternatives where vote_id = ? and alternative_title = ?";
		$values = Array($vote_id, $alternative_title);

		return db::select_single_value($query, $values);

	}

	public static function get_yes_no_ballots ($vote_id){

		$query = "select b.user_code as user_code, b.ballot_alternative as alternative, b.delegate_id as delegate_id, 
					(select d.title from delegates d where b.delegate_id = d.id) as delegate_name 
					from ballots b 
					where user_code is not null and b.vote_id = ?";
		$values = Array($vote_id);

		return db::select($query, $values);

	}

	public static function get_median_ballots ($vote_id){

		$query = "select b.user_code as user_code, b.median_vote_value as value, b.delegate_id as delegate_id, 
					(select d.title from delegates d where b.delegate_id = d.id) as delegate_name 
					from ballots b 
					where user_code is not null and b.vote_id = ?";
		$values = Array($vote_id);

		return db::select($query, $values);

	}

	public static function list_active_votes ($page = 0, $limit = LIST_ITEMS_PER_PAGE, $order_by = "timestamp_created desc", $where_filter = "1=1"){
// NOTE: This db function does not utilise full parametrised input due to bug in current MySQL that doesn't allow parametrised input in limit clause. Variables are instead sanitised by casting as int. When this bug is resolved, this function can be corrected. 

		$page = (int)($page-1) * $limit;
		$limit = (int)$limit;

		$query = "select id, title from votes where " . $where_filter . " and (status = 'active' or status = 'del_ended' or status = 'continuous') order by " . $order_by . " limit " . $page . ", " . $limit;
		$values = Array();

		return db::select($query, $values);

	}

	public static function list_active_votes_count ($where_filter = "1=1"){

		$query = "select count(*) from votes where " . $where_filter . " and (status = 'active' or status = 'del_ended' or status = 'continuous')";
		$values = Array();

		return db::select_single_value($query, $values);

	}

	public static function list_old_votes ($page = 0, $limit = LIST_ITEMS_PER_PAGE, $order_by = "timestamp_created desc", $where_filter = "1=1"){
// NOTE: This db function does not utilise full parametrised input due to bug in current MySQL that doesn't allow parametrised input in limit clause. Variables are instead sanitised by casting as int. When this bug is resolved, this function can be corrected. 

		$page = (int)($page-1) * $limit;
		$limit = (int)$limit;

		$query = "select id, title from votes where " . $where_filter . " and (status = 'ended' or status = 'finished') order by " . $order_by . " limit " . $page . ", " . $limit;
		$values = Array();

		return db::select($query, $values);

	}

	public static function list_old_votes_count ($where_filter = "1=1"){

		$query = "select count(*) from votes where " . $where_filter . " and (status = 'ended' or status = 'finished')";
		$values = Array();

		return db::select_single_value($query, $values);

	}

	public static function get_ballot_from_user_code ($vote_id, $user_code){

		$query = "select id, ballot_alternative, vote_alternative_id, priority, median_vote_value, delegate_id, time_ballot_placed, delegate_level, delegate_priority, (select vd.priority from voters_delegates vd, votes v where v.constituency_id = vd.constituency_id and vd.user_code = b.user_code and vd.delegate_id = b.delegate_id) as priority from ballots b where b.vote_id = ? and b.user_code = ?";
		$values = Array($vote_id, $user_code);

		return db::select_single_row($query, $values);

	}

	public static function get_ballot_from_voter_is_delegate_id ($vote_id, $voter_is_delegate_id){

		$query = "select id, ballot_alternative, vote_alternative_id, priority, median_vote_value, delegate_id, time_ballot_placed, delegate_level, delegate_priority, (select vd.priority from voters_delegates vd, votes v where v.constituency_id = vd.constituency_id and vd.user_code = b.user_code and vd.delegate_id = b.delegate_id) as priority from ballots b where b.vote_id = ? and b.voter_is_delegate_id = ?";
		$values = Array($vote_id, $voter_is_delegate_id);

		return db::select_single_row($query, $values);

	}

	public static function count_ballots_for_vote ($vote_id){

		$query = "update votes set number_of_ballots = (select count(*) from ballots where vote_id = ? and user_code is not null), number_of_direct_ballots = (select count(*) from ballots where vote_id = ? and user_code is not null and delegate_id is null) where id = ?";
		$values = Array($vote_id, $vote_id, $vote_id);

		return db::update($query, $values);

	}

	public static function get_alternative_ids_from_vote_id ($vote_id){

		$query = "select id from votes_alternatives where vote_id = ?";
		$values = Array($vote_id);

		return db::select($query, $values);

	}

	public static function get_prio_vote_ballots ($vote_id){

		$query = "select b.user_code as user_code, b.prio_ranking as prio_ranking, b.delegate_id as delegate_id, 
					(select d.title from delegates d where b.delegate_id = d.id) as delegate_name 
					from ballots b 
					where user_code is not null and b.vote_id = ?";
		$values = Array($vote_id);

		return db::select($query, $values);

	}

	public static function get_prio_vote_ballots_without_extra_info ($vote_id){

		$query = "select prio_ranking as prio_ranking from ballots where user_code is not null and vote_id = ?";
		$values = Array($vote_id);

		return db::select($query, $values);

	}

	public static function add_alternative_by_user ($vote_id, $title, $description, $user_id){

		$query = "insert into votes_alternatives (vote_id, added_by_user, timestamp_added, alternative_title, alternative_description) values (?, ?, ?, ?, ?)";
		$values = Array($vote_id, $user_id, time(), htmlspecialchars($title), htmlspecialchars($description));

		$return =  db::insert($query, $values);

		self::update_number_of_alternatives($vote_id);

		return $return;

	}

	public static function add_alternative_by_delegate ($vote_id, $title, $description, $delegate_id){

		$query = "insert into votes_alternatives (vote_id, added_by_delegate, timestamp_added, alternative_title, alternative_description) values (?, ?, ?, ?, ?)";
		$values = Array($vote_id, $delegate_id, time(), htmlspecialchars($title), htmlspecialchars($description));

		$return =  db::insert($query, $values);

		self::update_number_of_alternatives($vote_id);

		return $return;

	}

	public static function add_candidate ($vote_id, $user_id, $description){

		$query = "insert into votes_alternatives (vote_id, added_by_user, timestamp_added, alternative_user_id, alternative_title, alternative_description) values (?, ?, ?, ?, ?, ?)";
		$values = Array($vote_id, $user_id, time(), $user_id, db_user::get_user_full_name($user_id), htmlspecialchars($description));

		$return = db::insert($query, $values);

		self::update_number_of_alternatives($vote_id);

		return $return;

	}

	public static function remove_candidate ($vote_id, $user_id){

		$query = "delete from votes_alternatives where vote_id = ? and alternative_user_id = ?";
		$values = Array($vote_id, $user_id);

		$return = db::delete($query, $values);

		self::update_number_of_alternatives($vote_id);

		return $return;

	}

	public static function update_number_of_alternatives ($vote_id){

		$query = "update votes v set number_of_alternatives = (select count(*) from votes_alternatives va where va.vote_id = v.id) where v.id = ?";
		$values = Array($vote_id);

		return db::update($query, $values);

	}

	public static function get_alternatives_for_vote ($vote_id){

		$query = "select id, alternative_title as title, alternative_description as description from votes_alternatives where vote_id = ? order by timestamp_added asc";
		$values = Array($vote_id);

		return db::select($query, $values);

	}

	public static function get_candidates_for_vote ($vote_id){

		$query = "select id, alternative_user_id as user_id, alternative_title as user_name, alternative_title as title, alternative_description as description from votes_alternatives where vote_id = ? order by timestamp_added asc";
		$values = Array($vote_id);

		return db::select($query, $values);

	}

	public static function get_alternative_info ($alternative_id){

		$query = "select * from votes_alternatives where id = ?";
		$values = Array($alternative_id);

		return db::select_single_row($query, $values);

	}

	public static function get_alternative_title ($alternative_id){

		$query = "select alternative_title as title from votes_alternatives where id = ?";
		$values = Array($alternative_id);

		return db::select_single_value($query, $values);

	}

	public static function get_alternative_candidate_info ($alternative_id){

		$query = "select alternative_user_id as user_id, alternative_title as user_name from votes_alternatives where id = ?";
		$values = Array($alternative_id);

		return db::select_single_row($query, $values);

	}

	public static function is_user_candidate_in_vote ($user_id, $vote_id){

		$query = "select id from votes_alternatives where alternative_user_id = ? and vote_id = ?";
		$values = Array($user_id, $vote_id);

		$result =  db::select_single_value($query, $values);

		if(empty($result)) return false;
		else return true;

	}

	public static function get_vote_type_from_id ($vote_id){

		$query = "select type from votes where id = ?";
		$values = Array($vote_id);

		return db::select_single_value($query, $values);

	}

}