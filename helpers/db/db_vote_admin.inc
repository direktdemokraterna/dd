<?php

class db_vote_admin 
{	
	public static function update_vote ($type, $title, $description, $forum_topic_id, $vote_id)
	{
		$query = "update vote set type = ?, title = ?, description = ?, forum_topic_id = ? where id = ?";
		$values = Array($type, general_helpers::clean($title), general_helpers::clean($description), $forum_topic_id, $vote_id);
		return db::update($query, $values);
	}

	public static function change_constituency ($constituency_id, $vote_id)
	{
		$old_constituency = db_vote::get_constituency_id_for_vote($vote_id);
		$query = "update vote set constituency_id = ? where id = ?";
		$values = Array($constituency_id, $vote_id);
		return db::update($query, $values);
	}

	public static function update_time_ended ($timestamp_ended, $timestamp_delegate_ended, $vote_id)
	{
		$query = "update vote set timestamp_ended = ?, timestamp_delegate_ended = ? where id = ?";
		$values = Array($timestamp_ended, $timestamp_delegate_ended, $vote_id);
		return db::update($query, $values);
	}

	public static function create_vote ($type, $status, $constituency_id, $title, $description, 
		$forum_topic_id, $timestamp_ended, $timestamp_delegate_ended)
	{
		$query = "insert into vote (type, status, constituency_id, title, description , forum_topic_id, timestamp_created, timestamp_ended, timestamp_delegate_ended) values (?, ?, ?, ?, ?, ?, ?, ?, ?)";
		$values = Array($type, $status, $constituency_id, $title, $description, $forum_topic_id, time(), $timestamp_ended, $timestamp_delegate_ended);
		$return_value = db::insert($query, $values);
		db_notice::make_vote_started_notice($vote_id);
		return $return_value;
	}

	public static function create_workgroup_election ($workgroup_id, $constituency_id, $title, $description, $forum_topic_id)
	{
		$query = "insert into vote (type, status, from_proposition_id, constituency_id, title, description, forum_topic_id, timestamp_created) values (?, ?, ?, ?, ?, ?, ?, ?)";
		$values = Array("workgroup-election", "continuous", $workgroup_id, $constituency_id, $title, $description, $forum_topic_id, time());
		$return_value = db::insert($query, $values);
		db_notice::make_vote_started_notice($vote_id);
		return $return;
	}

	public static function delete_alternatives ($alternative_ids, $vote_id)
	{
		$in_clause = implode(',', array_fill(0, count($alternative_ids), '?'));
		$query = "delete from vote_alternative where id in (" . $in_clause . ")";
		$values = $alternative_ids;
		$result = db::delete($query, $values);
		db_vote::update_number_of_alternatives($vote_id['vote_id']);
		return $result;
	}

	public static function add_alternative_by_admin ($vote_id, $title, $description)
	{
		$query = "insert into vote_alternative (vote_id, timestamp_added, alternative_title, alternative_description) values (?, ?, ?, ?)";
		$values = Array($vote_id, time(), general_helpers::clean($title), general_helpers::clean($description));
		$result = db::insert($query, $values);
		db_vote::update_number_of_alternatives($vote_id);
		return $result; 
	}

	public static function update_alternative ($alternative_title, $alternative_description, $alternative_id)
	{
		$query = "update vote_alternative set alternative_title = ?, alternative_description = ? where id = ?";
		$values = Array(general_helpers::clean($alternative_title), general_helpers::clean($alternative_description), $alternative_id);
		return db::update($query, $values);
	}

	public static function get_votes_past_end_time ()
	{
		$query = "select id from vote where timestamp_ended < ? and (status = 'active' or status = 'del_ended')";
		$values = Array(time());
		return db::select($query, $values);
	}

	public static function end_vote ($vote_id)
	{
		$query = "update vote set status = 'ended', timestamp_ended = ? where id = ?";
		$values = Array(time(), $vote_id);
		$return_value = db::update($query, $values);
		db_notice::make_vote_finished_notice($vote_id);
		return $return;
	}

	public static function end_delegate_vote ($vote_id)
	{
		$query = "update vote set status = 'del_ended', timestamp_delegate_ended = ? where id = ?";
		$values = Array(time(), $vote_id);
		return db::update($query, $values);
	}

	public static function restore_delegate_vote ($vote_id)
	{
		$query = "update vote set status = 'active', timestamp_delegate_ended = " . time() . " + (timestamp_ended - " . time() . ")/2 where id = ?";
		$values = Array($vote_id);
		return db::update($query, $values);
	}

	public static function restore_vote ($vote_id)
	{
		$query = "update vote set status = 'active', timestamp_ended = ?, timestamp_delegate_ended = ? where id = ?";
		$values = array(time()+STANDARD_VOTE_LENGTH, time()+STANDARD_VOTE_LENGTH/2, $vote_id);
		$result = db::update($query, $values);
		if ($result) 
			self::remove_all_ballots($vote_id);
		return $result;
	}

	public static function finish_vote ($vote_id)
	{
		$query = "update vote set status = 'finished', timestamp_ended = ? where id = ?";
		$values = Array(time(), $vote_id);
		$return_value = db::update($query, $values);
		db_notice::make_vote_finished_notice($vote_id);
		return $return;
	}

	public static function restore_finished_vote ($vote_id)
	{
		$query = "update vote set status = 'continuous', timestamp_ended = null where id = ?";
		$values = Array($vote_id);
		$result = db::update($query, $values);
		if ($result) 
			self::remove_all_ballots($vote_id);
		return $result;
	}

	public static function make_continuous ($vote_id)
	{
		$query = "update vote set status = 'continuous', timestamp_ended = null, timestamp_delegate_ended = null where id = ?";
		$values = Array($vote_id);
		return db::update($query, $values);
	}

	public static function make_active ($vote_id)
	{
		$query = "update vote set status = 'active', timestamp_ended = ?, timestamp_delegate_ended = ? where id = ?";
		$values = Array(time()+STANDARD_VOTE_LENGTH, time()+STANDARD_VOTE_LENGTH/2, $vote_id);
		return db::update($query, $values);
	}

	public static function delegate_end_votes ()
	{
		$query = "update vote set status = 'del_ended' where timestamp_delegate_ended < ? and status = 'active'";
		$values = Array(time());
		return db::update($query, $values);
	}

	private static function remove_all_ballots ($vote_id)
	{
		$query = "delete from ballot 
			where vote_id = ?";
		if (db::delete($query, array($vote_id)))
			db_vote::update_ballot_count_for_vote($vote_id);			
	}
}