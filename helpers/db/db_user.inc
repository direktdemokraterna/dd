<?php
class db_user 
{
	public static function delete_user ($user_id)
	{
		$query = "update user set deletion_time = ? where id = ?";
		$values = Array(time(), $user_id);
		$ok = db::update($query, $values);
		return $ok;
	}

	public static function restore_user ($user_id)
	{
		$query = "update user set deletion_time = null where id = ?";
		$values = Array($user_id);
		return db::update($query, $values);
	}

	public static function add_user ($username, $password, $first_name, $last_name, $street_address, $zip_code, $city_address, $county_id, $region_id, $social_security_number, $email, $skype_name = "")
	{
		$user_id = \db_general::create_voter('user');
		$query = "insert into user (id, username, password, registration_time, first_name, last_name, street_address, zip_code, city_address, county_id, region_id, social_security_number, email, skype_name) values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
		$values = Array($user_id, $username, $password, time(), $first_name, $last_name, $street_address, $zip_code, $city_address, $county_id, $region_id, $social_security_number, $email, $skype_name);
		db::insert($query, $values);

		// Adding forum accesses for new user
		$public_forums = db_forum::get_public_forum_ids();
		foreach($public_forums as $row)
			db_forum_admin::add_forum_access($user_id, $row['id']);
		$local_county_forum = db_forum::get_local_county_forum($county_id);
		db_forum_admin::add_forum_access($user_id, $local_county_forum);
		$local_region_forum = db_forum::get_local_region_forum($region_id);
		db_forum_admin::add_forum_access($user_id, $local_region_forum);

		// Adding constituency access for new user
		$public_constituencies = db_constituency::get_public_constituency_ids();
		foreach($public_constituencies as $row)
			db_constituency::add_constituency_access($user_id, $row['id']);
		db_constituency::add_constituency_access($user_id, $county_id);
		db_constituency::add_constituency_access($user_id, $region_id);
		return $user_id;
	}

	public static function get_all_users ($page = 1, $limit = LIST_ITEMS_PER_PAGE, $sort = 0, $where_filters)
	{
		$where_clause = self::create_where_clause($where_filters);
		$limit_clause = db_general::get_limit_clause($page, $limit);
		$order_by_clause = "order by " . self::get_order_by($sort);
		$visible_columns = implode(", ", self::$members_visible_columns);
		$query = "select u.id, $visible_columns, u.deletion_time
			from user u
				left join constituency cr on cr.id = u.region_id
				left join constituency cc on cc.id = u.county_id
				" . $where_clause . "
				" . $order_by_clause . " 
				" . $limit_clause;
		$values = array();
		return db::select($query, $values);
	}

	private static function get_order_by ($sort = 0)
	{
		return db_general::get_order_by(self::$members_visible_columns, 1, $sort);
	}

	private static $members_visible_columns =
		array("concat(if(u.activation_first_name is null, u.first_name, if(u.activation_first_name = '', 'Inget', u.activation_first_name)), ' ', if(u.activation_last_name is null, u.last_name, if(u.activation_last_name = '', 'namn', u.activation_last_name))) as full_name", "u.username"
			, "cr.title as region", "cc.title as county");

	public static function get_all_users_count ($where_filters)
	{
		$where_clause = self::create_where_clause($where_filters);
		$query = "select count(*) from user u " . $where_clause;
		$values = Array();
		return db::select_single_value($query, $values);
	}

	public static function create_where_clause ($where_filters)
	{
		return $where_filters ? " where " . implode(" and ", $where_filters) : "";
	}

	public static function get_user_data ($id)
	{
		return self::get_user_data_from("u.id = ?", array($id));
	}

	public static function get_password ($id)
	{
		$query = "select password from user where id = ?";
		$values = Array($id);
		return db::select_single_value($query, $values);
	}

	public static function get_user_data_from_username ($username)
	{
		return self::get_user_data_from("u.username = ?", array($username));
	}
	
	private static function get_user_data_from ($condition, $values)
	{
		$query = "select u.*, concat(u.first_name, ' ', u.last_name) as full_name
		, cr.title as region_name, cc.title as county_name
		 from user u 
			 join constituency cr on cr.id = u.region_id
			 join constituency cc on cc.id = u.county_id
		 where " . $condition;
		return db::select_single_row($query, $values);
	}

	public static function update_last_activity_time ($user_id)
	{
		$query = "update user set last_activity_time = ? where id = ?";
		$values = Array(time(), $user_id);
		return db::update($query, $values);
	}

