<?

class db_admin {
	
	public static function get_admin_roles_for_user ($user_id){

		$query = "select admin_roles.* from admin_roles, admin_roles_users where admin_roles_users.admin_role_id = admin_roles.id and user_id = ?";
		$values = Array($user_id);

		return db::select($query, $values);

	}

	public static function get_all_admin_roles_and_if_user_belongs ($user_id){

		$query = "select admin_roles.*, (if (exists (select * from admin_roles_users where admin_role_id = admin_roles.id and user_id = ?), 1, 0)) as user_role from admin_roles";
		$values = Array($user_id);

		return db::select($query, $values);

	}

	public static function get_admin_role_info ($admin_role_id){

		$query = "select * from admin_roles where id = ?";
		$values = Array($admin_role_id);

		return db::select_single_row($query, $values);

	}

	public static function get_admin_role_users ($admin_role_id){

		$query = "select users.* from users, admin_roles_users where admin_roles_users.user_id=users.id and admin_roles_users.admin_role_id = ?";
		$values = Array($admin_role_id);

		return db::select($query, $values);

	}

	public static function update_admin_roles_for_user ($admin_role_ids, $user_id){

		$not_in_clause = implode(',', array_fill(0, count($admin_role_ids), '?'));

		$query = "delete from admin_roles_users where admin_role_id not in (" . $not_in_clause . ") and user_id = ?";
		$values = $admin_role_ids;
		array_push($values, $user_id);

		$deleted = db::delete($query, $values);

		$query = "insert into admin_roles_users (admin_role_id, user_id) select * from (select ? as admin_role_id, ? as user_id) as tmp where not exists (select * from admin_roles_users where admin_role_id = ? and user_id = ?) limit 1";
		$inserted = db::insert_ignore_from_array($query, $admin_role_ids, $user_id);

		return $deleted + $inserted;

	}

	public static function remove_all_admin_roles_for_user ($user_id){

		$query = "delete from admin_roles_users where user_id = ?";
		$values = Array($user_id);

		return db::delete($query, $values);

	}

}