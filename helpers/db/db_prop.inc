<?php

class db_prop 
{
	public static function add_prop ($type, $created_by_user, $created_by_delegate, $constituency_id, $title, $description)
	{
		$forum_id = db_constituency::get_constituency_forum_id($constituency_id);
		$post_title = "Proposition: " . $title;
		$forum_topic_id = db_forum::new_topic($created_by_user, $forum_id, $post_title);
		$query = "insert into proposition (type, created_by_user, created_by_delegate, timestamp_created, constituency_id, title, description, forum_topic_id) values (?, ?, ?, ?, ?, ?, ?, ?)";
		$values = Array($type, $created_by_user, $created_by_delegate, time(), $constituency_id, $title, $description, $forum_topic_id);
		$prop_id = db::insert($query, $values);
		$post_content = "Det här är en automatiskt skapad forumtråd tillhörande propositionen: <a href=\"index.php?type=vote&action=view_prop&id=" . $prop_id . "\">" . $title . "</a>\n\n" . $description;
		db_forum::add_content_to_post($forum_topic_id, $post_content);
		return $prop_id;
	}

	public static function get_prop_info ($prop_id)
	{
		$query = "select p.id as prop_id, p.title as title, p.description as description, u.id as user_id
		, concat(u.first_name, ' ', u.last_name) as user_full_name, p.type as type, p.timestamp_created as timestamp_created
		, p.number_of_supporters as number_of_supporters, p.number_of_abstains as number_of_abstains, p.status as status
		, p.forum_topic_id as forum_topic_id, c.id as constituency_id, c.title as constituency_name
		, c.number_of_voters as number_of_voters 
			from proposition p, user u, constituency c 
			where u.id = p.created_by_user and c.id = p.constituency_id and p.id = ?";
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
		$query = "select ps.user_code as user_code, ps.voter_is_delegate_id as voter_is_delegate_id
			, (	select d1.title from delegate d1 where ps.voter_is_delegate_id = d1.id ) as voter_is_delegate_name
			, ps.support_type as support_type, ps.delegate_id as delegate_id
			, ( select d2.title from delegate d2 where ps.delegate_id = d2.id ) as delegate_name
			, time_ballot_placed as time_ballot_placed 
		from proposition_support ps 
		where ps.proposition_id = ?";
		$values = Array($prop_id);
		return db::select($query, $values);
	}

	public static function list_props ($statuses, $user_id, $sort, $page)
	{
		$where_clause = self::get_props_where_clause($statuses);
		$from_clause = self::get_props_from_clause($user_id);
		$order_by = self::get_props_order_by($sort);
		$row_offset = (int)($page-1) * LIST_ITEMS_PER_PAGE;
		$query = "select P.id, P.title, C.title as constituency 
					" . $from_clause . "
					" . $where_clause . "
					order by C.constituency_level asc, C.id, " . $order_by . " 
					limit " . $row_offset . ", " . LIST_ITEMS_PER_PAGE;
		$values = Array();
		return db::select($query, $values);
	}

	public static function get_props_order_by ($sort)
	{
		return $sort === "alphabetic" ? "P.title asc" : "P.timestamp_created desc";
	}

	public static function list_props_count ($statuses, $user_id)
	{
		$where_clause = self::get_props_where_clause($statuses);
		$from_clause = self::get_props_from_clause($user_id);
		$query = "select count(*) 
					" . $from_clause . "
					" . $where_clause;
		$values = Array();
		return db::select_single_value($query, $values);
	}

	private static function get_props_from_clause ($user_id)
	{
		return "from proposition P
					join constituency C on C.id = P.constituency_id
					left join constituency_user CU 
						on CU.constituency_id = C.id and CU.user_id = " . $user_id;
	}

	private static function get_props_where_clause ($statuses)
	{
		$where_clause = "where CU.id IS NOT NULL";
		if (!empty($statuses))
			$where_clause .= " and P.status in ('" . implode("', '", $statuses) . "')";
		return $where_clause;
	}

	public static function register_prop_ballot ($prop_id, $user_code, $support_type)
	{
		$query = "select count(*) from proposition_support where proposition_id = ? and user_code = ?";
		$values = Array($prop_id, $user_code);
		$ballot_already_present = db::select_single_value($query, $values);
		if($ballot_already_present){
			$query = "update proposition_support 
						set support_type = ?, delegate_id = null, time_ballot_placed = ? 
						where proposition_id = ? and user_code = ?";
			$values = Array($support_type, time(), $prop_id, $user_code);
			$ok = db::update($query, $values);
		}
		else{
			$constituency_id = db_constituency::get_prop_constituency_id($prop_id);
			$query = "insert into proposition_support 
						(proposition_id, constituency_id, user_code, support_type, time_ballot_placed) 
						values (?, ?, ?, ?, ?)";
			$values = Array($prop_id, $constituency_id, $user_code, $support_type, time());
			$ok = db::insert($query, $values);
		}
		self::count_prop_support($prop_id);
		return $ok >= 0;
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
					where proposition_id = ? and support_type = 'support' and user_code is not null
				)
				, number_of_abstains = 
				(
					select count(*) 
					from proposition_support 
					where proposition_id = ? and support_type = 'abstain' and user_code is not null
				) 
				where id = ?";
		$values = Array($prop_id, $prop_id, $prop_id);
		$ok = db::update($query, $values);
		$prop_info = self::get_prop_info($prop_id);
		if($prop_info['number_of_supporters'] >= ceil($prop_info['number_of_voters'] * PROP_TO_VOTE_SUPPORT))
			db_vote::make_vote_from_prop($prop_id);
		return $ok;
	}

	public static function reject_prop ($prop_id)
	{
		$query = "update proposition set status = 'rejected', timestamp_ended = ? where id = ?";
		$values = Array(time(), $prop_id);
		return db::update($query, $values);
	}

	public static function get_old_props ()
	{
		$query = "select id from proposition where timestamp_created > ?";
		$values = Array(time() - PROP_REMOVAL_TIME);
		return db::select($query, $values);
	}

	public static function get_prop_ballot_from_delegate_or_user ($prop_id, $user_code, $delegand_id)
	{
		$query = "select id, support_type, delegate_id, time_ballot_placed, delegation_level, delegate_priority from proposition_support where proposition_id = ? and (user_code = ? or voter_is_delegate_id = ?)";
		$values = Array($prop_id, $user_code, $delegand_id);
		return db::select_single_row($query, $values);
	}
}