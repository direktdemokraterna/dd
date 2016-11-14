<?php
namespace Logic;

class vote 
{
	private static $vote_types = array("yes-no", "prio-vote", "candidate-election", "median", "budget");
	private static $mandatory_change_vote_properties = array("vote_id", "type_of_vote", "constituency_id", "forum_topic_id", "title", "description");
	private static $mandatory_admin_create_vote_properties = array("type_of_vote", "constituency_id", "vote_status", "title", "description");
	private static $time_properties = array("year", "month", "day", "hour", "minute", "delegate_year", "delegate_month", "delegate_day", "delegate_hour", "delegate_minute");

	public static function get_vote_types() 
	{
		return self::$vote_types;
	}

	public static function change_vote() 
	{
		self::validate_input_for_update(self::$mandatory_change_vote_properties);
		$current_constituency = \db_vote::get_constituency_id_for_vote($_POST['vote_id']);
		$constituency_changed = $current_constituency != $_POST['constituency_id']
			&& \db_vote_admin::change_constituency($_POST['constituency_id'], $_POST['vote_id']);
		$vote_changed = \db_vote_admin::update_vote($_POST['type_of_vote'], $_POST['title'], $_POST['description'], $_POST['forum_topic_id'], $_POST['vote_id']);
		$vote_time_changed = util::is_all_set(self::$time_properties, $_POST) && self::change_vote_end_time();
		if(!($constituency_changed || $vote_changed || $vote_time_changed))
			throw new \Exception(_t("No change made."));
		$_SESSION['report_message'] = _t("The vote is updated.");
	}

	public static function change_vote_property() {
		$vote_id = $_GET['id'];
		$voteinfo = \db_vote::get_vote_info($vote_id);
		$status = $voteinfo['status'];
		$action = $_POST['action'];
		$ok = self::invoke_action($vote_id, $status, $action);
		if(!$ok)
			throw new \Exception(_t("Database error. No change made."));
		$_SESSION['report_message'] = _t("The vote is updated.");
	}

	public static function admin_create_vote() {
		self::validate_input(self::$mandatory_admin_create_vote_properties);
		$ok = $_POST['vote_status'] == "active"
			? self::admin_create_time_limited_vote()
			: self::admin_create_continuous_vote();
		if(!$ok)
			throw new \Exception(_t("Something went wrong. No vote created."));
		$_SESSION['report_message'] = _t("The vote is created.");
		$redirect = "index.php?type=vote&action=view_vote&id=" . $ok;		// todo: redirect not used
	}

	public static function update_proposition_support($prop_id, $ballot) 
	{
		$prop_info = \db_prop::get_prop_info($prop_id);

		if($_SESSION['delegate_id'])
			$delegate_constituency_access = \db_constituency::check_voter_constituency_access($_SESSION['delegate_id'], $prop_info['constituency_id']);
		if(!empty($delegate_constituency_access) && $prop_info['status'] == "pending"){
			$ballot_decoded = \json_decode($ballot, true);
			$ok = \db_delegate::register_prop_ballot($prop_id, $_SESSION['delegate_id'], $ballot_decoded['support']);

			if($ok)
				$_SESSION['report_message'] = _t("Your delegate's ballot is registered.")." in register_prop_ballot";
			else
				throw new \Exception(_t("Something went wrong. The ballot was not registered."));
		}
		elseif($prop_info['status'] == "pending"){
			$check_user_access = \db_constituency::check_voter_constituency_access($_SESSION['id'], $prop_info['constituency_id']);
			if($check_user_access){
				$post_vars = Array("user_id" => $_SESSION['id'], "prop_id" => $prop_id, "ballot" => $ballot);

				$reply = \crypt_helpers::curl_to_anon_server("anonymise_prop_ballot.php", $post_vars);

				if(mb_stristr($reply , "success"))
					$_SESSION['report_message'] = _t("Your ballot is registered.");
				else
					throw new \Exception(_t("Something went wrong. The ballot was not registered.")." in anonymise_prop_ballot");
			}
			else
				die("no constituency access");
		}		
	}

	public static function is_active_vote($vote_status) {
		return in_array($vote_status, $_SESSION['delegate_id'] 
			? array("active", "continuous")
			: array("active", "continuous", "del_ended"));
	}

	public static function remove_ballots($user_id, $constituency_id = null) {
		//\db_vote::remove_ballots('iiT8ol4mWekOXkSOdPPO', null, null, $constituency_id);
		//return;
		$post_vars = array("user_id" => $user_id, "constituency_id" => $constituency_id);
		$reply = \crypt_helpers::curl_to_anon_server("remove_ballots.php", $post_vars);
		if(!mb_stristr($reply , "success"))
			throw new \Exception('Failed to remove ballots with reply: ' . $reply);
	}

	public static function remove_prop_ballots($user_id, $constituency_id = null) {
		$post_vars = Array("user_id" => $user_id, "constituency_id" => $constituency_id);
		$reply = \crypt_helpers::curl_to_anon_server("remove_prop_ballots.php", $post_vars);
		if(!mb_stristr($reply , "success"))
			throw new \Exception('Failed to remove prop ballots with reply: ' . $reply);
	}

	public static function remove_delegations($user_id, $constituency_id = null) {
		$post_vars = Array("user_id" => $user_id, "constituency_id" => $constituency_id);
		$reply = \crypt_helpers::curl_to_anon_server("remove_delegations.php", $post_vars);
		if(!mb_stristr($reply , "success"))
			throw new \Exception('Failed to remove delegations with reply: ' . $reply);
	}