	public static function update_last_login_time ($user_id)
	{
		$query = "update user set last_login_time = ? where id = ?";
		$values = Array(time(), $user_id);
		return db::update($query, $values);
	}

	public static function update_password ($password_hash, $id)
	{
		$query = "update user set password = ? where id = ?";
		$values = Array($password_hash, $id);
		return db::update($query, $values);
	}

	public static function update_image ($image, $id)
	{
		$query = "update user set image = ? where id = ?";
		$values = Array($image, $id);
		return db::update($query, $values);
	}

	public static function update_settings ($show_email, $show_telephone, $show_skype, $id)
	{
		$query = "update user set show_email = ?, show_telephone = ?, show_skype = ? where id = ?";
		$values = Array($show_email, $show_telephone, $show_skype, $id);
		return db::update($query, $values);
	}

	public static function update_profile ($first_name, $last_name, $street_address, $zip_code, $city_address, $county_id, $region_id, $email, $skype_name, $telephone1, $telephone2, $id)
	{
		$query = "update user set first_name = ?, last_name = ?, street_address = ?, zip_code = ?, city_address = ?, county_id = ?, region_id = ?, email = ?, skype_name = ?, telephone1 = ?, telephone2 = ? where id = ?";
		$values = Array($first_name, $last_name, $street_address, $zip_code, $city_address, $county_id, $region_id, $email, $skype_name, $telephone1, $telephone2, $id);
		return db::update($query, $values);
	}

	public static function update_description ($description, $id)
	{
		$query = "update user set description = ? where id = ?";
		$values = Array($description, $id);
		return db::update($query, $values);
	}

	public static function update_user_by_admin ($username, $first_name, $last_name, $street_address, $zip_code, $city_address, $county_id, $region_id, $social_security_number, $email, $skype_name, $telephone1, $telephone2, $id)
	{
		$query = "update user set username = ?, first_name = ?, last_name = ?, street_address = ?, zip_code = ?, city_address = ?, county_id = ?, region_id = ?, social_security_number = ?, email = ?, skype_name = ?, telephone1 = ?, telephone2 = ? where id = ?";
		$values = Array($username, $first_name, $last_name, $street_address, $zip_code, $city_address, $county_id, $region_id, $social_security_number, $email, $skype_name, $telephone1, $telephone2, $id);
		return db::update($query, $values);
	}

	public static function get_username ($user_id)
	{
		$query = "select username from user where id = ?";
		$values = Array($user_id);
		return db::select_single_value($query, $values);
	}

	public static function get_user_id ($username)
	{
		$query = "select id from user where username = ?";
		$values = Array($username);
		return db::select_single_value($query, $values);
	}

	public static function get_activation_first_name ($user_id)
	{
		$query = "select activation_first_name from user where id = ?";
		$values = Array($user_id);
		return db::select_single_value($query, $values);
	}

	public static function get_user_full_name ($user_id)
	{
		$query = "select concat(first_name, ' ', last_name) as full_name from user where id = ?";
		$values = Array($user_id);
		return db::select_single_value($query, $values);
	}

	public static function set_remember_me_token ($remember_me_token, $id)
	{
		$query = "update user set remember_me_token = ? where id = ?";
		$values = Array($remember_me_token, $id);
		return db::update($query, $values);
	}

	public static function get_all_user_ids ()
	{
		$query = "select id from user";
		$values = Array();
		return db::select($query, $values);
	}

	public static function get_all_usernames_and_full_names ()
	{
		$query = "select username as username, concat(first_name, ' ', last_name) as full_name from user";
		$values = Array();
		return db::select($query, $values);
	}

	public static function get_all_ids_full_names_and_social_security_numbers ()
	{
		$query = "select u.id as id, concat(if(u.activation_first_name is null, u.first_name, if(u.activation_first_name = '', 'Inget', u.activation_first_name)), ' ', if(u.activation_last_name is null, u.last_name, if(u.activation_last_name = '', 'namn', u.activation_last_name))) as full_name, u.social_security_number as social_security_number from user u order by full_name asc";
		$values = Array();
		return db::select($query, $values);
	}

