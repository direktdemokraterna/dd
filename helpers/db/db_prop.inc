<?php

class db_prop 
{
	public static function add_prop ($type, $created_by_voter, $constituency_id, $title, $description)
	{
		$forum_id = db_constituency::get_constituency_forum_id($constituency_id);
		$post_title = _t("Proposition: ") . $title;
		$forum_topic_id = db_forum::new_topic($created_by_voter, $forum_id, $post_title);
		$query = "insert into proposition (type, created_by_voter, timestamp_created, constituency_id, title, description, forum_topic_id) values (?, ?, ?, ?, ?, ?, ?)";
		$values = Array($type, $created_by_voter, time(), $constituency_id, $title, $description, $forum_topic_id);
		$prop_id = db::insert($query, $values);
		$post_content = _t("This is an auto-generated forum thread for the proposition: ")
			. '<a href="index.php?type=vote&action=view_prop&id=' . $prop_id . '">' . $title . '</a>\n\n' . $description;
		db_forum::add_content_to_post($forum_topic_id, $post_content);
		return $prop_id;
	}

	public static function get_prop_info ($prop_id)
	{
		$query = "select p.id as prop_id, p.title, p.description, u.id as user_id
		, concat(u.first_name, ' ', u.last_name) as user_full_name, p.type, p.timestamp_created
		, p.number_of_supporters, p.status
		, p.forum_topic_id, c.id as constituency_id, c.title as constituency_name
		, c.number_of_voters 
			from proposition p, user u, constituency c 
			where u.id = p.created_by_voter and c.id = p.constituency_id and p.id = ?";
		$values = Array($prop_id);
		return db::select_single_row($query, $values);
	}

	public static function get_number_of_ballots ($prop_id)
	{
		$query = "select 
				(
					select count(*) 
					from proposition_support 
					where proposition_id = ? and user_code is not null
				) as total_number_of_ballots
				, (
					select count(*) 
					from proposition_support 
					where proposition_id = ? and user_code is not null and delegate_id is null
				) as number_of_direct_ballots
				, (
					select count(*) 
					from proposition_support 
					where proposition_id = ? and user_code is null
				) as number_of_delegate_ballots";
		$values = Array($prop_id, $prop_id, $prop_id);
		return db::select_single_row($query, $values);
	}

	public static function get_prop_status ($prop_id)
	{
		$query = "select status from proposition p where id = ?";
		$values = Array($prop_id);
		return db::select_single_value($query, $values);
	}

	public static function get_prop_supporters ($prop_id)
	{
		$query = "select ps.user_code, ps.voter_id
			, (select d1.title from delegate d1 where ps.voter_id = d1.id) as voter_is_delegate_name
			, ps.support, ps.delegate_id
			, (select d2.title from delegate d2 where ps.delegate_id = d2.id) as delegate_name
			, time_ballot_placed 
		from proposition_support ps 
		where ps.proposition_id = ?";
		$values = Array($prop_id);
		return db::select($query, $values);
	}

	public static function list_props ($status, $user_id, $sort, $page = 1)
	{
		$where_clause = self::get_props_where_clause($status);
		$from_clause = self::get_props_from_clause($user_id);
		$order_by = self::get_props_order_by(null, $sort);
		$limit_clause = db_general::get_limit_clause($page, LIST_ITEMS_PER_PAGE);
		$visible_columns = self::get_props_visible_columns();
		$query = "select id, $visible_columns, constituency 
					from (select P.*, C.title as constituency, C.constituency_level " 
						. $from_clause . "
					" . $where_clause . "
					order by (now() - timestamp_created)/(1+ln(1 + number_of_supporters))
					limit " . MAX_ACTIVE_PROPOSITION_COUNT . ") T
					order by constituency_level asc, constituency_id, " . $order_by . "
					" . $limit_clause;
		$values = Array();
		return db::select($query, $values);
	}

	public static function list_props_count ($status, $user_id)
	{
		$where_clause = self::get_props_where_clause($status);
		$from_clause = self::get_props_from_clause($user_id);
		$query = "select count(*) 
					" . $from_clause . "
					" . $where_clause;
		$values = Array();
		return min(db::select_single_value($query, $values), MAX_ACTIVE_PROPOSITION_COUNT);
	}

	public static function search_props ($search, $user_id, $sort, $page = 1)
	{
		$from_clause = self::get_props_from_clause($user_id);
		$where_clause = self::get_props_where_clause('pending') . "
					and match(P.title, P.description) against(? in boolean mode)";
		$order_by = self::get_props_order_by("P", $sort);
		$limit_clause = db_general::get_limit_clause($page, LIST_ITEMS_PER_PAGE);
		$visible_columns = self::get_props_visible_columns("P");
		$query = "select P.id, $visible_columns, C.title as constituency 
					" . $from_clause . "
					" . $where_clause . "
					order by C.constituency_level asc, C.id, " . $order_by . " 
					" . $limit_clause;
		$values = Array($search);
		return db::select($query, $values);
	}

	public static function search_props_count ($search, $user_id, $page = 1)
	{
		$from_clause = self::get_props_from_clause($user_id);
		$where_clause = self::get_props_where_clause('pending') . "
					and match(P.title, P.description) against(? in boolean mode)";
		$query = "select count(*) 
					" . $from_clause . "
					" . $where_clause;
		$values = Array($search);
		return db::select_single_value($query, $values);
	}

	private static function get_props_visible_columns($qualifier = null) 
	{
		return implode(", ", self::get_qualified_visible_columns($qualifier));
	}

	public static function get_props_order_by ($qualifier = null, $sort = 0)
	{
		$retval = db_general::get_order_by(self::get_qualified_visible_columns($qualifier), 1, $sort);
		return $retval;
	}

