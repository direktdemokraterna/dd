<?

class db_message {

	public static function check_unread ($user_id){

		$query = "select count(*) from messages where read_time = 0 and deleted_by_recipient = 0 and recipient_id = ?";
		$values = Array($user_id);

		return db::select_single_value($query, $values);

	}

	public static function mark_read ($message_id, $user_id){

		$query = "update messages set read_time = ? where read_time = 0 and id = ? and recipient_id = ?";
		$values = Array(time(), $message_id, $user_id);

		return db::update($query, $values);

	}

	public static function get_message ($message_id){

		$query = "select *, 
					(select concat(first_name, ' ', last_name) from users where users.id = messages.recipient_id) as recipient_name, 
					(select concat(first_name, ' ', last_name) from users where users.id = messages.sender_id) as sender_name
					from messages where id = ?";
		$values = Array($message_id);

		return db::select_single_row($query, $values);

	}

	public static function get_reply_message ($message_id){

		$query = "select u.username as username, concat(u.first_name, ' ', u.last_name) as full_name, m.title as title, m.content as content 
					from messages m, users u where m.sender_id = u.id and m.id = ?";
		$values = Array($message_id);

		return db::select_single_row($query, $values);

	}

	public static function create_message ($sender_id, $recipient_id, $title, $message){

		$query = "insert into messages (sender_id, recipient_id, sent_time, title, content) values (?, ?, ?, ?, ?)";
		$values = Array($sender_id, $recipient_id, time(), $title, $message);

		return db::insert($query, $values);

	}

	public static function get_inbox ($user_id, $page, $limit = LIST_ITEMS_PER_PAGE){
// NOTE: This db function does not utilise full parametrised input due to bug in current MySQL that doesn't allow parametrised input in limit clause. Variables are instead sanitised by casting as int. When this bug is resolved, this function can be corrected. 

		$page = (int)($page-1) * $limit;
		$limit = (int)$limit;
		
		$query = "select *, 
					(select concat(first_name, ' ', last_name) from users where users.id = messages.sender_id) as full_name 
					from messages where recipient_id = ? and deleted_by_recipient = 0 order by sent_time desc limit " . $page . ", " . $limit;
		$values = Array($user_id);

		return db::select($query, $values);

	}

	public static function get_outbox ($user_id, $page, $limit = 20){
// NOTE: This db function does not utilise full parametrised input due to bug in current MySQL that doesn't allow parametrised input in limit clause. Variables are instead sanitised by casting as int. When this bug is resolved, this function can be corrected. 

		$page = (int)($page-1) * $limit;
		$limit = (int)$limit;
		
		$query = "select *, 
					(select concat(first_name, ' ', last_name) from users where users.id = messages.recipient_id) as full_name 
					from messages where sender_id = ? and deleted_by_sender = 0 order by sent_time desc limit " . $page . ", " . $limit;
		$values = Array($user_id);

		return db::select($query, $values);

	}

	public static function delete_inbox ($message_ids, $user_id){

		$in_clause = implode(',', array_fill(0, count($message_ids), '?'));

		$query = "update messages set deleted_by_recipient = " . time() . " where id in (" . $in_clause . ") and recipient_id = ?";
		$values = $message_ids;
		array_push($values, $user_id);

		return db::update($query, $values);

	}

	public static function delete_outbox ($message_ids, $user_id){

		$in_clause = implode(',', array_fill(0, count($message_ids), '?'));

		$query = "update messages set deleted_by_sender = " . time() . " where id in (" . $in_clause . ") and sender_id = ?";
		$values = $message_ids;
		array_push($values, $user_id);

		return db::update($query, $values);

	}

	public static function cancel ($message_id, $user_id){

		$query = "delete from messages where id = ? and sender_id = ? and read_time = 0";
		$values = Array($message_id, $user_id);

		return db::delete($query, $values);

	}


}