<?php

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

		$vote_id = db::insert($query, $values);

		if($vote_id){
			$query = "update propositions set status = 'affirmed', timestamp_ended = ? where id = ?";
			$values = Array(time(), $prop_id);

			db::update($query, $values);

			$post_title = "Omröstning: " . $prop_data['title'];
			$post_content = "Det här är en automatiskt skapad forumtråd tillhörande omröstningen: <a href=\"index.php?type=vote&action=view_vote&id=" . $vote_id . "\">" . $prop_data['title'] . "</a>\n\n" . $prop_data['description'];

			db_forum_admin::edit_title($post_title, $prop_data['forum_topic_id']);
			db_forum_admin::edit_content($post_content, $prop_data['forum_topic_id']);
		}

		return $vote_id;

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

	public static function insert_ballot ($vote_id, $ballot, $user_code, $voter_is_delegate_id = null, $delegate_id = null, $delegation_level = null, $delegate_priority = null){

		$constituency_id = db_constituency::get_vote_constituency_id($vote_id);

		if($user_code){
			$query = "delete from ballots where vote_id = ? and user_code = ?";
			$values = Array($vote_id, $user_code);
		}
		else{
			$query = "delete from ballots where vote_id = ? and voter_is_delegate_id = ?";
			$values = Array($vote_id, $delegate_id);
		}

		db::delete($query, $values);


		$query = "insert into ballots (vote_id, constituency_id, ballot, user_code, voter_is_delegate_id, delegate_id, delegation_level, delegate_priority, time_ballot_placed) values (?, ?, ?, ?, ?, ?, ?, ?, ?)";
		$values = Array($vote_id, $constituency_id, $ballot, $user_code, $voter_is_delegate_id, $delegate_id, $delegation_level, $delegate_priority, time());

		$return = db::insert($query, $values);

		self::count_ballots_for_vote($vote_id);

		return $return;

	}

	public static function cancel_ballot ($vote_id, $user_code){

		$query = "delete from ballots where vote_id = ? and user_code = ? and delegate_id is null";
		$values = Array($vote_id, $user_code);

		$return = db::delete($query, $values);

		self::count_ballots_for_vote($vote_id);

		return true;

	}

	public static function get_vote_alternative_from_title ($vote_id, $alternative_title){

		$query = "select id from votes_alternatives where vote_id = ? and alternative_title = ?";
		$values = Array($vote_id, $alternative_title);

		return db::select_single_value($query, $values);

	}

	public static function get_ballots ($vote_id){

		$query = "select b.user_code as user_code, b.voter_is_delegate_id as voter_is_delegate_id, (select d1.title from delegates d1 where b.voter_is_delegate_id = d1.id) as voter_is_delegate_name, b.ballot as ballot, b.delegate_id as delegate_id, 
					(select d2.title from delegates d2 where b.delegate_id = d2.id) as delegate_name, b.delegation_level as delegation_level, b.time_ballot_placed as time_ballot_placed 
					from ballots b 
					where b.vote_id = ?";
		$values = Array($vote_id);

		return db::select($query, $values);

	}

	// NOTE: This db function does not utilise full parametrised input due to bug in current MySQL that doesn't allow parametrised input in limit clause. Variables are instead sanitised by casting as int. When this bug is resolved, this function can be corrected. 
	public static function list_active_votes ($sort, $page = 1)
	{
		$where_clause = self::get_votes_where_clause("V.");
		$order_by = self::get_votes_order_by($sort);
		$row_offset = (int)($page-1) * LIST_ITEMS_PER_PAGE;
		$query = "select V.id, V.title, C.title as constituency 
					from votes V
					join constituencies C on C.id = V.constituency_id 
					" . $where_clause . "
					order by C.constituency_level asc, C.id, " . $order_by . " 
					limit " . $row_offset . ", " . LIST_ITEMS_PER_PAGE;
		$values = Array();
		return db::select($query, $values);
	}

	public static function get_votes_order_by ($sort)
	{
		return $sort === "alphabetic" ? "V.title asc" : "V.timestamp_created desc";
	}

	public static function list_active_votes_count ()
	{
		$query = "select count(*) from votes " . self::get_votes_where_clause();
		$values = Array();
		return db::select_single_value($query, $values);
	}

	private static function get_votes_where_clause ($prefix = '')
	{
		return "where " . $prefix . "status in ('active', 'del_ended', 'continuous')";
	}

	public static function list_old_votes ($page = 1, $limit = LIST_ITEMS_PER_PAGE, $order_by = "timestamp_created desc", $where_filter = "1=1"){
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

	public static function get_ballot_from_delegate_or_user ($vote_id, $user_code, $delegand_id){

		$query = "select id, ballot, delegate_id, time_ballot_placed, delegation_level, delegate_priority from ballots b where b.vote_id = ? and (b.user_code = ? or b.voter_is_delegate_id = ?)";
		$values = Array($vote_id, $user_code, $delegand_id);

		return db::select_single_row($query, $values);

	}

	public static function count_ballots_for_vote ($vote_id){

		$query = "update votes set number_of_ballots = (select count(*) from ballots where vote_id = ? and user_code is not null), number_of_direct_ballots = (select count(*) from ballots where vote_id = ? and user_code is not null and delegate_id is null) where id = ?";
		$values = Array($vote_id, $vote_id, $vote_id);

		return db::update($query, $values);

	}

	public static function count_ballots_for_active_votes_for_constituency ($constituency_id){

		$query = "update votes v set number_of_ballots = (select count(*) from ballots b1 where b1.vote_id = v.id and user_code is not null), number_of_direct_ballots = (select count(*) from ballots b2 where b2.vote_id = v.id and user_code is not null and delegate_id is null) where (v.status = 'active' or v.status = 'del_ended' or v.status = 'continuous') and v.constituency_id = ?";
		$values = Array($constituency_id);

		return db::update($query, $values);

	}

	public static function get_alternative_ids_from_vote_id ($vote_id){

		$query = "select id from votes_alternatives where vote_id = ? order by timestamp_added asc";
		$values = Array($vote_id);

		return db::select($query, $values);

	}

	public static function get_prio_vote_ballots ($vote_id){

		$query = "select b.user_code as user_code, b.ballot as prio_ranking, b.delegate_id as delegate_id, 
					(select d.title from delegates d where b.delegate_id = d.id) as delegate_name 
					from ballots b 
					where user_code is not null and b.vote_id = ?";
		$values = Array($vote_id);

		return db::select($query, $values);

	}

	public static function get_prio_vote_ballots_without_extra_info ($vote_id){

		$query = "select ballot as prio_ranking from ballots where user_code is not null and vote_id = ?";
		$values = Array($vote_id);

		return db::select($query, $values);

	}

	public static function add_alternative_by_user ($vote_id, $title, $description, $user_id){

		$query = "insert into votes_alternatives (vote_id, added_by_user, timestamp_added, alternative_title, alternative_description) values (?, ?, ?, ?, ?)";
		$values = Array($vote_id, $user_id, time(), general_helpers::clean($title), general_helpers::clean($description));

		$return =  db::insert($query, $values);

		self::update_number_of_alternatives($vote_id);

		return $return;

	}

	public static function add_alternative_by_delegate ($vote_id, $title, $description, $delegate_id){

		$query = "insert into votes_alternatives (vote_id, added_by_delegate, timestamp_added, alternative_title, alternative_description) values (?, ?, ?, ?, ?)";
		$values = Array($vote_id, $delegate_id, time(), general_helpers::clean($title), general_helpers::clean($description));

		$return =  db::insert($query, $values);

		self::update_number_of_alternatives($vote_id);

		return $return;

	}

	public static function add_candidate ($vote_id, $user_id, $description){

		$query = "insert into votes_alternatives (vote_id, added_by_user, timestamp_added, alternative_user_id, alternative_title, alternative_description) values (?, ?, ?, ?, ?, ?)";
		$values = Array($vote_id, $user_id, time(), $user_id, db_user::get_user_full_name($user_id), general_helpers::clean($description));

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

	public static function get_alternative_user_id ($alternative_id){

		$query = "select alternative_user_id as user_id from votes_alternatives where id = ?";
		$values = Array($alternative_id);

		return db::select_single_value($query, $values);

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

	public static function get_constituency_id_for_vote ($vote_id){

		$query = "select constituency_id from votes where id = ?";
		$values = Array($vote_id);

		return db::select_single_value($query, $values);

	}

	public static function get_timestamp_added_for_alternative ($alternative_id){

		$query = "select timestamp_added from votes_alternatives where id = ?";
		$values = Array($alternative_id);

		return db::select_single_value($query, $values);

	}

}