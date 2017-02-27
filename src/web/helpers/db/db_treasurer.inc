<?php

class db_treasurer
{
	public static function add_account_entry ($type_of_transaction, $amount, $timestamp_accounting, $comment_from_bank, $comment_from_admin, $user_id = null)
	{
		$query = "insert into accounting (type_of_transaction, amount, timestamp_accounting, timestamp_insertion, user_id, comment_from_bank, comment_from_admin) values (?, ?, ?, ?, ?, ?, ?)";
		$values = Array($type_of_transaction, $amount, $timestamp_accounting, time(), $user_id, $comment_from_bank, $comment_from_admin);
		return db::insert($query, $values);
	}

	public static function get_all_account_entries ($page = 1, $limit = LIST_ITEMS_PER_PAGE)
	{
		$limit_clause = db_general::get_limit_clause($page, $limit);
		$query = "select id, type_of_transaction, amount, timestamp_accounting, timestamp_insertion, user_id, comment_from_bank, comment_from_admin from accounting";
		$values = Array();
		return db::select($query, $values);
	}

	public static function get_account_entries_for_user ($user_id)
	{
		$query = "select id, type_of_transaction, amount, timestamp_accounting, timestamp_insertion, user_id, comment_from_bank, comment_from_admin from accounting where user_id = ?";
		$values = Array($user_id);
		return db::select($query, $values);
	}

	public static function add_entry ($type_of_transaction, $amount, $timestamp_accounting, $user_id, $comment_from_bank, $comment_from_admin)
	{
		$query = "insert into accounting (type_of_transaction, amount, timestamp_accounting, timestamp_insertion, user_id, comment_from_bank, comment_from_admin) values (?, ?, ?, ?, ?, ?, ?)";
		$values = Array($type_of_transaction, $amount, $timestamp_accounting, time(), $user_id, $comment_from_bank, $comment_from_admin);
		return db::insert($query, $values);
	}

	public static function add_membership_fee ($timestamp_accounting, $user_id, $comment_from_bank, $comment_from_admin)
	{
		$query = "insert into accounting (type_of_transaction, amount, timestamp_accounting, timestamp_insertion, user_id, comment_from_bank, comment_from_admin) values (?, ?, ?, ?, ?, ?, ?)";
		$values = Array("medlemsavgift", MEMBERSHIP_FEE, $timestamp_accounting, time(), $user_id, $comment_from_bank, $comment_from_admin);
		$ok = db::insert($query, $values);
		if($ok){
			self::update_membership_fee_payment($user_id, $timestamp_accounting);
		}
		return $ok;
	}

	public static function days_since_last_memebership_payed_for_user ($user_id)
	{
		$query = "select timestamp_accounting from accounting where user_id = ? and type_of_transaction='medlemsavgift' order by timestamp_accounting desc limit 1";
		$values = Array($user_id);
		$timestamp_accounting = db::select_single_value($query, $values);
		if(!$timestamp_accounting) $timestamp_accounting = 0;
		return floor((time()-$timestamp_accounting)/(3600*24));
	}

	public static function update_membership_fee_payment ($user_id, $fee_payed, $time_added_to_membership = "+1 year")
	{
		$user_member_until = db_user::get_membership_until($user_id);
		if(!$user_member_until) $user_member_until = $fee_payed;
		$updated_user_member_until = strtotime($time_added_to_membership, $user_member_until);
		$query = "update user set membership_fee_last_payed = ?, membership_fee_payed_until = ? where id = ?";
		$values = Array($fee_payed, $updated_user_member_until, $user_id);
		return db::update($query, $values);
	}

}