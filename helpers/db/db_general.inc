<?php

class db_general 
{
	// NOTE: This db function does not utilise full parametrised input due to bug in current MySQL that doesn't allow parametrised input in limit clause. Variables are instead sanitised by casting as int. When this bug is resolved, this function can be corrected. 
	public static function get_limit_clause ($page = 1, $limit = POSTS_PER_PAGE){
		$page = (int)$page;
		$limit = (int)$limit;
		$offset = ($page-1) * $limit;
		return "limit " . $offset . ", " . $limit;
	}

	public static function make_hash($rows, $key, $value) {
		$hash = array();
		foreach($rows as $row) {
			$hash[$row[$key]] = $row[$value];
		}
		return $hash;
	}

	public static function create_voter($voter_type) {
		if ($voter_type != 'user' && $voter_type != 'delegate')
			throw new \Exception("Invalid voter_type: " . $voter_type);
		$query = "insert into voter (voter_type) values (?)";
		$values = array($voter_type);
		return db::insert($query, $values);
	}

	public static function delete_voter($voter_id) {
		$query = "delete from voter where id = ?";
		$values = array($voter_id);
		return db::delete($query, $values);
	}

	public static function get_order_by ($sortable_columns, $default_sort = 1, $sort = 0)
	{
		if ($sort == 0) $sort = $default_sort;
		$direction = $sort > 0 ? " asc" : " desc";
		$sort_column = $sortable_columns[abs($sort) - 1];
		if (starts_with($sort_column, "null"))
			return self::get_order_by($sortable_columns, $default_sort);
		$column_and_alias = explode(" as ", $sort_column);
		return end($column_and_alias) . $direction;
	}	
}