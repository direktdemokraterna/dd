<?php

class db_workgroup {

	public static function list_all ($page, $limit = LIST_ITEMS_PER_PAGE){
// NOTE: This db function does not utilise full parametrised input due to bug in current MySQL that doesn't allow parametrised input in limit clause. Variables are instead sanitised by casting as int. When this bug is resolved, this function can be corrected. 

		$page = (int)($page-1) * $limit;
		$limit = (int)$limit;

		$query = "select * from workgroups where is_active=1 order by id asc limit " . $page . ", " . $limit;
		$values = Array();

		return db::select($query, $values);

	}

	public static function list_proposed ($page, $limit = LIST_ITEMS_PER_PAGE){
// NOTE: This db function does not utilise full parametrised input due to bug in current MySQL that doesn't allow parametrised input in limit clause. Variables are instead sanitised by casting as int. When this bug is resolved, this function can be corrected. 

		$page = (int)($page-1) * $limit;
		$limit = (int)$limit;

		$query = "select * from workgroups where is_active=0 order by id asc limit " . $page . ", " . $limit;
		$values = Array();

		return db::select($query, $values);

	}

	public static function list_workgroups_where_user_is_member ($user_id){

		$query = "select * from workgroups w where is_active=1 and exists (select * from workgroups_members wm where w.id = wm.workgroup_id and user_id = ?) order by id asc";
		$values = Array($user_id);

		return db::select($query, $values);

	}

	public static function create ($title, $description, $user_id){

		$already_exists = self::get_id_from_name($title);

		if($already_exists==0){
			$public_forum_id = db_forum_admin::add_forum(WORKGROUP_PUBLIC_FORUMS_CATEGORY, $title, "Publikt forum för arbetsgruppen".$title, "public");
			$private_forum_id = db_forum_admin::add_forum(WORKGROUP_PRIVATE_FORUMS_CATEGORY, $title, "Privat forum för arbetsgruppen".$title, "workgroup");

			$query = "insert into workgroups (title, description, propose_time, create_user, public_forum_id, private_forum_id) values (?, ?, ?, ?, ?, ?)";
			$values = Array($title, $description, time(), $user_id, $public_forum_id, $private_forum_id);

			return db::insert($query, $values);
		}
		else{
			return false;
		}

	}

	public static function create_restricted ($title, $description, $number_of_members){

		$already_exists = self::get_id_from_name($title);
		$constituency_id = DEFAULT_CONSTITUENCY_ID;

		if($already_exists==0 && $constituency_exists){
			$public_forum_id = db_forum_admin::add_forum(WORKGROUP_PUBLIC_FORUMS_CATEGORY, $title, "Publikt forum för arbetsgruppen".$title, "public");
			$private_forum_id = db_forum_admin::add_forum(WORKGROUP_PRIVATE_FORUMS_CATEGORY, $title, "Privat forum för arbetsgruppen".$title, "workgroup");

			$query = "insert into workgroups (title, description, is_active, number_of_members, create_time, create_user, public_forum_id, private_forum_id, is_restricted) values (?, ?, ?, ?, ?, ?, ?, ?, ?)";
			$values = Array($title, $description, 1, $number_of_members, time(), $_SESSION['id'], $public_forum_id, $private_forum_id, 1);

			$workgroup_id = db::insert($query, $values);

			if($workgroup_id){
				self::create_vote_for_restricted($workgroup_id, $title, $public_forum_id, $constituency_id, $_SESSION['id']);

				return $workgroup_id;
			}
		}

		return false;

	}

	public static function update ($workgroup_id, $description, $title = null, $number_of_members = null, $is_restricted = null){

		if($title == null || $number_of_members == null || $is_restricted == null){
			$workgroup_info = self::get_info($workgroup_id);
			$title = $workgroup_info['title'];
			$number_of_members = $workgroup_info['number_of_members'];
			$is_restricted = $workgroup_info['is_restricted'];
		}

		$query = "update workgroups set title = ?, description = ?, number_of_members = ?, is_restricted = ? where id = ?";
		$values = Array($title, $description, $number_of_members, $is_restricted, $workgroup_id);

		return db::update($query, $values);

	}

