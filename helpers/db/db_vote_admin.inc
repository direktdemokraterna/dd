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

}