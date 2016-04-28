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
}