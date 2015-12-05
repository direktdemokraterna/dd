<?php
namespace View;

class vote 
{
	public static function get_two_weeks_in_seconds() {
		return 14*24*3600;
	}

	public static function make_vote_type_selector($selected_option = null, $tab_index = 1) {
		$options = self::get_selectable_vote_type_descriptions();
		general::make_control_label("type_of_vote", _t("Type of vote"));
		general::make_selector("type_of_vote", $options, $selected_option, 'tabindex = "' . $tab_index . '"');
	}	

	public static function get_vote_type_description($type) {
		return self::get_vote_type_descriptions()[$type];
	}	

	public static function get_selectable_vote_type_descriptions() {
		$descriptions = self::get_vote_type_descriptions();
		unset($descriptions['workgroup-election']);
		return $descriptions;
	}	

	public static function get_vote_type_descriptions() {
		return array(
			"yes-no" => _t("Vote (yes/no)")
			, "prio-vote" => _t("Priority vote")
			, "candidate-election" => _t("Candidate election")
			, "workgroup-election" => _t("Workgroup election")
			, "median" => _t("Median vote")
			, "budget" => _t("Budget vote")
			); 
	}	

	public static function make_vote_time_type_selector($selected_option = null, $tab_index = 1) {
		$options = array(
			"active" => _t("Time limited")
			, "continuous" => _t("Continuous")
			); 
		general::make_control_label("vote_status", _t("Vote time"));
		general::make_selector("vote_status", $options, $selected_option, 'tabindex = "' . $tab_index . '"');
	}	

	public static function make_constituency_selector($selected_option = null, $user_id = null, $tab_index = 1) {
		$options = array();
		$constituencies = $user_id 
			? \db_constituency::get_constituencies_for_user($user_id)
			: \db_constituency::get_all_constituencies(1, PHP_INT_MAX);
		foreach($constituencies as $row)
			$options[$row['id']] = $row['name'];
		general::make_control_label("constituency_id", "Valkrets");
		general::make_selector("constituency_id", $options, $selected_option, 'tabindex = "' . $tab_index . '"');
	}

	public static function output_vote_status($status) 
	{
		_br();
		_label(_t("Vote status: "), "vote_status");
		$status_text = self::get_vote_status_text($status);
		__($status_text);
		_br();
		$buttons = self::get_vote_status_buttons($status);
		foreach ($buttons as $key => $value)
			echo '<button type="submit" name="action" value="' . $key . '">' . _t($value) . '</button>';
	}

	public static function get_ballot_content($vote_type, $ballot) {
		if($ballot == "abstain")
			return _t("Abstain");
		switch ($vote_type) {
			case 'yes-no':
				return _t($ballot == "yes" ? "Yes" : "No");
			case 'prio-vote':
			case 'candidate-election':
			case 'workgroup-election':
				return \vote_helpers::get_prio_vote_result_for_single_voter($_GET['id'], 
					json_decode($ballot, true));
			case 'median':
				return $ballot;
			default:
				return '';
		}
	}

	private static function get_vote_status_text($status) {
		switch ($status) {
			case "active": return "Ongoing";
			case "del_ended": return "Closed for delegates";
			case "ended": return "Finished";
			case "continuous": return "Continous";
			case "finished": return "Finished continous";
			default: throw new \Exception("unknown status: " . $status);
		} 
	}

	private static function get_vote_status_buttons($status) 
	{
		switch ($status) {
			case "active": return array(
				"end_vote" => "Finish the vote"
				, "end_delegate_vote" => "Finish the delegate vote"
				, "make_continuous" => "Transform to continous");
			case "del_ended": return array(
				"end_vote" => "Finish the vote"
				, "restore_delegate_vote" => "Resume the delegate vote");
			case "ended": return array(
				"restore_vote" => "Resume the vote");
			case "continuous": return array(
				"end_vote" => "Finish the vote"
				, "restore_delegate_vote" => "Transform to time limited");
			case "finished": return array(
				"restore_finished_vote" => "Resume the vote");
			default: throw new \Exception("unknown status: " . $status);
		} 
	}

	public static function get_vote_form_include($vote_type) {
		switch ($vote_type) {
			case "yes-no":
				return "/vote_types/yes-no.inc";
			case "prio-vote":
				return "/vote_types/prio-vote.inc";
			case "candidate-election":
			case "workgroup-election":
				return "/vote_types/candidate-election.inc";
			case "median":
				return "/vote_types/median.inc";
			default:
				throw new \Exception("Unknown vote type: " . $vote_type);
		}
	}

