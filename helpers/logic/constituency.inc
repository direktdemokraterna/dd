<?php
namespace Logic;

class constituency 
{
	public static function update_constituencies_for_user($constituency_ids, $user_id)
	{
		$old_constituencies = \db_constituency::get_constituency_ids_for_voter($user_id);
		$removed_constituencies = array_diff($old_constituencies, $constituency_ids);
		$chg_cnt = self::add_constituency_access($constituency_ids, $old_constituencies, $user_id);
		foreach($removed_constituencies as $removed_constituency)
			$chg_cnt += self::remove_constituency_access_for_user($user_id, $removed_constituency);
		return $chg_cnt;
	}

	public static function update_constituencies_for_delegate($constituency_ids, $user_id)
	{
		$delegate_id = \db_delegate::get_delegate_id_from_user_id($user_id);
		$old_constituencies = \db_constituency::get_constituency_ids_for_voter($delegate_id);
		$removed_constituencies = array_diff($old_constituencies, $constituency_ids);
		$chg_cnt = self::add_constituency_access($constituency_ids, $old_constituencies, $delegate_id);
		foreach($removed_constituencies as $removed_constituency)
			$chg_cnt += self::remove_constituency_access_for_delegate($delegate_id, $removed_constituency);
		return $chg_cnt;
	}

	public static function update_county_region_constituencies ($user_id, $county_id)
	{
		$old_county_constituency_id = \db_constituency::get_local_county_constituency_for_user($user_id);
		if ($old_county_constituency_id != $county_id) {
			self::remove_constituency_access_for_user($user_id, $old_county_constituency_id);
			db_constituency::add_constituency_access($user_id, $county_id);
			$old_region_constituency_id = db_constituency::get_local_region_constituency_for_user($user_id);
			if ($old_county_constituency_id != $county_id) {
				$new_region_id = db_constituency::get_region_id_from_county_id($county_id);
				self::remove_constituency_access($user_id, $old_region_constituency_id);
				db_constituency::add_constituency_access($user_id, $new_region_constituency_id);
			}
		}
	}	

	public static function add_constituency_access($current_constituency_ids, $old_constituencies
		, $voter_id)
	{
		$chg_cnt = 0;
		$added_constituencies = array_diff($current_constituency_ids, $old_constituencies);
		foreach($added_constituencies as $added_constituency)
			$chg_cnt += \db_constituency::add_constituency_access($voter_id, $added_constituency);
		return $chg_cnt;
	}

	private static function remove_constituency_access_for_user($user_id, $constituency_id)
	{
		\Logic\vote::remove_ballots($user_id, $constituency_id);
		\Logic\vote::remove_prop_ballots($user_id, $constituency_id);
		\Logic\vote::remove_delegations($user_id, $constituency_id);
		$delegate_id = \db_delegate::get_delegate_id_from_user_id($user_id);
		if ($delegate_id)
			self::remove_constituency_access_for_delegate($delegate_id, $constituency_id);
		return \db_constituency::remove_constituency_access($user_id, $constituency_id);
	}

	private static function remove_constituency_access_for_delegate($delegate_id, $constituency_id)
	{
		\Logic\vote::remove_delegate_ballots($delegate_id, $constituency_id);
		\Logic\vote::remove_delegate_delegations($delegate_id, $constituency_id);
		return \db_constituency::remove_constituency_access($delegate_id, $constituency_id);
	}
}
