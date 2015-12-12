<?php

class db_member_admin 
{
	public static function delete_user ($user_id)
	{
		$query = "update user set deletion_time = ? where id = ?";
		$values = Array(time(), $user_id);
		return db::update($query, $values);
	}

	public static function restore_user ($user_id)
	{
		$query = "update user set deletion_time = null where id = ?";
		$values = Array($user_id);
		return db::update($query, $values);
	}
}