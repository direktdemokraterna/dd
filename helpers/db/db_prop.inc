<?php

class db_prop {

	public static function add_prop ($type, $created_by_user, $created_by_delegate, $constituency_id, $title, $description){

		$forum_id = db_constituency::get_constituency_forum_id($constituency_id);

		$post_title = "Proposition: " . $title;

		$forum_topic_id = db_forum::new_topic($created_by_user, $forum_id, $post_title);

		$query = "insert into propositions (type, created_by_user, created_by_delegate, timestamp_created, constituency_id, title, description, forum_topic_id) values (?, ?, ?, ?, ?, ?, ?, ?)";
		$values = Array($type, $created_by_user, $created_by_delegate, time(), $constituency_id, $title, $description, $forum_topic_id);

		$prop_id = db::insert($query, $values);

		$post_content = "Det här är en automatiskt skapad forumtråd tillhörande propositionen: <a href=\"index.php?type=vote&action=view_prop&id=" . $prop_id . "\">" . $title . "</a>\n\n" . $description;
		db_forum::add_content_to_post($forum_topic_id, $post_content);

		return $prop_id;

	}

	public static function get_prop_info ($prop_id){

		$query = "select p.id as prop_id, p.title as title, p.description as description, u.id as user_id, concat(u.first_name, ' ', u.last_name) as user_full_name, p.type as type, p.timestamp_created as timestamp_created, p.number_of_supporters as number_of_supporters, p.number_of_abstains as number_of_abstains, p.status as status, p.forum_topic_id as forum_topic_id, c.id as constituency_id, c.title as constituency_name, c.number_of_voters as number_of_voters 
			from propositions p, users u, constituencies c 
			where u.id = p.created_by_user and c.id = p.constituency_id and p.id = ?";
		$values = Array($prop_id);

		return db::select_single_row($query, $values);

	}

	public static function get_number_of_ballots ($prop_id){

		$query = "select (select count(*) from propositions_support where proposition_id = ? and user_code is not null) as total_number_of_ballots, (select count(*) from propositions_support where proposition_id = ? and user_code is not null and delegate_id is null) as number_of_direct_ballots, (select count(*) from propositions_support where proposition_id = ? and user_code is null) as number_of_delegate_ballots";
		$values = Array($prop_id, $prop_id, $prop_id);

		return db::select_single_row($query, $values);

	}

	public static function get_prop_status ($prop_id){

		$query = "select status from propositions p where id = ?";
		$values = Array($prop_id);

		return db::select_single_value($query, $values);

	}

	public static function get_prop_supporters ($prop_id){

		$query = "select ps.user_code as user_code, ps.voter_is_delegate_id as voter_is_delegate_id, (select d1.title from delegates d1 where ps.voter_is_delegate_id = d1.id) as voter_is_delegate_name, ps.support_type as support_type, ps.delegate_id as delegate_id, 
					(select d2.title from delegates d2 where ps.delegate_id = d2.id) as delegate_name, time_ballot_placed as time_ballot_placed 
					from propositions_support ps 
					where ps.proposition_id = ?";
		$values = Array($prop_id);

		return db::select($query, $values);

	}