	public static function get_info ($id){

		$query = "select * from workgroups where id = ?";
		$values = Array($id);

		return db::select_single_row($query, $values);

	}

	public static function is_active ($workgroup_id){

		$query = "select is_active from workgroups where id = ?";
		$values = Array($workgroup_id);

		return db::select_single_value($query, $values);

	}

	public static function is_restricted ($workgroup_id){

		$query = "select is_restricted from workgroups where id = ?";
		$values = Array($workgroup_id);

		return db::select_single_value($query, $values);

	}

	public static function is_member ($workgroup_id, $user_id){

		$query = "select count(*) from workgroups_members where workgroup_id = ? and user_id = ?";
		$values = Array($workgroup_id, $user_id);

		return db::select_single_value($query, $values);

	}

	public static function is_candidate ($workgroup_id, $candidate_id){

		$query = "select count(*) from workgroups_candidates where workgroup_id = ? and candidate_id = ?";
		$values = Array($workgroup_id, $candidate_id);

		return db::select_single_value($query, $values);

	}

	public static function get_member_count ($workgroup_id){

		$query = "select number_of_members from workgroups where id = ?";
		$values = Array($workgroup_id);

		return db::select_single_value($query, $values);

	}

	public static function list_members ($workgroup_id){

		$query = "select u.id as user_id, concat(u.first_name, ' ', u.last_name) as full_name 
					from workgroups_members wm, users u where wm.user_id = u.id and wm.workgroup_id = ?";
		$values = Array($workgroup_id);

		return db::select($query, $values);

	}

	public static function get_member_ids ($workgroup_id){

		$query = "select user_id from workgroups_members where workgroup_id = ?";
		$values = Array($workgroup_id);

		return db::select_sequential_array($query, $values);

	}

	public static function list_candidates ($workgroup_id){

		$query = "select concat(u.first_name, ' ', u.last_name) as full_name, u.id as user_id 
					from workgroups_candidates wc, users u where wc.candidate_id = u.id and wc.workgroup_id = ?";
		$values = Array($workgroup_id);

		return db::select($query, $values);

	}

	public static function exclude_info ($workgroup_id, $excluded_id, $excluder_id){

		$query = "select count(*) as number_of_excluders, 
					(select id from workgroups_members_exclude wme2 where wme2.workgroup_id = ? and wme2.excluded_id = ? and wme2.excluder_id = ?) as is_excluder 
					from workgroups_members_exclude wme where wme.workgroup_id = ? and wme.excluded_id = ?";
		$values = Array($workgroup_id, $excluded_id, $excluder_id, $workgroup_id, $excluded_id);

		return db::select_single_row($query, $values);

	}

	public static function members_supporting_exclusion ($workgroup_id, $excluded_id){

		$query = "select count(*) from workgroups_members_exclude where workgroup_id = ? and excluded_id = ?";
		$values = Array($workgroup_id, $excluded_id);

		return db::select_single_value($query, $values);

	}

	public static function cancel_exclude ($workgroup_id, $excluded_id, $excluder_id){

		$query = "delete from workgroups_members_exclude where workgroup_id = ? and excluded_id = ? and excluder_id = ?";
		$values = Array($workgroup_id, $excluded_id, $excluder_id);

		return db::delete($query, $values);

	}

	public static function support_exclude ($workgroup_id, $excluded_id, $excluder_id){

		$db_table = "workgroups_members_exclude";
		$columns = Array("workgroup_id", "excluded_id", "excluder_id");
		$values = Array($workgroup_id, $excluded_id, $excluder_id);

		return db::insert_ignore($db_table, $columns, $values);

	}

	public static function calculate_exclusion ($workgroup_id, $excluded_id){

		$number_of_members = self::get_member_count($workgroup_id);
		$needed_member_count_for_exclusion = ceil($number_of_members / 1.999);
		$members_supporting_exclusion = self::members_supporting_exclusion($workgroup_id, $excluded_id);

		if($members_supporting_exclusion >= $needed_member_count_for_exclusion){ // Exclude member
			$ok = self::drop_member($workgroup_id, $excluded_id);
			if($ok) return "excluded";
			else return false;
		}
		else return "still member";

	}

