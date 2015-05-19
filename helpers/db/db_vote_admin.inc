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

}