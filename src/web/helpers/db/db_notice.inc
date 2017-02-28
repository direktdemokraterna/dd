<?php

class db_notice 
{
	public static function get_user_settings ($user_id)
	{
		$query = "select view_quoting_post, email_quoting_post, view_subscribed_topic, email_subscribed_topic, view_vote_started, email_vote_started, view_vote_finished, email_vote_finished, view_proposition_created, email_proposition_created, email_message, email_notification_interval from notice_user_setting where user_id = ?";
		return db::select_single_row($query, $user_id);
	}

	public static function update_user_settings ($user_id, $view_quoting_post, $email_quoting_post, $view_subscribed_topic, $email_subscribed_topic, $view_vote_started, $email_vote_started, $view_vote_finished, $email_vote_finished, $view_proposition_created, $email_proposition_created, $email_message, $email_notification_interval)
	{
		$query = "update notice_user_setting set view_quoting_post = ?, email_quoting_post = ?, view_subscribed_topic = ?, email_subscribed_topic = ?, view_vote_started = ?, email_vote_started = ?, view_vote_finished = ?, email_vote_finished = ?, view_proposition_created = ?, email_proposition_created = ?, email_message = ?, email_notification_interval = ? where user_id = ?";
		$values = Array($view_quoting_post, $email_quoting_post, $view_subscribed_topic, $email_subscribed_topic, $view_vote_started, $email_vote_started, $view_vote_finished, $email_vote_finished, $view_proposition_created, $email_proposition_created, $email_message, $email_notification_interval, $user_id);
		return db::update($query, $values);
	}

	public static function create_user_settings ($user_id)
	{
		$query = "insert into notice_user_setting (user_id) values (?)";
		return db::insert($query, $user_id);
	}

	public static function get_view_notices_for_user ($user_id)
	{
		$query = "select id from notice where user_id = ? and view_or_email = 'view' order by timestamp_created desc";
		return db::select($query, $user_id);
	}

	public static function get_notice_info ($notice_id)
	{
		$query = "select * from notice where id=?";
		return db::select_single_row($query, $notice_id);
	}

	public static function does_notice_exist ($user_id, $view_or_email, $type_of_notification, $action_id)
	{
		$query = "select id from notice where user_id=? and view_or_email=? and type_of_notification=? and action_id=?";
		$values = Array($user_id, $view_or_email, $type_of_notification, $action_id);
		if(empty(db::select($query, $values))) return false;
		else return true;
	}

	public static function create_notice ($user_id, $view_or_email, $type_of_notification, $action_id)
	{
		$query = "insert into notice (user_id, timestamp_created, view_or_email, type_of_notification, action_id) values (?, ?, ?, ?, ?)";
		$values = Array($user_id, time(), $view_or_email, $type_of_notification, $action_id);
		return db::insert($query, $values);
	}

	public static function make_quoting_post_notice ($user_id, $quoting_post_id)
	{
		$quoting_post_user_id = db_forum::get_user_id_from_post($quoting_post_id);
//		if($user_id != $quoting_post_user_id){
			if(self::does_user_want_notice($user_id, "view_quoting_post")){
				if(empty(self::does_notice_exist($user_id, 'view', 'quoting_post', $quoting_post_id)))
					self::create_notice($user_id, 'view', 'quoting_post',$quoting_post_id);
			}
			if(self::does_user_want_notice($user_id, "email_quoting_post")){
				if(empty(self::does_notice_exist($user_id, 'email', 'quoting_post',$quoting_post_id)))
					self::create_notice($user_id, 'email', 'quoting_post',$quoting_post_id);
			}
//		}
	}

	public static function make_subscribed_topic_notice ($user_id, $topic_id)
	{
		if(self::does_user_want_notice($user_id, "view_subscribed_topic")){
			if(empty(self::does_notice_exist($user_id, 'view', 'subscribed_topic', $topic_id)))
				self::create_notice($user_id, 'view', 'subscribed_topic', $topic_id);
		}
		if(self::does_user_want_notice($user_id, "email_subscribed_topic")){
			if(empty(self::does_notice_exist($user_id, 'email', 'subscribed_topic', $topic_id)))
				self::create_notice($user_id, 'email', 'subscribed_topic', $topic_id);
		}
	}