	public static function drop_member ($workgroup_id, $excluded_id){

		$query = "delete from workgroups_members where workgroup_id = ? and user_id = ?";
		$values = Array($workgroup_id, $excluded_id);

		db::delete($query, $values);

		$query = "delete from workgroups_members_exclude where workgroup_id = ? and excluded_id = ?";
		$values = Array($workgroup_id, $excluded_id);

		db::delete($query, $values);

		$private_forum_id = self::get_private_forum_id($workgroup_id);

		db_forum_admin::remove_forum_access($excluded_id, $private_forum_id);

		if(!self::is_restricted($workgroup_id)){
			self::update_membership_count($workgroup_id);

			$number_of_members = self::get_member_count($workgroup_id);
			if($number_of_members < 3){
				self::deactivate($workgroup_id);
			}
		}

		return true;

	}

	public static function update_membership_count ($workgroup_id){

		$query = "update workgroups set number_of_members = (select count(*) from workgroups_members where workgroup_id = ?) where id = ?";
		$values = Array($workgroup_id, $workgroup_id);

		return db::update($query, $values);

	}

	public static function candidate_info ($workgroup_id, $candidate_id, $supporter_id){

		$query = "select count(*) as number_of_supporters, 
					(select id from workgroups_candidates_support wcs where wcs.workgroup_id = ? and wcs.candidate_id = ? and wcs.supporter_id = ?) as is_supporter 
					from workgroups_candidates_support wcs2 where wcs2.workgroup_id = ? and wcs2.candidate_id = ?";
		$values = Array($workgroup_id, $candidate_id, $supporter_id, $workgroup_id, $candidate_id);

		return db::select_single_row($query, $values);

	}

	public static function cancel_support ($workgroup_id, $candidate_id, $supporter_id){

		$query = "delete from workgroups_candidates_support where workgroup_id = ? and candidate_id = ? and supporter_id = ?";
		$values = Array($workgroup_id, $candidate_id, $supporter_id);

		return db::delete($query, $values);

	}

	public static function support_membership ($workgroup_id, $candidate_id, $supporter_id){

		$db_table = "workgroups_candidates_support";
		$columns = Array("workgroup_id", "candidate_id", "supporter_id");
		$values = Array($workgroup_id, $candidate_id, $supporter_id);

		return db::insert_ignore($db_table, $columns, $values);

	}

	public static function check_candidate_support ($workgroup_id, $candidate_id){

		$number_of_members = self::get_member_count($workgroup_id);
		$members_needed_for_elevation = ceil($number_of_members / 1.999);
		$members_supporting_candidate = self::members_supporting_candidate($workgroup_id, $candidate_id);

		if($members_supporting_candidate >= $members_needed_for_elevation){ // Elevate candidate
			$ok = self::add_member($workgroup_id, $candidate_id);
			if($ok) return "new member";
			else return false;
		}
		else return "still candidate";

	}

	public static function members_supporting_candidate ($workgroup_id, $candidate_id){

		$query = "select count(*) from workgroups_candidates_support where workgroup_id = ? and candidate_id = ?";
		$values = Array($workgroup_id, $candidate_id);

		return db::select_single_value($query, $values);

	}

	public static function add_member ($workgroup_id, $candidate_id){

		$query = "delete from workgroups_candidates where workgroup_id = ? and candidate_id = ?";
		$values = Array($workgroup_id, $candidate_id);

		db::delete($query, $values);

		$query = "delete from workgroups_candidates_support where workgroup_id = ? and candidate_id = ?";
		$values = Array($workgroup_id, $candidate_id);

		db::delete($query, $values);

		$query = "insert into workgroups_members (workgroup_id, user_id, member_since) values (?, ?, ?)";
		$values = Array($workgroup_id, $candidate_id, time());

		db::insert($query, $values);

		self::update_membership_count($workgroup_id);

		$private_forum_id = self::get_private_forum_id($workgroup_id);

		db_forum_admin::add_forum_access($candidate_id, $private_forum_id);

		return true;

	}

