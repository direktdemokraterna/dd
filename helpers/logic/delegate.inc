<?php
namespace Logic;

class delegate 
{
	public static function delete_delegate_for_user ($user_id)
	{
		$delegate_id = db_delegate::get_delegate_id_from_user_id($user_id);
		self::delete_delegate($delegate_id);
	}

	public static function delete_delegate ($delegate_id)
	{
		\Logic\vote::remove_delegate_ballots($delegate_id);
		\Logic\vote::remove_delegate_prop_ballots($delegate_id);
		\Logic\vote::remove_delegate_delegations($delegate_id);
		\db_constituency::remove_constituency_access($delegate_id);
		\db_delegate::delete_delegate($delegate_id);
	}	
}
