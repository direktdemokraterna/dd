<?php

class db_user {
	
	public static function add_user ($username, $password, $first_name, $last_name, $street_address, $zip_code, $city_address, $county, $region, $social_security_number, $email, $skype_name){

		$query = "insert into users (username, password, registration_time, first_name, last_name, street_address, zip_code, city_address, county, region, social_security_number, email, skype_name) values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

		$registration_time = time();

		$values = Array($username, $password, $registration_time, $first_name, $last_name, $street_address, $zip_code, $city_address, $county, $region, $social_security_number, $email, $skype_name);

		$user_id = db::insert($query, $values);

		$public_forums = db_forum::get_public_forum_ids();

		$query = "insert into forums_users (forum_id, user_id) values (?, " . $user_id . ")";

		db::insert_all($query, $public_forums);

		return $user_id;

	}

	public static function get_all_users ($page = 0, $limit = LIST_ITEMS_PER_PAGE, $order_by = "last_activity_time desc", $where_filter = "1=1"){
// NOTE: This db function does not utilise full parametrised input due to bug in current MySQL that doesn't allow parametrised input in limit clause. Variables are instead sanitised by casting as int. When this bug is resolved, this function can be corrected. 

		$page = (int)($page-1) * $limit;
		$limit = (int)$limit;

		$query = "select id, concat(first_name, ' ', last_name) as full_name from users where " . $where_filter . " order by " . $order_by . " limit " . $page . ", " . $limit;
		$values = Array();

		return db::select($query, $values);

	}

	public static function get_all_users_count ($where_filter = "1=1"){

		$query = "select count(*) from users where " . $where_filter;
		$values = Array();

		return db::select_single_value($query, $values);

	}

	public static function get_user_data ($id){

		$query = "select *, concat(first_name, ' ', last_name) as full_name from users where id = ?";
		$values = Array($id);

		return db::select_single_row($query, $values);

	}

	public static function get_password ($id){

		$query = "select password from users where id = ?";
		$values = Array($id);

		return db::select_single_value($query, $values);

	}

	public static function get_user_data_from_username ($username){

		$query = "select * from users where username = ?";
		$values = Array($username);

		return db::select_single_row($query, $values);

	}

	public static function update_last_activity_time ($user_id){

		$query = "update users set last_activity_time = ? where id = ?";
		$values = Array(time(), $user_id);

		return db::update($query, $values);

	}

	public static function update_last_login_time ($user_id){

		$query = "update users set last_login_time = ? where id = ?";
		$values = Array(time(), $user_id);

		return db::update($query, $values);

	}

	public static function update_password ($password_hash, $id){

		$query = "update users set password = ? where id = ?";
		$values = Array($password_hash, $id);

		return db::update($query, $values);

	}

	public static function update_image ($image, $id){

		$query = "update users set image = ? where id = ?";
		$values = Array($image, $id);

		return db::update($query, $values);

	}

	public static function update_settings ($show_email, $show_telephone, $show_skype, $id){

		$query = "update users set show_email = ?, show_telephone = ?, show_skype = ? where id = ?";
		$values = Array($show_email, $show_telephone, $show_skype, $id);

		return db::update($query, $values);

	}

	public static function update_profile ($first_name, $last_name, $street_address, $zip_code, $city_address, $county, $region, $email, $skype_name, $telephone1, $telephone2, $id){

		$query = "update users set first_name = ?, last_name = ?, street_address = ?, zip_code = ?, city_address = ?, county = ?, region = ?, email = ?, skype_name = ?, telephone1 = ?, telephone2 = ? where id = ?";
		$values = Array($first_name, $last_name, $street_address, $zip_code, $city_address, $county, $region, $email, $skype_name, $telephone1, $telephone2, $id);

		return db::update($query, $values);

	}

	public static function update_description ($description, $id){

		$query = "update users set description = ? where id = ?";
		$values = Array($description, $id);

		return db::update($query, $values);

	}

	public static function update_user_by_admin ($username, $first_name, $last_name, $street_address, $zip_code, $city_address, $county, $region, $social_security_number, $email, $skype_name, $telephone1, $telephone2, $id){

		$query = "update users set username = ?, first_name = ?, last_name = ?, street_address = ?, zip_code = ?, city_address = ?, county = ?, region = ?, social_security_number = ?, email = ?, skype_name = ?, telephone1 = ?, telephone2 = ? where id = ?";
		$values = Array($username, $first_name, $last_name, $street_address, $zip_code, $city_address, $county, $region, $social_security_number, $email, $skype_name, $telephone1, $telephone2, $id);

		return db::update($query, $values);

	}

	public static function get_username ($user_id){

		$query = "select username from users where id = ?";
		$values = Array($user_id);

		return db::select_single_value($query, $values);

	}

	public static function get_user_id ($username){

		$query = "select id from users where username = ?";
		$values = Array($username);

		return db::select_single_value($query, $values);

	}

	public static function get_user_full_name ($user_id){

		$query = "select concat(first_name, ' ', last_name) as full_name from users where id = ?";
		$values = Array($user_id);

		return db::select_single_value($query, $values);

	}

	public static function get_public_forum_ids (){

		$query = "select id from users";
		$values = Array();

		return db::select($query, $values);

	}

	public static function set_remember_me_token ($remember_me_token, $id){

		$query = "update users set remember_me_token = ? where id = ?";
		$values = Array($remember_me_token, $id);

		return db::update($query, $values);

	}

	public static function get_all_user_ids (){

		$query = "select id from users";
		$values = Array();

		return db::select($query, $values);

	}

	public static function search_users ($search, $page = 0, $limit = LIST_ITEMS_PER_PAGE){
// NOTE: This db function does not utilise full parametrised input due to bug in current MySQL that doesn't allow parametrised input in limit clause. Variables are instead sanitised by casting as int. When this bug is resolved, this function can be corrected. 

		$page = (int)($page-1) * $limit;
		$limit = (int)$limit;

		$query = "select id, concat(first_name, ' ', last_name) as full_name from users 
					where match(first_name, last_name, description) against (? in boolean mode) 
					limit " . $page . ", " . $limit;
		$values = Array($search);

		return db::select($query, $values);

	}

} 