	public static function submit_candidacy ($workgroup_id, $candidate_id){

		$db_table = "workgroups_candidates";
		$columns = Array("workgroup_id", "candidate_id");
		$values = Array($workgroup_id, $candidate_id);

		return db::insert_ignore($db_table, $columns, $values);

	}

	public static function cancel_candidacy ($workgroup_id, $candidate_id){

		$query = "delete from workgroups_candidates where workgroup_id = ? and candidate_id = ?";
		$values = Array($workgroup_id, $candidate_id);

		db::delete($query, $values);

		$query = "delete from workgroups_candidates_support where workgroup_id = ? and candidate_id = ?";
		$values = Array($workgroup_id, $candidate_id);

		db::delete($query, $values);

	}

	public static function add_supporting_member ($workgroup_id, $candidate_id){

		$is_active = self::is_active($workgroup_id);
		if($is_active==1){
			return false;
		}
		else{
			$db_table = "workgroups_members";
			$columns = Array("workgroup_id", "user_id");
			$values = Array($workgroup_id, $candidate_id);

			db::insert_ignore($db_table, $columns, $values);

			self::update_membership_count($workgroup_id);

			$member_count = self::get_member_count($workgroup_id);

			if($member_count >= 3){
				$workgroup_name = self::get_info($workgroup_id);

				$public_forum_id = db_forum_admin::add_forum(WORKGROUP_PUBLIC_FORUMS_CATEGORY, $workgroup_name['title'], "Publikt forum för arbetsgruppen " . $workgroup_name['title'] . ".", "public");
				$private_forum_id = db_forum_admin::add_forum(WORKGROUP_PRIVATE_FORUMS_CATEGORY, $workgroup_name['title'], "Privat forum för arbetsgruppen " . $workgroup_name['title'] . ".", "workgroup");

				self::activate($public_forum_id, $private_forum_id, $workgroup_id);

				$members = self::list_members($workgroup_id);
				$query = "insert into forums_users (forum_id, user_id) values (" . $private_forum_id . ", ?)";

				db::insert_all($query, $members);

			}

			return true;

		}

	}

	public static function remove_supporting_member ($workgroup_id, $candidate_id){

		$query = "delete from workgroups_members where workgroup_id = ? and user_id = ?";
		$values = Array($workgroup_id, $candidate_id);

		$return = db::delete($query, $values);

		self::update_membership_count($workgroup_id);

		return $return;

	}

	public static function activate ($public_forum_id, $private_forum_id, $workgroup_id){

		$query = "update workgroups set is_active = 1, create_time = ?, public_forum_id = ?, private_forum_id = ? where id = ?";
		$values = Array(time(), $public_forum_id, $private_forum_id, $workgroup_id);

		db::update($query, $values);

		$query = "update workgroups_members set member_since = ? where workgroup_id = ?";
		$values = Array(time(), $workgroup_id);

		db::update($query, $values);

		return true;

	}

	public static function deactivate ($workgroup_id){

		$query = "update workgroups set is_active = 0 where id = ?";
		$values = Array($workgroup_id);

		return db::update($query, $values);

	}

	public static function get_private_forum_id ($workgroup_id){

		$query = "select private_forum_id from workgroups where id = ?";
		$values = Array($workgroup_id);

		return db::select_single_value($query, $values);

	}
	
	public static function get_id_from_name ($workgroup_name){

		$query = "select id from workgroups where title = ?";
		$values = Array($workgroup_name);

		return db::select_single_value($query, $values);

	}

	public static function get_name_from_id ($workgroup_id){

		$query = "select title as name from workgroups where id = ?";
		$values = Array($workgroup_id);

		return db::select_single_value($query, $values);

	}

	public static function get_number_of_members ($workgroup_id){

		$query = "select number_of_members from workgroups where id = ?";
		$values = Array($workgroup_id);

		return db::select_single_value($query, $values);

	}

	public static function get_workgroup_election_changes ($workgroup_id){

		$query = "select timestamp, user_id_in, user_id_out from workgroup_election_changes where workgroup_id = ?";
		$values = Array($workgroup_id);

		return db::select($query, $values);

	}

