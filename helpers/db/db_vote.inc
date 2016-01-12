<?php
class db_vote 
{
	public static function get_vote_id_from_prop_id ($prop_id)
	{
		$query = "select id from vote where from_proposition_id = ?";
		$values = Array($prop_id);
		return db::select_single_value($query, $values);
	}

	public static function make_vote_from_prop ($prop_id)
	{
		$prop_data = db_prop::get_prop_info($prop_id);
		$timestamp_delegate_ended = time() + STANDARD_VOTE_LENGTH / 2;
		$timestamp_ended = time() + STANDARD_VOTE_LENGTH;
		$query = "insert into vote (type, from_proposition_id, timestamp_created, timestamp_delegate_ended, timestamp_ended, constituency_id, title, description, forum_topic_id) values (?, ?, ?, ?, ?, ?, ?, ?, ?)";
		$values = Array($prop_data['type'], $prop_id, time(), $timestamp_delegate_ended, $timestamp_ended, $prop_data['constituency_id'], $prop_data['title'], $prop_data['description'], $prop_data['forum_topic_id']);
		$vote_id = db::insert($query, $values);
		if($vote_id){
			$query = "update proposition set status = 'affirmed', timestamp_ended = ? where id = ?";
			$values = Array(time(), $prop_id);
			db::update($query, $values);
			$post_title = _t("Vote: ", array('class' => 'noun')) . $prop_data['title'];
			$post_content = _t("This is an auto-generated forum thread for the vote: ") 
				. '<a href="index.php?type=vote&action=view_vote&id=' . $vote_id . '">' . $prop_data['title'] . "</a>\n\n" . $prop_data['description'];
			db_forum_admin::edit_title($post_title, $prop_data['forum_topic_id']);
			db_forum_admin::edit_content($post_content, $prop_data['forum_topic_id']);
		}
		return $vote_id;
	}

	public static function get_vote_info ($vote_id)
	{
		$query = "select v.id, v.title, v.description
			, p.created_by_voter as user_id
			, concat(initiator.first_name, ' ', initiator.last_name) as user_full_name
			, v.type, v.timestamp_created, v.timestamp_delegate_ended , v.timestamp_ended
			, v.forum_topic_id, c.id as constituency_id, c.title as constituency_name
			, c.number_of_voters, v.number_of_alternatives
			, v.number_of_ballots, v.number_of_direct_ballots
			, v.from_proposition_id, p.timestamp_created as proposition_created, v.status  
		from vote v
			join constituency c on c.id = constituency_id
			left join proposition p on p.id = v.from_proposition_id
			left join user initiator on initiator.id = p.created_by_voter
		where c.id = v.constituency_id and v.id = ?";
		$values = Array($vote_id);
		return db::select_single_row($query, $values);
	}

	public static function get_vote_ballots ($vote_id)
	{
		$query = "select b.user_code as user_code, va.alternative_title as alternative, b.delegate_id as delegate_id, 
		(select title from delegate d where d.id = b.delegate_id) as delegate_name 
			from ballot b, vote_alternative va 
			where b.vote_alternative_id = va.id and b.vote_id = ?";
		$values = Array($vote_id);
		return db::select($query, $values);
	}

	public static function insert_ballot ($vote_id, $ballot, $user_code, $voter_id = null, 
		$delegate_id = null, $delegation_level = null, $delegate_priority = null)
	{
		$constituency_id = db_constituency::get_vote_constituency_id($vote_id);
		if($user_code){
			$query = "delete from ballot where vote_id = ? and user_code = ?";
			$values = Array($vote_id, $user_code);
		}
		else{
			$query = "delete from ballot where vote_id = ? and voter_id = ?";
			$values = Array($vote_id, $delegate_id);
		}
		db::delete($query, $values);

		$query = "insert into ballot 
				(vote_id, constituency_id, ballot, user_code, voter_id, delegate_id, 
					delegation_level, delegate_priority, time_ballot_placed) 
				values (?, ?, ?, ?, ?, ?, ?, ?, ?)";
		$values = Array($vote_id, $constituency_id, $ballot, $user_code, $voter_id, $delegate_id, $delegation_level, $delegate_priority, time());
		$return = db::insert($query, $values);
		self::count_ballots_for_vote($vote_id);
		return $return;
	}