	public static function list_active_props ($sort, $page = 1)
	{
		$where_clause = self::get_props_where_clause("P.");
		$order_by = self::get_props_order_by($sort);
		$row_offset = (int)($page-1) * LIST_ITEMS_PER_PAGE;
		$query = "select P.id, P.title, C.title as constituency 
					from propositions P
					join constituencies C on C.id = P.constituency_id 
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

	public static function list_active_props_count ()
	{
		$query = "select count(*) from propositions " . self::get_props_where_clause();
		$values = Array();
		return db::select_single_value($query, $values);
	}

	private static function get_props_where_clause ($prefix = '')
	{
		return "where " . $prefix . "status = 'pending'";
	}

	public static function register_prop_ballot ($prop_id, $user_code, $support_type){

		$query = "select count(*) from propositions_support where proposition_id = ? and user_code = ?";
		$values = Array($prop_id, $user_code);

		$ballot_already_present = db::select_single_value($query, $values);

		if($ballot_already_present){
			$query = "update propositions_support set support_type = ?, delegate_id = null, time_ballot_placed = ? where proposition_id = ? and user_code = ?";
			$values = Array($support_type, time(), $prop_id, $user_code);

			$ok = db::update($query, $values);
		}
		else{
			$constituency_id = db_constituency::get_prop_constituency_id($prop_id);

			$query = "insert into propositions_support (proposition_id, constituency_id, user_code, support_type, time_ballot_placed) values (?, ?, ?, ?, ?)";
			$values = Array($prop_id, $constituency_id, $user_code, $support_type, time());

			$ok = db::insert($query, $values);
		}

		self::count_prop_support($prop_id);

		if($ok >= 0){
			return true;
		}
		else{
			return false;
		}

	}

	public static function cancel_ballot ($prop_id, $user_code){

		$query = "delete from propositions_support where proposition_id = ? and user_code = ? and delegate_id is null";
		$values = Array($prop_id, $user_code);

		$return = db::delete($query, $values);

		self::count_prop_support($prop_id);

		return $return;

	}

	public static function count_prop_support ($prop_id){

		$query = "update propositions set number_of_supporters = (select count(*) from propositions_support where proposition_id = ? and support_type = 'support' and user_code is not null), number_of_abstains = (select count(*) from propositions_support where proposition_id = ? and support_type = 'abstain' and user_code is not null) where id = ?";
		$values = Array($prop_id, $prop_id, $prop_id);

		$ok = db::update($query, $values);

		$prop_info = self::get_prop_info($prop_id);

		if($prop_info['number_of_supporters'] >= ceil($prop_info['number_of_voters'] * PROP_TO_VOTE_SUPPORT)){
			db_vote::make_vote_from_prop($prop_id);
		}
//		elseif($prop_info['number_of_abstains'] > $prop_info['number_of_supporters']){
//			self::reject_prop($prop_id);
//		}

		return $ok;

	}

	public static function reject_prop ($prop_id){

		$query = "update propositions set status = 'rejected', timestamp_ended = ? where id = ?";
		$values = Array(time(), $prop_id);

		return db::update($query, $values);

	}

	public static function list_old_props ($page = 1, $limit = LIST_ITEMS_PER_PAGE, $order_by = "created_by_user desc", $where_filter = "1=1"){
// NOTE: This db function does not utilise full parametrised input due to bug in current MySQL that doesn't allow parametrised input in limit clause. Variables are instead sanitised by casting as int. When this bug is resolved, this function can be corrected. 

		$page = (int)($page-1) * $limit;
		$limit = (int)$limit;

		$query = "select id, title, status from propositions where " . $where_filter . " and (status = 'rejected' or status = 'affirmed') order by " . $order_by . " limit " . $page . ", " . $limit;
		$values = Array();

		return db::select($query, $values);

	}

	public static function list_old_props_count ($where_filter = "1=1"){

		$query = "select count(*) from propositions where " . $where_filter . " and (status = 'rejected' or status = 'affirmed')";
		$values = Array();

		return db::select_single_value($query, $values);

	}

	public static function get_old_props (){

		$query = "select id from propositions where timestamp_created > ?";
		$values = Array(time() - PROP_REMOVAL_TIME);

		return db::select($query, $values);

	}

	public static function get_prop_ballot_from_delegate_or_user ($prop_id, $user_code, $delegand_id){

		$query = "select id, support_type, delegate_id, time_ballot_placed, delegation_level, delegate_priority from propositions_support where proposition_id = ? and (user_code = ? or voter_is_delegate_id = ?)";
		$values = Array($prop_id, $user_code, $delegand_id);

		return db::select_single_row($query, $values);

	}

}