	private static function get_qualified_visible_columns($qualifier = null) 
	{
		return $qualifier 
			? array_map(function($col) use ($qualifier) 
				{ return "$qualifier." . $col;}
				, self::$props_visible_columns)
			: self::$props_visible_columns;
	}

	private static $props_visible_columns =
		array("title", "timestamp_created", "number_of_supporters");

	private static function get_props_from_clause ($user_id)
	{
		return "from proposition P
					join constituency C on C.id = P.constituency_id
					left join constituency_voter cv 
						on cv.constituency_id = C.id and cv.voter_id = " . $user_id;
	}

	private static function get_props_where_clause ($status)
	{
		$where_clause = "where cv.voter_id IS NOT NULL and P.status = '" . $status . "'";
		return $where_clause;
	}

	public static function register_prop_ballot ($prop_id, $user_code, $support)
	{
		$query = "select count(*) from proposition_support where proposition_id = ? and user_code = ?";
		$values = Array($prop_id, $user_code);
		$ballot_already_present = db::select_single_value($query, $values);
		if($ballot_already_present){
			$query = "update proposition_support 
						set support = ?, delegate_id = null, time_ballot_placed = ? 
						where proposition_id = ? and user_code = ?";
			$values = Array($support, time(), $prop_id, $user_code);
			$ok = db::update($query, $values);
		}
		else{
			$constituency_id = db_constituency::get_prop_constituency_id($prop_id);
			$query = "insert into proposition_support 
						(proposition_id, constituency_id, user_code, support, time_ballot_placed) 
						values (?, ?, ?, ?, ?)";
			$values = Array($prop_id, $constituency_id, $user_code, $support, time());
			$ok = db::insert($query, $values);
		}
		self::count_prop_support($prop_id);
		return $ok >= 0;
	}

	public static function remove_prop_ballots($user_code, $voter_id, $delegate_id = null
		, $constituency_id = null, $prop_id = null) {
		$affected_prop_ids = array_unique(self::remove_prop_ballots_no_recount($user_code, $voter_id, $delegate_id, $constituency_id, $prop_id));
		foreach ($affected_prop_ids as $id)
			self::count_prop_support($id);
		return true;
	}

	private static function remove_prop_ballots_no_recount($user_code, $voter_id, $delegate_id = null
		, $constituency_id = null, $prop_id = null) {
		$values = array();
		$from_where = self::get_prop_ballots_from_where_fragment($values, $user_code, $voter_id
			, $delegate_id, $constituency_id, $prop_id);
		$sel_query = "select ps.user_code, ps.voter_id, ps.proposition_id " . $from_where;
		$deleted_prop_ballots = db::select($sel_query, $values);
		$affected_prop_ids = array();
		if ($deleted_prop_ballots) {
			$del_query = "delete " . $from_where;
			db::delete($del_query, $values);
			foreach ($deleted_prop_ballots as $prop_ballot) {
				if ($prop_ballot['user_code'])
					$affected_prop_ids[] = $ballot['proposition_id'];
				else {
					$new_affected_prop_ids = self::remove_prop_ballots_no_recount(null, null, $voter_id
						, $constituency_id, $ballot['proposition_id']);
					$affected_prop_ids = array_merge($affected_prop_ids, $new_affected_prop_ids);
				}
			}
		}
		return $affected_prop_ids;
	}

	private static function get_prop_ballots_from_where_fragment(&$values, $user_code, $voter_id, $delegate_id = null, $constituency_id = null, $prop_id = null) {
		$from_where = "from proposition_support ps
		join proposition p on p.id = ps.proposition_id and status = 'pending'
		where ";
		$conditions = array();
		if ($user_code || $voter_id) {
			$conditions[] .= "(ps.user_code = ? OR ps.voter_id = ?)";
			$values[] = $user_code;
			$values[] = $voter_id;
		}
		if ($delegate_id) {
			$conditions[] = "ps.delegate_id = ?";
			$values[] = $delegate_id;
		}
		if ($constituency_id) {
			$conditions[] = "p.constituency_id = ?";
			$values[] = $constituency_id;
		}
		if ($prop_id) {
			$conditions[] = "p.id = ?";
			$values[] = $prop_id;
		}
		$from_where .= implode(" and ", $conditions);
		return $from_where;
	}

	public static function cancel_ballot ($prop_id, $user_code)
	{
		$query = "delete from proposition_support where proposition_id = ? and user_code = ? and delegate_id is null";
		$values = Array($prop_id, $user_code);
		$return = db::delete($query, $values);
		self::count_prop_support($prop_id);
		return $return;
	}

	public static function count_prop_support ($prop_id)
	{
		$query = "update proposition set number_of_supporters = 
				(
					select count(*) 
					from proposition_support 
					where proposition_id = ? and support = 1 and user_code is not null
				)
				where id = ?";
		$values = Array($prop_id, $prop_id);
		$ok = db::update($query, $values);
		$prop_info = self::get_prop_info($prop_id);
		if($prop_info['number_of_supporters'] >= ceil($prop_info['number_of_voters'] * PROP_TO_VOTE_SUPPORT))
			db_vote::make_vote_from_prop($prop_id);
		return $ok;
	}

	public static function get_old_props ()
	{
		$query = "select id from proposition where timestamp_created > ?";
		$values = Array(time() - PROP_REMOVAL_TIME);
		return db::select($query, $values);
	}

	public static function get_prop_ballot_from_delegate_or_user ($prop_id, $user_code, $delegand_id)
	{
		$query = "select id, support, delegate_id, time_ballot_placed, delegation_level, delegate_priority from proposition_support where proposition_id = ? and (user_code = ? or voter_id = ?)";
		$values = Array($prop_id, $user_code, $delegand_id);
		return db::select_single_row($query, $values);
	}
}