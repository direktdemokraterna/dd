<?php
class db 
{
	public static function connect ()
	{
		global $conn;
		if($conn){
			return $conn;
		}
		else{
			$data_source = "mysql:host=" . DB_HOST . ";dbname=" . DB_NAME;
			$conn = new PDO($data_source, DB_USERNAME, DB_PASSWORD,array(PDO::MYSQL_ATTR_INIT_COMMAND => 'SET NAMES utf8'));
			$conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
			$conn->setAttribute(PDO::ATTR_EMULATE_PREPARES, false);
			return $conn;
		}
	}

	// returns a result array from a select query
	public static function select ($query, $values)
	{
		$db = self::connect();
		$stmt = $db->prepare($query);
		$stmt->execute($values);
		return $stmt->fetchAll();
	}

	// returns a result array from a select query with result in a associative array only
	public static function select_associative ($query, $values)
	{
		$db = self::connect();
		$stmt = $db->prepare($query);
		$stmt->execute($values);
		return $stmt->fetchAll(PDO::FETCH_ASSOC);
	}

	// returns a sequential only result array from a select query
	public static function select_sequential_array ($query, $values)
	{
		$db = self::connect();
		$stmt = $db->prepare($query);
		$stmt->execute($values);
		return $stmt->fetchAll(PDO::FETCH_COLUMN, 0);
	}

	// returns single value from a select query
	public static function select_single_value ($query, $values)
	{
		$db = self::connect();
		$stmt = $db->prepare($query);
		$stmt->execute($values);
		$result = $stmt->fetchAll();
		return empty($result) ? false : $result[0][0];
	}

	// returns single row from a select query
	public static function select_single_row ($query, $values)
	{
		$db = self::connect();
		$stmt = $db->prepare($query);
		$stmt->execute($values);
		$result = $stmt->fetchAll(PDO::FETCH_ASSOC);
		return empty($result) ? false : $result[0];
	}

	// executes an insert query, returns insert_id
	public static function insert ($query, $values)
	{
		$db = self::connect();
		$stmt = $db->prepare($query);
		$stmt->execute($values);
		return $db->lastInsertId();
	}

	// executes an update query, returns number of affected rows
	public static function update ($query, $values)
	{
		return self::execute($query, $values);
	}

	public static function update_from_array ($query, $id_array)
	{
		$db = self::connect();
		$stmt = $db->prepare($query);
		$counter = 0;
		foreach($id_array as $id_value){
			$values = Array($id_value);
			$stmt->execute($values);
			$counter++;
		}
		return $counter;
	}

	public static function delete ($query, $values)
	{
		return self::execute($query, $values);
	}

	public static function execute ($query, $values)
	{
		$db = self::connect();
		$stmt = $db->prepare($query);
		$stmt->execute($values);
		return $stmt->rowCount();
	}

	public static function insert_multiple_rows_with_two_variables ($query, $variable_array, $second_variable)
	{
		$db = self::connect();
		$stmt = $db->prepare($query);
		$counter = 0;
		foreach($variable_array as $first_variable){
			$values = Array($first_variable, $second_variable);
			$stmt->execute($values);
			$counter += $stmt->rowCount();
		}		
		return $counter;
	}

	public static function insert_ignore_from_array ($query, $variable_array, $second_variable)
	{
		$db = self::connect();
		$stmt = $db->prepare($query);
		$counter = 0;
		foreach($variable_array as $first_variable){
			$values = Array($first_variable, $second_variable, $first_variable, $second_variable);
			$stmt->execute($values);
			$counter += $stmt->rowCount();
		}
		return $counter;
	}

	public static function insert_ignore ($db_table, $columns, $values)
	{
		$db = self::connect();
		$select_statement = "";
		foreach ($columns as $value)
			$select_statement = $select_statement . " and " . $value . " = ?";
		$select_statement = trim($select_statement, " and");
		$query = "select count(*) from " . $db_table . " where " . $select_statement;
		$if_exists = self::select_single_value($query, $values);
		if(!empty($if_exists))
			return false;
		$question_marks = "";
		foreach ($columns as $value)
			$question_marks = $question_marks . ", ?";
		$question_marks = trim($question_marks, ",");
		$query = "insert into " . $db_table . "(" . implode(",", $columns) . ") values(" . $question_marks . ")";
		return self::insert($query, $values);
	}

	public static function insert_all ($query, $insert_array)
	{
		$db = self::connect();
		$stmt = $db->prepare($query);
		$counter = 0;
		foreach($insert_array as $row){
			$values = Array($row[0]);
			$stmt->execute($values);
			$counter = $counter + $stmt->rowCount();
		}
		return $counter;
	}

	// transaction functions
	public static function begintransaction()
	{
		$db = self::connect();
		return $db->beginTransaction();
	}

	public static function commit()
	{
		$db = self::connect();
		return $db->commit();
	}

	public static function rollback()
	{
		$db = self::connect();
		return $db->rollBack();
	}
}