	public static function get_workgroup_election_members_in ($workgroup_id){

		$query = "select user_id_in from workgroup_election_changes where workgroup_id = ?";
		$values = Array($workgroup_id);

		return db::select_sequential_array($query, $values);

	}

	public static function get_workgroup_election_members_out ($workgroup_id){

		$query = "select user_id_out from workgroup_election_changes where workgroup_id = ?";
		$values = Array($workgroup_id);

		return db::select_sequential_array($query, $values);

	}

	public static function check_if_workgroup_election_member_in_exists_and_get_timestamp ($workgroup_id, $user_id){

		$query = "select timestamp from workgroup_election_changes where workgroup_id = ? and user_id_in = ?";
		$values = Array($workgroup_id, $user_id);

		return db::select_single_value($query, $values);

	}

	public static function check_if_workgroup_election_member_out_exists_and_get_timestamp ($workgroup_id, $user_id){

		$query = "select timestamp from workgroup_election_changes where workgroup_id = ? and user_id_out = ?";
		$values = Array($workgroup_id, $user_id);

		return db::select_single_value($query, $values);

	}

	public static function get_oldest_workgroup_election_member ($workgroup_id){

		$query = "select * from workgroup_election_changes where workgroup_id = ? order by timestamp asc limit 1";
		$values = Array($workgroup_id);

		return db::select_single_value($query, $values);

	}

	public static function get_workgroup_election_changes_for_member_in ($workgroup_id, $user_id_in){

		$query = "select * from workgroup_election_changes where workgroup_id = ? and user_id_in = ?";
		$values = Array($workgroup_id, $user_id_in);

		return db::select_single_row($query, $values);

	}

	public static function insert_workgroup_election_changes ($workgroup_id, $user_id_in, $user_id_out){

		$query = "insert into workgroup_election_changes (workgroup_id, timestamp, user_id_in, user_id_out) values (?, ?, ?, ?)";
		$values = Array($workgroup_id, time(), $user_id_in, $user_id_out);

		return db::insert($query, $values);

	}

	public static function delete_workgroup_election_changes ($workgroup_election_changes_id){

		$query = "delete from workgroup_election_changes where id = ?";
		$values = Array($workgroup_election_changes_id);

		return db::delete($query, $values);

	}

	public static function get_workgroup_election_changes_to_execute (){

		$query = "select id, workgroup_id, timestamp, user_id_in, user_id_out from workgroup_election_changes where timestamp < ?";
		$values = Array(time() + BUFFER_TIME_FOR_CONTINUOUS_ELECTIONS);

		return db::select($query, $values);

	}

	public static function make_un_restricted ($workgroup_id){

		$workgroup_info = self::get_info($_GET['id']);
		$vote_id = $workgroup_info['is_restricted'];

		db_vote::finish_vote($vote_id);

		$query = "update workgroups set is_restricted = 0 where id = ?";
		$values = Array($workgroup_id);

		return db::update($query, $values);

	}

	public static function make_restricted ($workgroup_id){

		$constituency_id = DEFAULT_CONSTITUENCY_ID;

		$workgroup_info = self::get_info($workgroup_id);

		self::create_vote_for_restricted($workgroup_id, $workgroup_info['title'], $workgroup_info['public_forum_id'], $constituency_id, $workgroup_info['create_user']);

		$query = "update workgroups set is_restricted = ? where id = ?";
		$values = Array($vote_id, $workgroup_id);

		return db::update($query, $values);

	}

	private static function create_vote_for_restricted ($workgroup_id, $title, $public_forum_id, $constituency_id, $user_id){

		$vote_title = "Val av medlemmar till arbetsgruppen " . $title;
		$vote_description = "Denna omröstning utser medlemmarna i arbetsgruppen <a href=\"index.php?type=workgroup&action=view&id=" . $workgroup_id . "\">" . $title . "</a>.";

		$forum_topic_id = db_forum::new_topic($user_id, $public_forum_id, "Personval till arbetsgruppen ".$title);
		db_forum::add_content_to_post($forum_topic_id, $vote_description);

		return db_vote_admin::create_workgroup_election($workgroup_id, $constituency_id, $vote_title, $vote_description, $forum_topic_id);

	}

}