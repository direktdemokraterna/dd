<?php

class db_calendar {

	public static function add_event ($timestamp, $year, $month, $day, $time, $user_id, $group, $title, $content){

		$query = "insert into calendar (timestamp, year, month, day, time, timestamp_added, added_by_user, location, title, content) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
		$values = Array($timestamp, $year, $month, $day, $time, time(), $user_id, $group, $title, $content);

		return db::insert($query, $values);

	}

	public static function get_event ($event_id){

		$query = "select c.id as event_id, c.time as time, c.timestamp_added as timestamp_added, c.added_by_user as user_id, concat(u.first_name, ' ', u.last_name) as full_name, c.			location as location, c.title as title, c.content as content, c.day as day, c.month as month, c.year as year, c.timestamp as timestamp 
					from calendar c, users u 
					where c.added_by_user = u.id and c.id = ?";
		$values = Array($event_id);

		return db::select_single_row($query, $values);

	}

	public static function get_events ($year, $month, $day){

		$query = "select c.id as event_id, c.time as time, c.timestamp_added as timestamp_added, c.added_by_user as user_id, concat(u.first_name, ' ', u.last_name) as full_name, c.location as 			location, c.title as title, c.content as content 
					from calendar c, users u 
					where c.added_by_user = u.id and c.year = ? and c.month = ? and c.day = ?";
		$values = Array($year, $month, $day);

		return db::select($query, $values);

	}

	public static function get_month ($year, $month){

		$query = "select c.time as time, c.timestamp_added as timestamp_added, c.added_by_user as added_by_user, concat(u.first_name, ' ', u.last_name) as full_name, c.location as 			location, c.title as title, c.content as content 
					from calendar c 
					where c.added_by_user = u.id and c.year = ? and c.month = ? and c.day = ?";
		$values = Array($year, $month, $day);

		return db::select($query, $values);

	}

	public static function get_participants ($event_id){

		$query = "select u.id as user_id, concat(u.first_name, ' ', u.last_name) as full_name 
					from users u, calendar_participants cp 
					where u.id = cp.user_id and cp.calendar_id = ?";
		$values = Array($event_id);

		return db::select($query, $values);

	}

	public static function is_participant ($event_id, $user_id){

		$query = "select id 
					from calendar_participants cp 
					where cp.calendar_id = ? and cp.user_id = ?";
		$values = Array($event_id, $user_id);

		$result = db::select($query, $values);

		if(empty($result)){
			return false;
		}
		else{
			return true;
		}

	}

	public static function participate ($event_id, $user_id){

		$db_table = "calendar_participants";
		$columns = Array("calendar_id", "user_id");
		$values = Array($event_id, $user_id);

		return db::insert_ignore($db_table, $columns, $values);

	}

	public static function cancel_participate ($event_id, $user_id){

		$query = "delete from calendar_participants where calendar_id = ? and user_id = ?";
		$values = Array($event_id, $user_id);

		return db::delete($query, $values);

	}

}