	public static function get_vote_script_include($vote_type) {
		switch ($vote_type) {
			case "yes-no":
				return "/vote_types/yes-no_js.inc";
			case "prio-vote":
			case "candidate-election":
			case "workgroup-election":
				return "/vote_types/prio-vote_js.inc";
			case "median":
				return "/vote_types/median_js.inc";
			default:
				return null;
		}
	}

	public static function make_title_input() {
		general::make_textfield("new_prop_title", "Titel", 3);
	}	

	public static function make_description_input() {
		general::make_textarea("new_prop_description", "Beskrivning", 4);
	}

	public static function make_vote_list($vote_groups, $type, $action, $from_action = null) {
		general::open_div("list_of_links");
		foreach($vote_groups as $vote_group) {
			echo '<h2>' . $vote_group->constituency . '</h2>';
			foreach($vote_group->votes as $row) {
				general::output_internal_link($row['title'], $type, $action, 'id=' . $row['id']
					. \View\general::get_from_action_for_url(array($from_action)));
				echo '<br/>';
			}
		}
		general::close_div("list_of_links");
	}

	public static function make_vote_end_time_select($vote_end_time, $control_name_prefix = "") {
		echo('<input type="text" value="' . date("Y", $vote_end_time) . '" name="' . 
			$control_name_prefix . 'year" id="year" style="width: 50px;">');
		$month_options = array(
			"1" => "Januari",
			"2" => "Februari",
			"3" => "Mars",
			"4" => "April",
			"5" => "Maj",
			"6" => "Juni",
			"7" => "Juli",
			"8" => "Augusti",
			"9" => "September",
			"10" => "Oktober",
			"11" => "November",
			"12" => "December",
		);
		general::make_selector($control_name_prefix . "month", $month_options, date("n", $vote_end_time), 
			'style="width: 100px;"');
		$days = array();
		for ($i = 1; $i < 32; $i++)
			$days[$i] = $i;
		general::make_selector($control_name_prefix . "day", $days, date("j", $vote_end_time), 
		'style="width: 60px; margin-right: 12px;"');
		echo "Kl.";
		$hours = array();
		for ($i = 0; $i < 24; $i++)
			$hours[$i] = str_pad("" . $i, 2, "0", STR_PAD_LEFT);
		general::make_selector($control_name_prefix . "hour", $hours, date("G", $vote_end_time), 
			'style="width: 60px;"');
		echo ": ";
		$minutes = array();
		for ($i = 0; $i < 60; $i += 5)
			$minutes[$i] = str_pad("" . $i, 2, "0", STR_PAD_LEFT);;
		general::make_selector($control_name_prefix . "minute", $minutes, date("i", $vote_end_time), 
			'style="width: 60px;"');
	}

	public static function output_back_link() {
		switch ($_GET['from_action']) {
			case 'search_prop':
			case 'search':
				\View\general::output_internal_link("Tillbaka till sökresultat",
					$_GET['type'], $_GET['from_action']);
				echo '<br>';
				break;
			default:
				throw new \Exception("Unknown from_action: " . $_GET('from_action'));
		}
	}

	public static function output_vote_header($voteinfo) {
		echo '<h1>' . self::get_vote_header_prefix($voteinfo['type']) . $voteinfo['title'] . '</h1>';
		if($voteinfo['type'] == "workgroup-election") {
			$workgroup_id = $voteinfo['from_proposition_id'];
			$workgroup_title = \db_workgroup::get_name_from_id($workgroup_id);
			echo '<p>Den här omröstningen utser medlemmarna till arbetsgruppen <a href="index.php?type=workgroup&action=view&id=" . $workgroup_id . ">' . $workgroup_title . '</a></p>';
		}		
	}

	private static function get_vote_header_prefix($type) {
		switch($type) {
			case "yes-no": return 'Votering: ';
			case "prio-vote": return 'Prioritetsomröstning: ';
			case "candidate-election": return 'Personval: ';
			case "median": return 'Medianomröstning: ';
			case "workgroup-election": return '';
			default: throw new \Exception("Unknown vote type: " . $type);
		}		
	}
}
?>
