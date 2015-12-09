<?php
class db_user 
{
	public static function add_user ($username, $password, $first_name, $last_name, $street_address, $zip_code, $city_address, $county, $region, $social_security_number, $email, $skype_name = "")
	{
		$query = "insert into user (username, password, registration_time, first_name, last_name, street_address, zip_code, city_address, county, region, social_security_number, email, skype_name) values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
		$values = Array($username, $password, time(), $first_name, $last_name, $street_address, $zip_code, $city_address, $county, $region, $social_security_number, $email, $skype_name);
		$user_id = db::insert($query, $values);
		if(!$user_id)
			return false;

		// Adding forum accesses for new user
		$public_forums = db_forum::get_public_forum_ids();
		foreach($public_forums as $row)
			db_forum_admin::add_forum_access($user_id, $row['id']);
		$local_county_forum = db_forum::get_local_county_forum($_POST['county']);
		db_forum_admin::add_forum_access($user_id, $local_county_forum);
		$local_region_forum = db_forum::get_local_region_forum($region);
		db_forum_admin::add_forum_access($user_id, $local_region_forum);

		// Adding constituency access for new user
		$public_constituencies = db_constituency::get_public_constituency_ids();
		foreach($public_constituencies as $row)
			db_constituency::add_constituency_access($user_id, $row['id']);
		$local_county_constituency = db_constituency::get_local_county_constituency($_POST['county']);
		db_constituency::add_constituency_access($user_id, $local_county_constituency);
		$local_region_constituency = db_constituency::get_local_region_constituency($region);
		db_constituency::add_constituency_access($user_id, $local_region_constituency);
		return $user_id;
	}

	public static function get_all_users ($page = 1, $limit = LIST_ITEMS_PER_PAGE, $order_by = "last_activity_time desc", $where_filters)
	{
		$where_clause = self::create_where_clause($where_filters);
		$limit_clause = db_general::get_limit_clause($page, $limit);
		$query = "select id, concat(first_name, ' ', last_name) as full_name, deletion_time from user" . $where_clause . " order by " . $order_by . " " . $limit_clause;
		$values = Array();
		return db::select($query, $values);
	}

	public static function get_all_users_count ($where_filters)
	{
		$where_clause = self::create_where_clause($where_filters);
		$query = "select count(*) from user" . $where_clause;
		$values = Array();
		return db::select_single_value($query, $values);
	}

	public static function create_where_clause ($where_filters)
	{
		return $where_filters ? " where " . implode(" and ", $where_filters) : "";
	}

	public static function get_user_data ($id)
	{
		return self::get_user_data_from("id = ?", array($id));
	}

	public static function get_password ($id)
	{
		$query = "select password from user where id = ?";
		$values = Array($id);
		return db::select_single_value($query, $values);
	}

	public static function get_user_data_from_username ($username)
	{
		return self::get_user_data_from("username = ?", array($username));
	}
	
	private static function get_user_data_from ($condition, $values)
	{
		$query = "select *, concat(first_name, ' ', last_name) as full_name
		 from user where " . $condition;
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

	public static function update_profile ($first_name, $last_name, $street_address, $zip_code, $city_address, $county, $region, $email, $skype_name, $telephone1, $telephone2, $id)
	{
		$query = "update user set first_name = ?, last_name = ?, street_address = ?, zip_code = ?, city_address = ?, county = ?, region = ?, email = ?, skype_name = ?, telephone1 = ?, telephone2 = ? where id = ?";
		$values = Array($first_name, $last_name, $street_address, $zip_code, $city_address, $county, $region, $email, $skype_name, $telephone1, $telephone2, $id);
		return db::update($query, $values);
	}

	public static function update_description ($description, $id)
	{
		$query = "update user set description = ? where id = ?";
		$values = Array($description, $id);
		return db::update($query, $values);
	}

	public static function update_user_by_admin ($username, $first_name, $last_name, $street_address, $zip_code, $city_address, $county, $region, $social_security_number, $email, $skype_name, $telephone1, $telephone2, $id)
	{
		$query = "update user set username = ?, first_name = ?, last_name = ?, street_address = ?, zip_code = ?, city_address = ?, county = ?, region = ?, social_security_number = ?, email = ?, skype_name = ?, telephone1 = ?, telephone2 = ? where id = ?";
		$values = Array($username, $first_name, $last_name, $street_address, $zip_code, $city_address, $county, $region, $social_security_number, $email, $skype_name, $telephone1, $telephone2, $id);
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

	public static function search_users ($search, $page = 1, $limit = LIST_ITEMS_PER_PAGE)
	{
		$limit_clause = db_general::get_limit_clause($page, $limit);
		$query = "select id, concat(first_name, ' ', last_name) as full_name from user 
					where match(first_name, last_name, description) against (? in boolean mode) 
					" . $limit_clause;
		$values = Array($search);
		return db::select($query, $values);
	}

	public static function enter_user_application ($first_name, $last_name, $street_address, $zip_code, $city_address, $county, $region, $social_security_number, $email, $telephone)
	{
		$query = "insert into user_application (application_filed_time, first_name, last_name, street_address, zip_code, city_address, county, region, social_security_number, email, telephone1) values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
		$values = Array(time(), $first_name, $last_name, $street_address, $zip_code, $city_address, $county, $region, $social_security_number, $email, $telephone);
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