	public static function cancel_ballot ($vote_id, $user_code)
	{
		$query = "delete from ballot where vote_id = ? and user_code = ? and delegate_id is null";
		$values = Array($vote_id, $user_code);
		$result = db::delete($query, $values);
		db_delegate::find_and_insert_delegate_vote_for_user($user_code, null, $vote_id);
		self::count_ballots_for_vote($vote_id);
		return $result;
	}

	public static function remove_ballots($user_code, $voter_id, $delegate_id = null
		, $constituency_id = null, $vote_id = null) {
		$affected_vote_ids = array_unique(self::remove_ballots_no_recount($user_code, $voter_id, $delegate_id, $constituency_id, $vote_id));
		foreach ($affected_vote_ids as $id)
			self::count_ballots_for_vote($id);
		return true;
	}

	private static function remove_ballots_no_recount($user_code, $voter_id, $delegate_id = null
		, $constituency_id = null, $vote_id = null) {
		$values = array();
		$from_where = self::get_ballots_from_where_fragment($values, $user_code, $voter_id
			, $delegate_id, $constituency_id, $vote_id);
		$sel_query = "select b.user_code, b.voter_id, b.vote_id " . $from_where;
		$deleted_ballots = db::select($sel_query, $values);
		$affected_vote_ids = array();
		if ($deleted_ballots) {
			$del_query = "delete b " . $from_where;
			db::delete($del_query, $values);
			foreach ($deleted_ballots as $ballot) {
				if ($ballot['user_code'])
					$affected_votes[] = $ballot['vote_id'];
				else {
					$new_affected_vote_ids = self::remove_ballots_no_recount(null, null, $voter_id
						, $constituency_id, $ballot['vote_id']);
					$affected_vote_ids = array_merge($affected_vote_ids, $new_affected_vote_ids);
				}
			}
		}
		return $affected_vote_ids;
	}

	protected static function get_ballots_from_where_fragment(&$values, $user_code, $voter_id, $delegate_id = null, $constituency_id = null, $vote_id = null) {
		$from_where = "from ballot b
		join vote v on v.id = b.vote_id and status in ('active', 'del_ended', 'continuous')
		where ";
		$conditions = array();
		if ($user_code || $voter_id) {
			$conditions[] = "(b.user_code = ? OR b.voter_id = ?)";
			$values[] = $user_code;
			$values[] = $voter_id;
		}
		if ($delegate_id) {
			$conditions[] = "b.delegate_id = ?";
			$values[] = $delegate_id;
		}
		if ($constituency_id) {
			$conditions[] = "v.constituency_id = ?";
			$values[] = $constituency_id;
		}
		if ($vote_id) {
			$conditions[] = "v.id = ?";
			$values[] = $vote_id;
		}
		$from_where .= implode(" and ", $conditions);
		return $from_where;
	}

	public static function get_vote_alternative_from_title ($vote_id, $alternative_title)
	{
		$query = "select id from vote_alternative where vote_id = ? and alternative_title = ?";
		$values = Array($vote_id, $alternative_title);
		return db::select_single_value($query, $values);
	}

	public static function get_ballots ($vote_id)
	{
		$query = "select b.user_code as user_code, b.voter_id as voter_id, 
					(
						select d1.title from delegate d1 where b.voter_id = d1.id
					) as voter_is_delegate_name
					, b.ballot as ballot, b.delegate_id as delegate_id, 
					(
						select d2.title from delegate d2 where b.delegate_id = d2.id
					) as delegate_name
					, b.delegation_level as delegation_level, b.time_ballot_placed as time_ballot_placed 
					from ballot b 
					where b.vote_id = ?";
		$values = Array($vote_id);
		return db::select($query, $values);
	}

	public static function list_votes ($user_id, $sort, $page, $statuses)
	{
		$from_clause = self::get_votes_from_clause();
		$where_clause = self::get_votes_where_clause($statuses);
		$order_by = self::get_votes_order_by($sort);
		$limit_clause = db_general::get_limit_clause($page, LIST_ITEMS_PER_PAGE);
		$visible_columns = self::get_votes_visible_columns();
		$query = "select V.id, $visible_columns, C.title as constituency, V.from_proposition_id
					" . $from_clause . "
					" . $where_clause . "
					order by C.constituency_level asc, C.id, " . $order_by . " 
					" . $limit_clause;
		$values = array($user_id);
		return db::select($query, $values);
	}

