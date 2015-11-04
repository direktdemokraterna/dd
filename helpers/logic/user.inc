<?php
namespace Logic;

class user 
{
	public static function validate_user($personnummer, $email, $exclude_user_id = 0) 
	{
		if(!\general_helpers::check_personnummer($personnummer))
			return "Ogiltigt personnummer";
		if(!filter_var($email, FILTER_VALIDATE_EMAIL))
			return "Ogiltig mejladress";
		if(\db_user::check_if_personnummer_exists($personnummer, $exclude_user_id))
			return "Det finns redan en användare med det personnumret";
		if(\db_user::check_if_email_exists($email, $exclude_user_id))
			return "Det finns redan en användare med den mejladressen";
	}
}
