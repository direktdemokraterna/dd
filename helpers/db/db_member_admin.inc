<?php

class db_member_admin 
{
	public static function delete_user ($user_id)
	{
		$query = "update user set deletion_time = ? where id = ?";
		$values = Array(time(), $user_id);
		$ok = db::update($query, $values);
		if ($ok)
			\Logic\vote::remove_prop_ballots($user_id);
		return $ok;
	}

	public static function restore_user ($user_id)
	{
		$query = "update user set deletion_time = null where id = ?";
		$values = Array($user_id);
		return db::update($query, $values);
	}
}