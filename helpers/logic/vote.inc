<?php
namespace Logic;

class vote 
{
	private static $vote_types = array("yes-no", "prio-vote", "candidate-election", "median", "budget");
	private static $mandatory_properties = array("vote_id", "type_of_vote", "constituency_id", "forum_topic_id", "title");
	private static $time_properties = array("year", "month", "day", "hour", "minute", "delegate_year", "delegate_month", "delegate_day", "delegate_hour", "delegate_minute");

	public static function get_vote_types() 
	{
		return self::$vote_types;
	}

	public static function change_vote() 
	{
		self::validate_change_vote_input();
		$current_constituency = \db_vote::get_constituency_id_for_vote($_POST['vote_id']);
		$constituency_changed = $current_constituency != $_POST['constituency_id']
			&& \db_vote_admin::change_constituency($_POST['constituency_id'], $_POST['vote_id']);
		$vote_changed = \db_vote_admin::update_vote($_POST['type_of_vote'], $_POST['title'], $_POST['description'], $_POST['forum_topic_id'], $_POST['vote_id']);
		$vote_time_changed = self::is_all_vote_time_properties_set() && self::change_vote_end_time();
		if(!($constituency_changed || $vote_changed || $vote_time_changed))
			throw new \Exception("Databasfel. Ingen uppdatering gjord.");
		$_SESSION['report_message'] = "Omröstningen är uppdaterad.";
	}

	public static function change_vote_property() {
		$vote_id = $_GET['id'];
		$voteinfo = db_vote::get_vote_info($vote_id);
		$status = $voteinfo['status'];
		$action = $_POST['action'];
		$ok = self::invoke_action($vote_id, $status, $action);
		if(!$ok) 
			throw new Exception("Databasfel. Ingen ändring gjord.");
		self::invoke_post_action($vote_id, $status, $action);
		$_SESSION['report_message'] = "Omröstningen är ändrad.";
	}

	private static $valid_actions_by_status = array(
		'active' => array('end_vote', 'end_delegate_vote', 'make_continuous'),
		'del_ended' => array('end_vote', 'restore_delegate_vote'),
		'ended' => array('restore_vote'),
		'continuous' => array('finish_vote', 'make_active'),
		'finished' => array('restore_finished_vote'),
	); 

	private static function invoke_action($vote_id, $status, $action) {
		if (!self::is_action_valid_for_status($action, $status))
			throw new Exception('Invalid action: ' . $action . ' for status: ' . $status);
		switch ($action) {
			case 'end_vote':
				return \db_vote_admin::end_vote($vote_id);
			case 'end_delegate_vote':
				return \db_vote_admin::end_delegate_vote($vote_id);
			case 'restore_vote':
				return \db_vote_admin::restore_vote($vote_id);
			case 'finish_vote':
				return \db_vote_admin::finish_vote($vote_id);
			case 'restore_finished_vote':
				return \db_vote_admin::restore_finished_vote($vote_id);
			case 'make_continuous':
				return \db_vote_admin::make_continuous($vote_id);
			case 'make_active':
				return \db_vote_admin::make_active($vote_id);
			default:
				throw new Exception("Invalid action: " . $action);
		}
	}

	private static function invoke_post_action($vote_id, $action) {
		switch ($action) {
			case 'end_vote':
			case 'finish_vote':
				\vote_helpers::substitute_active_for_passive_user_codes($vote_id);
				break;
			case 'restore_vote':
			case 'restore_finished_vote':
				\vote_helpers::restore_active_user_codes($vote_id);
				break;
		}
	}

	private static function is_action_valid_for_status($action, $status) {
		$valid_actions = self::$valid_actions_by_status[$status];
		return in_array($action, $valid_actions);
	}

	private static function change_vote_end_time() 
	{
		$time_string = self::generate_time_string();
		$delegate_time_string = self::generate_time_string('delegate_');
		$timestamp_ended = strtotime($time_string);
		$timestamp_delegate_ended = strtotime($delegate_time_string);
		return \db_vote_admin::update_time_ended($timestamp_ended, $timestamp_delegate_ended, $_POST['vote_id']);
	}

	private static function generate_time_string($prefix = '') 
	{
		return $_POST[$prefix . 'year'] . "-" . $_POST[$prefix . 'month'] . "-" . $_POST[$prefix . 'day'] . " " . $_POST[$prefix . 'hour'] . ":" . $_POST[$prefix . 'minute'] . ":00";
	}

	private static function validate_change_vote_input() 
	{
		if(!self::is_all_mandatory_vote_properties_set()) {
			throw new \Exception("Värde saknas i något av de obligatoriska fälten");
		}
		if($_POST['vote_id'] != $_GET['id'])
			throw new \Exception("Något gick fel. Den uppdaterade omröstningens id matchar inte den aktuella omröstningen.");
		if(!\db_constituency::check_that_constituency_exists($_POST['constituency_id']))
			throw new \Exception("Valkretsfel. Ingen ändring gjord.");
		if(!in_array($_POST['type_of_vote'], \Logic\vote::get_vote_types()))
			throw new \Exception("Fel omröstningstyp. Ingen ändring gjord.");
	}

	private static function is_all_mandatory_vote_properties_set() 
	{
		return util::is_all_set(self::$mandatory_properties, $_POST);
	}

	private static function is_all_vote_time_properties_set() 
	{
		return util::is_all_set(self::$time_properties, $_POST);
	}
}