	public static function search_users ($search, $page = 1, $limit = LIST_ITEMS_PER_PAGE)
	{
		$limit_clause = db_general::get_limit_clause($page, $limit);
		$query = "select id, concat(if(activation_first_name is null, first_name, if(activation_first_name = '', 'Inget', activation_first_name)), ' ', if(activation_last_name is null, last_name, if(activation_last_name = '', 'namn', activation_last_name))) as full_name from user 
					where match(first_name, last_name, description, activation_first_name, activation_last_name) against (? in boolean mode) 
					" . $limit_clause;
		$values = Array($search);
		return db::select($query, $values);
	}

	public static function enter_user_application ($first_name, $last_name, $street_address, $zip_code, $city_address, $county_id, $region_id, $social_security_number, $email, $telephone1, $telephone2)
	{
		$query = "insert into user_application (application_filed_time, first_name, last_name, street_address, zip_code, city_address, county_id, region_id, social_security_number, email, telephone1, telephone2) values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
		$values = Array(time(), $first_name, $last_name, $street_address, $zip_code, $city_address, $county_id, $region_id, $social_security_number, $email, $telephone1, $telephone2);
		return db::insert($query, $values);
	}

	public static function get_all_user_applications ()
	{
		$query = "select id, concat(first_name, ' ', last_name) as full_name, application_filed_time from user_application order by application_filed_time desc";
		$values = Array();
		return db::select($query, $values);
	}

	public static function get_user_application ($id)
	{
		$query = "select *, concat(first_name, ' ', last_name) as full_name from user_application where id = ?";
		$values = Array($id);
		return db::select_single_row($query, $values);
	}

	public static function delete_user_application ($id)
	{
		$query = "delete from user_application where id = ?";
		$values = Array($id);
		return db::delete($query, $values);
	}

	public static function get_first_name_from_activation_code ($activation_code)
	{
		$query = "select first_name from user where activation_code = ?";
		$values = Array($activation_code);
		return db::select_single_value($query, $values);
	}

	public static function activate_user ($user_id)
	{
		$user_data = self::get_user_data($user_id);

		// Adding forum accesses for new user
		$public_forums = db_forum::get_public_forum_ids();
		foreach($public_forums as $row)
			db_forum_admin::add_forum_access($user_id, $row['id']);
		$local_county_forum = db_forum::get_local_county_forum($user_data['county_id']);
		db_forum_admin::add_forum_access($user_id, $local_county_forum);
		$local_region_forum = db_forum::get_local_region_forum($user_data['region_id']);
		db_forum_admin::add_forum_access($user_id, $local_region_forum);

		// Adding constituency access for new user
		$public_constituencies = db_constituency::get_public_constituency_ids();
		foreach($public_constituencies as $row)
			db_constituency::add_constituency_access($user_id, $row['id']);
		db_constituency::add_constituency_access($user_id, $user_data['county_id']);
		db_constituency::add_constituency_access($user_id, $user_data['region_id']);

		$query = "update user set activation_code = ?, activation_time = ?, first_name = activation_first_name, last_name = activation_last_name where id = ?";
		$values = Array(null, time(), $user_id);
		return db::update($query, $values);
	}

	public static function get_activation_code_from_email ($user_email)
	{
		$query = "select activation_code from user where email = ?";
		$values = Array($user_email);
		return db::select_single_value($query, $values);
	}

	public static function is_user_active ($user_id){
		$query = "select activation_code from user where id = ?";
		$values = Array($user_id);
		$result = db::select_single_value($query, $values);
		if(empty($result)){
			return true;
		}
		else{
			return false;
		}
	}

	public static function get_membership_until ($user_id)
	{
		$query = "select membership_fee_payed_until from user where id = ?";
		$values = Array($user_id);
		return db::select_single_value($query, $values);
	}

	public static function check_if_personnummer_exists ($personnummer, $exclude_user_id = 0)
	{
		return self::check_if_key_property_exists('social_security_number', $personnummer, $exclude_user_id);
	}

		public static function check_if_email_exists ($email, $exclude_user_id = 0)
	{
		return self::check_if_key_property_exists('email', $email, $exclude_user_id);
	}

	private static function check_if_key_property_exists ($property_name, $value, $exclude_user_id)
	{
		$query = "select * from user where " . $property_name . " = ? 
		and deletion_time is null
		and id <> ?";
		$values = Array($value, $exclude_user_id);
		$user_result = db::select($query, $values);
		$query = "select * from user_application where " . $property_name . " = ?";
		$values = Array($value);
		$user_application_result = db::select($query, $values);
		return $user_result || $user_application_result;
	}
} 