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
}