	public static function search_votes ($search, $user_id, $sort, $page = 1)
	{
		$from_clause = self::get_votes_from_clause();
		$where_clause = self::get_search_votes_where_clause();
		$order_by = self::get_votes_order_by($sort);
		$limit_clause = db_general::get_limit_clause($page, LIST_ITEMS_PER_PAGE);
		$visible_columns = self::get_votes_visible_columns();
		$query = "select V.id, $visible_columns, C.title as constituency, V.from_proposition_id
					" . $from_clause . "
					" . $where_clause . "
					order by C.constituency_level asc, C.id, " . $order_by . " 
					" . $limit_clause;
		$values = Array($user_id, $search);
		return db::select($query, $values);
	}

	public static function search_votes_count ($search, $user_id)
	{
		$from_clause = self::get_votes_from_clause();
		$where_clause = self::get_search_votes_where_clause();
		$query = "select count(*) 
					" . $from_clause . "
					" . $where_clause;
		$values = array($user_id, $search);
		return db::select_single_value($query, $values);
	}

	private static function get_search_votes_where_clause() {
		return self::get_votes_where_clause() . "
			and match(V.title, V.description) against(? in boolean mode)";
	}

	private static function get_votes_visible_columns() 
	{
		return implode(", ", self::$votes_visible_columns);
	}

	private static function get_votes_order_by ($sort = 0)
	{
		return db_general::get_order_by(self::$votes_visible_columns, -3, $sort);
	}

	private static $votes_visible_columns =
		array("V.title", "V.type", "V.timestamp_created", "null as result", "V.number_of_ballots");

	public static function list_votes_count ($user_id, $statuses = null)
	{
		$from_clause = self::get_votes_from_clause();
		$where_clause = self::get_votes_where_clause($statuses);
		$query = "select count(*) 
					" . $from_clause . "
					" . $where_clause;
		$values = array($user_id);
		return db::select_single_value($query, $values);
	}

	private static function get_votes_from_clause ()
	{
		return "from vote V
					join constituency C on C.id = V.constituency_id
					join constituency_voter CV 
						on CV.constituency_id = C.id and CV.voter_id = ?";
	}

	private static function get_votes_where_clause ($statuses = null)
	{
		$where_clause = "where CV.voter_id IS NOT NULL";
		if (!empty($statuses)) 
			$where_clause .= " and V.status in ('" . implode("', '", $statuses) . "')";
		return $where_clause;
	}

	public static function get_ballot_from_delegate_or_user ($vote_id, $user_code, $delegand_id)
	{
		$query = "select id, ballot, delegate_id, time_ballot_placed, delegation_level, delegate_priority from ballot b where b.vote_id = ? and (b.user_code = ? or b.voter_id = ?)";
		$values = Array($vote_id, $user_code, $delegand_id);
		return db::select_single_row($query, $values);
	}

	public static function count_ballots_for_vote ($vote_id)
	{
		$query = "update vote 
				set number_of_ballots = 
				(
					select count(*) from ballot where vote_id = ? and user_code is not null
				)
				, number_of_direct_ballots = 
				(	
					select count(*) from ballot where vote_id = ? and user_code is not null and delegate_id is null
				) 
				where id = ?";
		$values = Array($vote_id, $vote_id, $vote_id);
		return db::update($query, $values);
	}

	public static function count_ballots_for_active_votes_for_constituency ($constituency_id)
	{
		$query = "update vote v 
					set number_of_ballots = 
					(
						select count(*) 
						from ballot b1 
						where b1.vote_id = v.id and user_code is not null
					)
					, number_of_direct_ballots = 
					(
						select count(*) 
						from ballot b2 
						where b2.vote_id = v.id and user_code is not null and delegate_id is null
					) 
					where (v.status = 'active' or v.status = 'del_ended' or v.status = 'continuous') 
						and v.constituency_id = ?";
		$values = Array($constituency_id);
		return db::update($query, $values);
	}

	public static function get_alternative_ids_from_vote_id ($vote_id)
	{
		$query = "select id from vote_alternative where vote_id = ? order by timestamp_added asc";
		$values = Array($vote_id);
		return db::select($query, $values);
	}

	public static function get_prio_vote_ballots ($vote_id)
	{
		$query = "select b.user_code as user_code, b.ballot as prio_ranking, b.delegate_id as delegate_id, 
					(select d.title from delegate d where b.delegate_id = d.id) as delegate_name 
					from ballot b 
					where user_code is not null and b.vote_id = ?";
		$values = Array($vote_id);
		return db::select($query, $values);
	}

