<?php

class db_message 
{
	public static function check_unread ($user_id)
	{
		$query = "select count(*) from message where read_time = 0 and deleted_by_recipient = 0 and recipient_id = ?";
		$values = Array($user_id);
		return db::select_single_value($query, $values);
	}

	public static function mark_read ($message_id, $user_id)
	{
		$query = "update message set read_time = ? where read_time = 0 and id = ? and recipient_id = ?";
		$values = Array(time(), $message_id, $user_id);
		return db::update($query, $values);
	}

	public static function get_message ($message_id)
	{
		$query = "select m.*
					,concat(ur.first_name, ' ', ur.last_name) as recipient_name
					,concat(us.first_name, ' ', us.last_name) as sender_name
					,us.username sender_username
					from message m
						join user us on us.id = m.sender_id 
						join user ur on ur.id = m.recipient_id 
					where m.id = ?";
		$values = Array($message_id);
		return db::select_single_row($query, $values);
	}

	public static function create_message ($sender_id, $recipient_id, $title, $message)
	{
		$query = "insert into message (sender_id, recipient_id, sent_time, title, content) values (?, ?, ?, ?, ?)";
		$values = Array($sender_id, $recipient_id, time(), $title, $message);
		return db::insert($query, $values);
	}

	public static function get_inbox ($user_id, $page, $sort)
	{
		$limit_clause = db_general::get_limit_clause($page, LIST_ITEMS_PER_PAGE);
		$order_by_clause = "order by " . self::get_inbox_order_by($sort);
		$visible_columns = implode(", ", self::$inbox_visible_columns);
		$query = "select m.id, $visible_columns, m.sender_id, m.read_time
					from message m
						join user s on s.id = m.sender_id
					where recipient_id = ? and deleted_by_recipient = 0 
					" . $order_by_clause . "
					" . $limit_clause;
		$values = Array($user_id);
		return db::select($query, $values);
	}

	public static function get_inbox_count ($user_id)
	{
		$query = "select count(*)
					from message where recipient_id = ? and deleted_by_recipient = 0";
		$values = Array($user_id);
		return db::select_single_value($query, $values);
	}

	public static function get_outbox ($user_id, $page, $sort){
		$limit_clause = db_general::get_limit_clause($page, LIST_ITEMS_PER_PAGE);
		$order_by_clause = "order by " . self::get_outbox_order_by($sort);
		$visible_columns = implode(", ", self::$outbox_visible_columns);
		$query = "select m.id, $visible_columns, m.recipient_id, m.read_time
					from message m
						join user r on r.id = m.recipient_id
					where sender_id = ? and deleted_by_sender = 0 
					" . $order_by_clause . "
					" . $limit_clause;
		$values = Array($user_id);
		return db::select($query, $values);
	}

	public static function get_outbox_count ($user_id){
		$query = "select count(*)
					from message where sender_id = ? and deleted_by_sender = 0";
		$values = Array($user_id);
		return db::select_single_value($query, $values);
	}

	private static function get_inbox_order_by ($sort = 0)
	{
		return db_general::get_order_by(self::$inbox_visible_columns, 1, $sort);
	}

	private static $inbox_visible_columns =
		array("concat(s.first_name, ' ', s.last_name) as full_name", "m.title", "m.sent_time");

	private static function get_outbox_order_by ($sort = 0)
	{
		return db_general::get_order_by(self::$outbox_visible_columns, 1, $sort);
	}

	private static $outbox_visible_columns =
		array("concat(r.first_name, ' ', r.last_name) as full_name", "m.title", "m.sent_time");

	public static function delete_inbox ($message_ids, $user_id)
	{
		$in_clause = implode(',', array_fill(0, count($message_ids), '?'));
		$query = "update message set deleted_by_recipient = " . time() . " where id in (" . $in_clause . ") and recipient_id = ?";
		$values = $message_ids;
		array_push($values, $user_id);
		return db::update($query, $values);
	}

	public static function delete_outbox ($message_ids, $user_id)
	{
		$in_clause = implode(',', array_fill(0, count($message_ids), '?'));
		$query = "update message set deleted_by_sender = " . time() . " where id in (" . $in_clause . ") and sender_id = ?";
		$values = $message_ids;
		array_push($values, $user_id);
		return db::update($query, $values);
	}

	public static function cancel ($message_id, $user_id)
	{
		$query = "delete from message where id = ? and sender_id = ? and read_time = 0";
		$values = Array($message_id, $user_id);
		return db::delete($query, $values);
	}
}