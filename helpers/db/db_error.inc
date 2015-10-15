<?php

class db_error 
{
	public static function insert_error_message ($user_id, $message, $color = "green")
	{
		$query = "insert into error_messages (user_id, message, color, timestamp) values (?, ?, ?, ?)";
		$values = Array($user_id, $message, $color, time());
		return db::insert($query, $values);
	}

	public static function retrieve_error_message ($user_id)
	{
		$query = "select * from error_messages where user_id = ?";
		$values = Array($user_id);
		$result = db::select($query, $values);
		$query = "delete from error_messages where user_id = ?";
		$values = Array($user_id);
		db::delete($query, $values);
		return $result;
	}
}
?>