	public static function make_vote_started_notice ($vote_id)
	{
		$constituency_id = db_constituency::get_vote_constituency_id($vote_id);
		$query = "select u.id as id from user u, constituency_voter cv, notice_user_setting n where n.user_id=u.id and cv.constituency_id=? and cv.voter_id=u.id and n.view_vote_finished=1";
		$users_who_want_view_notice = db::select($query, $constituency_id);
		foreach ($users_who_want_view_notice as $user) {
			self::create_notice($user['id'], 'view', 'vote_started', $vote_id);
		}
		$query = "select u.id as id from user u, constituency_voter cv, notice_user_setting n where n.user_id=u.id and cv.constituency_id=? and cv.voter_id=u.id  and n.email_vote_finished=1";
		$users_who_want_email_notice = db::select($query, $constituency_id);
		foreach ($users_who_want_email_notice as $user) {
			self::create_notice($user['id'], 'email', 'vote_started', $vote_id);
		}
	}

	public static function make_vote_finished_notice ($vote_id)
	{
		$constituency_id = db_constituency::get_vote_constituency_id($vote_id);
		$query = "select u.id as id from user u, constituency_voter cv, notice_user_setting n where n.user_id=u.id and cv.constituency_id=? and cv.voter_id=u.id and n.view_vote_finished=1";
		$users_who_want_view_notice = db::select($query, $constituency_id);
		foreach ($users_who_want_view_notice as $user) {
			self::create_notice($user['id'], 'view', 'vote_finished', $vote_id);
		}
		$query = "select u.id as id from user u, constituency_voter cv, notice_user_setting n where n.user_id=u.id and cv.constituency_id=? and cv.voter_id=u.id  and n.email_vote_finished=1";
		$users_who_want_email_notice = db::select($query, $constituency_id);
		foreach ($users_who_want_email_notice as $user) {
			self::create_notice($user['id'], 'email', 'vote_finished', $vote_id);
		}
	}

	public static function make_proposition_created_notice ($prop_id)
	{
		$constituency_id = db_constituency::get_prop_constituency_id($prop_id);
		$query = "select u.id as id from user u, constituency_voter cv, notice_user_setting n where n.user_id=u.id and cv.constituency_id=? and cv.voter_id=u.id and n.view_proposition_created=1 and u.id!=?";
		$values = Array($constituency_id, $_SESSION['id']);
		$users_who_want_view_notice = db::select($query, $values);
		foreach ($users_who_want_view_notice as $user) {
			self::create_notice($user['id'], 'view', 'proposition_created', $prop_id);
		}
		$query = "select u.id as id from user u, constituency_voter cv, notice_user_setting n where n.user_id=u.id and cv.constituency_id=? and cv.voter_id=u.id  and n.email_proposition_created=1 and u.id!=?";
		$values = Array($constituency_id, $_SESSION['id']);
		$users_who_want_email_notice = db::select($query, $values);
		foreach ($users_who_want_email_notice as $user) {
			self::create_notice($user['id'], 'email', 'proposition_created', $prop_id);
		}
	}

	public static function make_message_notice ($user_id, $prop_id)
	{
		if(self::does_user_want_notice($user_id, "email_message"))
			self::create_notice($user_id, 'email', 'message', $prop_id);
	}

	public static function does_user_want_notice ($user_id, $notice_type)
	{
		$query = "select " . $notice_type . " from notice_user_setting where user_id=?";
		if(empty(db::select_single_value($query, $user_id))) return false;
		else return true;
	}

	public static function remove_own_notice ($id)
	{
		$query = "delete from notice where id=? and user_id=?";
		$values = Array($id, $_SESSION['id']);
		return db::delete($query, $values);
	}

	public static function remove_all_view_notices ($user_id)
	{
		$query = "delete from notice where user_id=? and view_or_email='view'";
		return db::delete($query, $user_id);
	}

	public static function get_users_to_send_emails_to ()
	{
		$query = "select nus.user_id as user_id from notice_user_setting nus where (last_email_notification+email_notification_interval)<? and exists (select * from notice n where view_or_email='email' and nus.user_id=n.user_id)";
		return db::select($query, time());
	}

	public static function get_email_notices_for_user ($user_id)
	{
		$query = "select * from notice where type_of_notification='email' and user_id=? order by type_of_notification asc, timestamp_created desc";
		return db::select($query, $user_id);
	}

	public static function delete_email_notices_for_user ($user_id)
	{
		$query = "delete from notice where user_id=? and view_or_email='email'";
		return db::delete($query, $user_id);
	}

	public static function update_last_email_notification ($user_id, $time)
	{
		$query = "update notice_user_setting set last_email_notification=? where user_id=?";
		$values = Array($time, $user_id);
		return db::update($query, $values);
	}

} 