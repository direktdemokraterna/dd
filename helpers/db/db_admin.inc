<?php

class db_admin 
{
	public static function get_all_admin_roles ()
	{
		$query = "select * from admin_role";
		$values = Array();
		return db::select($query, $values);
	}

	public static function get_admin_roles_for_user ($user_id)
	{
		$query = "select admin_role.* from admin_role, admin_role_user where admin_role_user.admin_role_id = admin_role.id and user_id = ?";
		$values = Array($user_id);
		return db::select($query, $values);
	}

	public static function get_all_admin_roles_and_if_user_belongs ($user_id)
	{
		$query = "select admin_role.*, (if (exists (select * from admin_role_user where admin_role_id = admin_role.id and user_id = ?), 1, 0)) as user_role from admin_role";
		$values = Array($user_id);
		return db::select($query, $values);
	}

	public static function get_admin_role_info ($admin_role_id)
	{
		$query = "select * from admin_role where id = ?";
		$values = Array($admin_role_id);
		return db::select_single_row($query, $values);
	}

	public static function get_admin_role_users ($admin_role_id)
	{
		$query = "select u.id as id, concat(u.first_name, ' ', u.last_name) as full_name from user u, admin_role_user aru where aru.user_id = u.id and aru.admin_role_id = ?";
		$values = Array($admin_role_id);
		return db::select($query, $values);
	}

	public static function update_admin_roles_for_user ($admin_role_ids, $user_id)
	{
		$not_in_clause = implode(',', array_fill(0, count($admin_role_ids), '?'));
		$query = "delete from admin_role_user where admin_role_id not in (" . $not_in_clause . ") and user_id = ?";
		$values = $admin_role_ids;
		array_push($values, $user_id);
		$deleted = db::delete($query, $values);
		$query = "insert into admin_role_user (admin_role_id, user_id) select ? as admin_role_id, ? as user_id from dual where not exists (select * from admin_role_user where admin_role_id = ? and user_id = ?) limit 1";
		$inserted = db::insert_ignore_from_array($query, $admin_role_ids, $user_id);
		return $deleted + $inserted;
	}

	public static function remove_all_admin_roles_for_user ($user_id)
	{
		$query = "delete from admin_role_user where user_id = ?";
		$values = Array($user_id);
		return db::delete($query, $values);
	}
}