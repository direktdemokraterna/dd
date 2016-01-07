<?php
namespace Logic;

class user 
{
	public static function validate_user($personnummer, $email, $exclude_user_id = 0) 
	{
		if(!\general_helpers::check_personnummer($personnummer))
			return _t("Invalid social security number");
		if(!filter_var($email, FILTER_VALIDATE_EMAIL))
			return "Invalid email address";
		if(\db_user::check_if_personnummer_exists($personnummer, $exclude_user_id))
			return "There already exists a user with that social security number";
		if(\db_user::check_if_email_exists($email, $exclude_user_id))
			return "There already exists a user with that email address";
	}

	public static function delete_user ($user_id)
	{
		$ok = \db_user::delete_user ($user_id);
		if ($ok) {
			\Logic\delegate::delete_delegate_for_user($user_id);
			\Logic\vote::remove_ballots($user_id);
			\Logic\vote::remove_prop_ballots($user_id);
			\Logic\vote::remove_delegations($user_id);
		}
		return $ok;
	}

	public static function restore_user ($user_id)
	{
		return \db_user::restore_user ($user_id);
	}	
}