	public static function get_prio_vote_ballots_without_extra_info ($vote_id)
	{
		$query = "select ballot as prio_ranking from ballot where user_code is not null and vote_id = ?";
		$values = Array($vote_id);
		return db::select($query, $values);
	}

	public static function add_alternative_by_voter ($vote_id, $title, $description, $voter_id)
	{
		$query = "insert into vote_alternative 
					(vote_id, added_by_voter, timestamp_added, alternative_title, alternative_description) 
					values (?, ?, ?, ?, ?)";
		$values = Array($vote_id, $voter_id, time(), general_helpers::clean($title), general_helpers::clean($description));
		$result =  db::insert($query, $values);
		self::update_number_of_alternatives($vote_id);
		return $result;
	}

	public static function add_candidate ($vote_id, $user_id, $description)
	{
		$query = "insert into vote_alternative 
			(vote_id, added_by_voter, timestamp_added, alternative_user_id, alternative_title, alternative_description) 
			values (?, ?, ?, ?, ?, ?)";
		$values = Array($vote_id, $user_id, time(), $user_id, 
			db_user::get_user_full_name($user_id), 
			general_helpers::clean($description));
		$result = db::insert($query, $values);
		self::update_number_of_alternatives($vote_id);
		return $result;
	}

	public static function remove_candidate ($vote_id, $user_id)
	{
		$query = "delete from vote_alternative where vote_id = ? and alternative_user_id = ?";
		$values = Array($vote_id, $user_id);
		$result = db::delete($query, $values);
		self::update_number_of_alternatives($vote_id);
		return $result;
	}

	public static function update_number_of_alternatives ($vote_id)
	{
		$query = "update vote v set number_of_alternatives = (select count(*) 
			from vote_alternative va where va.vote_id = v.id) 
			where v.id = ?";
		$values = Array($vote_id);
		return db::update($query, $values);
	}

	public static function get_alternatives_for_vote ($vote_id)
	{
		$query = "select id, alternative_title as title, alternative_description as description from vote_alternative where vote_id = ? order by timestamp_added asc";
		$values = Array($vote_id);
		return db::select($query, $values);
	}

	public static function get_candidates_for_vote ($vote_id)
	{
		$query = "select id, alternative_user_id as user_id, alternative_title as user_name, 
			alternative_title as title, alternative_description as description 
			from vote_alternative 
			where vote_id = ? order by timestamp_added asc";
		$values = Array($vote_id);
		return db::select($query, $values);
	}

	public static function get_alternative_info ($alternative_id)
	{
		$query = "select * from vote_alternative where id = ?";
		$values = Array($alternative_id);
		return db::select_single_row($query, $values);
	}

	public static function get_alternative_title ($alternative_id)
	{
		$query = "select alternative_title as title from vote_alternative where id = ?";
		$values = Array($alternative_id);
		return db::select_single_value($query, $values);
	}

	public static function get_alternative_candidate_info ($alternative_id)
	{
		$query = "select alternative_user_id as user_id, alternative_title as user_name from vote_alternative where id = ?";
		$values = Array($alternative_id);
		return db::select_single_row($query, $values);
	}

	public static function get_alternative_user_id ($alternative_id)
	{
		$query = "select alternative_user_id as user_id from vote_alternative where id = ?";
		$values = Array($alternative_id);
		return db::select_single_value($query, $values);
	}

	public static function is_user_candidate_in_vote ($user_id, $vote_id)
	{
		$query = "select id from vote_alternative where alternative_user_id = ? and vote_id = ?";
		$values = Array($user_id, $vote_id);
		$result =  db::select_single_value($query, $values);
		return !empty($result);
	}

	public static function get_vote_type_from_id ($vote_id)
	{
		$query = "select type from vote where id = ?";
		$values = Array($vote_id);
		return db::select_single_value($query, $values);
	}

	public static function get_constituency_id_for_vote ($vote_id)
	{
		$query = "select constituency_id from vote where id = ?";
		$values = Array($vote_id);
		return db::select_single_value($query, $values);
	}

	public static function get_timestamp_added_for_alternative ($alternative_id)
	{
		$query = "select timestamp_added from vote_alternative where id = ?";
		$values = Array($alternative_id);
		return db::select_single_value($query, $values);
	}
}