	public static function remove_delegate_ballots($delegate_id, $constituency_id = null) {
		\db_delegate::remove_delegated_ballots(null, $delegate_id, null, $constituency_id);
	}

	public static function remove_delegate_delegations($delegate_id, $constituency_id = null) {
		\db_delegate::remove_delegations_for(null, $delegate_id, null, $constituency_id);
		\db_delegate::remove_delegations_for(null, null, $delegate_id, $constituency_id);
	}

	public static function get_vote_groups($statuses = null) 
	{
		$user_id = $_SESSION['id'];
		$page = isset($_GET['page']) ? $_GET['page'] : 1;
		$sort = isset($_GET['sort']) ? $_GET['sort'] : 0;
		$votes = \db_vote::list_votes($user_id, $sort, $page, $statuses);
		return self::group_by_constituency($votes);
	}

	public static function get_prop_groups($status) 
	{
		$user_id = $_SESSION['id'];
		$page = isset($_GET['page']) ? $_GET['page'] : 1;
		$sort = isset($_GET['sort']) ? $_GET['sort'] : 0;
		$props = \db_prop::list_props($status, $user_id, $sort, $page);
		return self::group_by_constituency($props);
	}

	public static function group_by_constituency($rows) 
	{
		$groups = array();
		foreach ($rows as $row) {
			$group = self::get_vote_group($groups, $row["constituency"]);
			$group->add_vote($row);
		}
		return $groups;
	}

	private static function &get_vote_group(&$vote_groups, $constituency) 
	{
		if (array_key_exists($constituency, $vote_groups)) {
			return $vote_groups[$constituency];
		}
		$vote_group = \Vote_group::create();
		$vote_groups[$constituency] = $vote_group;
		return $vote_group;
	}

	private static function admin_create_time_limited_vote() {
		$forum_topic_id = self::create_vote_topic();
		$time_string = self::generate_time_string(); 
		$timestamp_ended = strtotime($time_string);
		$timestamp_delegate_ended = ($timestamp_ended - time()) / 2 + time();
		return self::create_vote($forum_topic_id, $timestamp_ended, $timestamp_delegate_ended);
	}

	private static function admin_create_continuous_vote() {
		$forum_topic_id = self::create_vote_topic();
		return self::create_vote($forum_topic_id);
	}

	private static function create_vote($forum_topic_id, $timestamp_ended = null, $timestamp_delegate_ended = null) {
		return \db_vote_admin::create_vote($_POST['type_of_vote'], $_POST['vote_status'], $_POST['constituency_id'], \general_helpers::clean($_POST['title']), \general_helpers::clean($_POST['description']), $forum_topic_id, $timestamp_ended, $timestamp_delegate_ended); 
	}

	private static function create_vote_topic() {
		$forum_id = \db_constituency::get_constituency_forum_id($_POST['constituency_id']);
		$forum_topic_id = \db_forum::new_topic($_SESSION['id'], $forum_id, $_POST['title']);
		\db_forum::add_content_to_post($forum_topic_id, $_POST['description']);
		return $forum_topic_id;
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
			throw new \Exception('Invalid action: ' . $action . ' for status: ' . $status);
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
			case 'restore_delegate_vote':
				return \db_vote_admin::restore_delegate_vote($vote_id);
			default:
				throw new \Exception(_t("Invalid action: ") . $action);
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
		self::validate_time($_POST[$prefix . 'year']
			, $_POST[$prefix . 'month']
			, $_POST[$prefix . 'day']
			, $_POST[$prefix . 'hour']
			, $_POST[$prefix . 'minute']);
		return $_POST[$prefix . 'year'] . "-" . $_POST[$prefix . 'month'] . "-" . $_POST[$prefix . 'day'] . " " . $_POST[$prefix . 'hour'] . ":" . $_POST[$prefix . 'minute'] . ":00";
	}

	private static function validate_time($year, $month, $day, $hour, $minute) {
		self::validate_time_param('year', $year, 1970, 2999);
		self::validate_time_param('month', $month, 1, 12);
		self::validate_time_param('day', $day, 1, 31);
		self::validate_time_param('hour', $hour, 0, 23);
		self::validate_time_param('minute', $minute, 0, 59);
	}

	private static function validate_time_param($param_name, $time_param, $min, $max) {
		$ntime_param = (int)$time_param;
		if ($ntime_param < $min || $ntime_param > $max)
			throw new \Exception(_t("Invalid $param_name: $time_param"));
	}

	private static function validate_input_for_update($manatody_properties) 
	{
		self::validate_input($manatody_properties);
		if($_POST['vote_id'] != $_GET['id'])
			throw new \Exception(_t("Something went wrong. The updated vote's id doesn't match the current vote."));
	}

	private static function validate_input($mandatory_properties) 
	{
		if(!util::is_all_set($mandatory_properties, $_POST))
			throw new \Exception(_t("Value missing in one of the mandatory fields"));
		if(!\db_constituency::check_that_constituency_exists($_POST['constituency_id']))
			throw new \Exception(_t("Constituency missing. No change made."));
		if(!in_array($_POST['type_of_vote'], \Logic\vote::get_vote_types()))
			throw new \Exception(_t("Wrong vote type. No change made."));
	}
}
