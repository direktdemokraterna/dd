<?

class db_vote_admin {
	
	public static function update_vote ($type, $constituency_id, $title, $description, $forum_topic_id, $vote_id){

		$query = "update votes set type = ?, constituency_id = ?, title = ?, description = ?, forum_topic_id = ? where id = ?";
		$values = Array($type, $constituency_id, htmlspecialchars($title), htmlspecialchars($description), $forum_topic_id, $vote_id);

		return db::update($query, $values);

	}

	public static function update_time_ended ($timestamp_ended, $timestamp_delegate_ended, $vote_id){

		$query = "update votes set timestamp_ended = ?, timestamp_delegate_ended = ? where id = ?";
		$values = Array($timestamp_ended, $timestamp_delegate_ended, $vote_id);

		return db::update($query, $values);

	}

	public static function create_vote ($type, $status, $constituency_id, $title, $description, $forum_topic_id, $timestamp_ended, $timestamp_delegate_ended){

		$query = "insert into votes (type, status, constituency_id, title, description , forum_topic_id, timestamp_created, timestamp_ended, timestamp_delegate_ended) values (?, ?, ?, ?, ?, ?, ?, ?, ?)";
		$values = Array($type, $status, $constituency_id, htmlspecialchars($title), htmlspecialchars($description), $forum_topic_id, time(), $timestamp_ended, $timestamp_delegate_ended);

		return db::insert($query, $values);

	}

	public static function delete_alternatives ($alternative_ids, $vote_id){

		$in_clause = implode(',', array_fill(0, count($alternative_ids), '?'));

		$query = "delete from votes_alternatives where id in (" . $in_clause . ")";
		$values = $alternative_ids;

		$return = db::delete($query, $values);

		db_vote::update_number_of_alternatives($vote_id['vote_id']);

		return $return;

	}

	public static function add_alternative_by_admin ($vote_id, $title, $description){

		$query = "insert into votes_alternatives (vote_id, timestamp_added, alternative_title, alternative_description) values (?, ?, ?, ?)";
		$values = Array($vote_id, time(), htmlspecialchars($title), htmlspecialchars($description));

		$return = db::insert($query, $values);

		db_vote::update_number_of_alternatives($vote_id);

		return $return; 

	}

	public static function update_alternative ($alternative_title, $alternative_description, $alternative_id){

		$query = "update votes_alternatives set alternative_title = ?, alternative_description = ? where id = ?";
		$values = Array(htmlspecialchars($alternative_title), htmlspecialchars($alternative_description), $alternative_id);

		return db::update($query, $values);

	}

	public static function get_votes_past_end_time (){

		$query = "select id from votes where timestamp_ended < ? and (status = 'active' or status = 'del_ended')";
		$values = Array(time());

		return db::select($query, $values);

	}

	public static function end_vote ($vote_id){

		$query = "update votes set status = 'ended', timestamp_ended = ? where id = ?";
		$values = Array(time(), $vote_id);

		return db::update($query, $values);

	}

	public static function end_delegate_vote ($vote_id){

		$query = "update votes set status = 'del_ended', timestamp_delegate_ended = ? where id = ?";
		$values = Array(time(), $vote_id);

		return db::update($query, $values);

	}

	public static function restore_delegate_vote ($vote_id){

		$query = "update votes set status = 'active', timestamp_delegate_ended = " . time() . " + (timestamp_ended - " . time() . ")/2 where id = ?";
		$values = Array($vote_id);

		return db::update($query, $values);

	}

	public static function restore_vote ($vote_id){

		$query = "update votes set status = 'active', timestamp_ended = ?, timestamp_delegate_ended = ? where id = ?";
		$values = Array(time()+STANDARD_VOTE_LENGTH, time()+STANDARD_VOTE_LENGTH/2, $vote_id);

		return db::update($query, $values);

	}

	public static function finish_vote ($vote_id){

		$query = "update votes set status = 'finished', timestamp_ended = ? where id = ?";
		$values = Array(time(), $vote_id);

		return db::update($query, $values);

	}

	public static function restore_finished_vote ($vote_id){

		$query = "update votes set status = 'continuous', timestamp_ended = null where id = ?";
		$values = Array($vote_id);

		return db::update($query, $values);

	}

	public static function make_continuous ($vote_id){

		$query = "update votes set status = 'continuous', timestamp_ended = null, timestamp_delegate_ended = null where id = ?";
		$values = Array($vote_id);

		return db::update($query, $values);

	}

	public static function make_active ($vote_id){

		$query = "update votes set status = 'active', timestamp_ended = ?, timestamp_delegate_ended = ? where id = ?";
		$values = Array(time()+STANDARD_VOTE_LENGTH, time()+STANDARD_VOTE_LENGTH/2, $vote_id);

		return db::update($query, $values);

	}

	public static function delegate_end_votes (){

		$query = "update votes set status = 'del_ended' where timestamp_delegate_ended < ? and status = 'active'";
		$values = Array(time());

		return db::update($query, $values);

	}

	public static function get_user_codes_for_vote ($vote_id){

		$query = "select user_code from ballots where vote_id = ?";
		$values = Array($vote_id);

		return db::select($query, $values);

	}

	public static function set_active_user_code_to_passive ($active_user_code, $passive_user_code, $vote_id){

		$query = "update ballots set user_code = ? where user_code = ? and vote_id = ?";
		$values = Array($passive_user_code, $active_user_code, $vote_id);

		return db::update($query, $values);

	}

	public static function set_passive_user_code_to_active ($active_user_code, $passive_user_code, $vote_id){

		$query = "update ballots set user_code = ? where user_code = ? and vote_id = ?";
		$values = Array($active_user_code, $passive_user_code, $vote_id);

		return db::update($query, $values);

	}

}