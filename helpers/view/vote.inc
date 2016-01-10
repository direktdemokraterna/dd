<?php
namespace View;

class vote 
{
	public static function make_add_alternative_form($voteinfo) {
		if($voteinfo['type'] == "prio-vote") {
			self::open_add_alternative_form("Add alternative to", $voteinfo);
			_p(_t("Here you can create more vote alternatives to the priority vote above. Note that when you have created an alternative it cannot be removed other than by a vote admin."));
			\View\general::make_textfield("alternative_title", _t("Title"), 1);
			\View\general::make_textarea("alternative_description", _t("Description"), 2);
			self::close_add_alternative_form(_t("Create alternative"), 3);
		}
		elseif(\db_vote::is_user_candidate_in_vote($_SESSION['id'], $voteinfo['id'])){
			self::open_add_alternative_form("Remove your candidacy in", $voteinfo);
			self::close_add_alternative_form(_t("Remove candidacy"));
		}
		else {
			self::open_add_alternative_form("Register as candidate for", $voteinfo);
			\View\general::make_textarea("alternative_description", _t("Candidate description", array('class' => 'noun')), 1);
			self::close_add_alternative_form(_t("Candidate", array('class' => 'verb')), 2);
		}
	}

	public static function output_common_delegate_vote_box_translations_for_js() {
		echo 'var delegate_vote_box_header = "' . _t("Delegate ballots:", array('class' => 'noun')) 
		. '<table><tr style=\'color: white\'><th>' 
		. _t("Delegate", array('class' => 'noun')) . '</th><th>' 
		. _t("Ballot") . '</th><th>' 
		. _t("Ballot cast by", array('class' => 'adj')) . '</th></tr>";';
		echo 'var abstain_text = "' . _t("Abstain") . '";';
	}

	private static function open_add_alternative_form($caption_prefix, $voteinfo) {
		_h1(_t($caption_prefix) . _t(" the vote: ") . $voteinfo['title']);
		_p(\View\general::generate_internal_link(_t("Back to the vote"), 'vote', 'view_vote', 'id=' . $voteinfo['id']));
		_open_form();
		_hidden("vote_id", $voteinfo['id']);
	}

	private static function close_add_alternative_form($submit_text, $submit_tab_index = 1) 
	{
		_submit_and_close($submit_text, null, $submit_tab_index);
	}

	public static function make_vote_type_selector($selected_option = null, $tab_index = 1) {
		$options = self::get_selectable_vote_type_descriptions();
		general::make_control_label("type_of_vote", _t("Type of vote", array('class' => 'noun')));
		general::make_selector("type_of_vote", $options, $selected_option, 'tabindex = "' . $tab_index . '"');
	}	

	public static function get_vote_type_description($type) {
		$type_descriptions = self::get_vote_type_descriptions();
		return $type_descriptions[$type];
	}	

	public static function get_selectable_vote_type_descriptions() {
		$descriptions = self::get_vote_type_descriptions();
		unset($descriptions['workgroup-election']);
		return $descriptions;
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
			? \db_constituency::get_constituencies_for_voter($user_id)
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
		foreach ($buttons as $key => $value) {
			_space();
			echo '<button type="submit" name="action" value="' . $key . '">' 
			. _t($value, array('class' => 'noun')) . '</button>';			
			_space();
		}
	}

	public static function list_ballots($vote_type, $ballots, $content_prop = 'ballot') 
	{
		if(empty($ballots))
			__("No ballots cast.", array('class'=>'adj'));
		else {
			echo '<table class="responsive">';
			echo '<tr><th>' . _t("Voter") . '</th><th>' . _t("Ballot") 
			. '</th><th>' . _t("Delegate", array('class' => 'noun')) . '</th><th>' 
			. _t("Time of vote") . '</th></tr>';
			foreach ($ballots as $ballot){
				echo '<tr><td>';
				if($ballot['user_code'])
					__("User");
				else 
					_link($ballot['voter_is_delegate_name'], 'vote', 'view_delegate', 'id=' . $ballot['voter_id']);
				echo '</td><td>';
				echo self::get_ballot_content($vote_type, $ballot[$content_prop]);
				echo '</td><td>';
				if($ballot['delegate_id'])
					_link($ballot['delegate_name'], 'vote', 'view_delegate', 'id=' . $ballot['delegate_id']);
				echo '</td><td>';
				echo \general_helpers::show_date($ballot['time_ballot_placed']);
				echo '</td></tr>';
			}
			echo '</table>';
		}
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
			case 'proposition':
				return $ballot ? _t('Supports') : _t("Doesn't support");
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
		general::make_textfield("new_prop_title", _t("Title"), 3);
	}	

	public static function make_description_input() {
		general::make_textarea("new_prop_description", _t("Description"), 4);
	}

	public static function make_vote_list($vote_groups, $type, $action, $from_action = null) 
	{
		foreach($vote_groups as $vote_group) {
			echo '<h2>' . $vote_group->constituency . '</h2>';
			$columns = array(_t("Vote", array('class' => 'noun')), _t('Vote type'), _t("Result"), _t("Number of ballots"));
			$rows = array_map(function($vote) use ($type, $action, $from_action) {
				return array(
					\View\general::generate_internal_link($vote['title'], $type, $action
						, 'id=' . $vote['id']
					. \View\general::get_from_action_for_url(array($from_action)))
					, \View\vote::get_vote_type_description($vote['type'])
					, \View\vote::generate_vote_result($vote)
					, $vote['number_of_ballots']
					);
			}, $vote_group->votes);
			\View\general::output_grid_view($columns, $rows);
		}
	}

	public static function make_proposition_list($prop_groups, $type, $action, $from_action = null) 
	{
		foreach($prop_groups as $prop_group) {
			echo '<h2>' . $prop_group->constituency . '</h2>';
			$columns = array(_t("Proposition", array('class' => 'noun')), _t("Support", array('class' => 'noun')));
			$rows = array_map(function($prop) use ($type, $action, $from_action) {
				return array(
					\View\general::generate_internal_link($prop['title'], $type, $action
						, 'id=' . $prop['id']
					. \View\general::get_from_action_for_url(array($from_action)))
					, $prop['number_of_supporters']
					);
			}, $prop_group->votes);
			\View\general::output_grid_view($columns, $rows);
		}
	}

	public static function output_vote_result_with_header($voteinfo, $ballots_to_count) {
		echo self::generate_vote_result_header($voteinfo, $ballots_to_count);
		echo self::generate_vote_result($voteinfo);
	}

	public static function generate_vote_result_header($voteinfo) {
		switch ($voteinfo['type']) {
			case "candidate-election": 
			case "median": 
			case "prio-vote": 
			case "yes-no": 
				return _t("The vote count is:") . '<br>';
			case "workgroup-election": 
				return _t("Candidates above the line are elected to the workgroup, candidates in bold are those who are currently members: ") . '<br>';
			default: throw new \Exception("Unknonw vote type: " . $voteinfo['type']);
		}
	}

	public static function generate_vote_result($voteinfo, $ballots_to_count = null) {
		if (!$ballots_to_count) {
			$all_ballots = \db_vote::get_ballots($voteinfo['id']);
			$ballots_to_count = array_filter($all_ballots, 
				function($ballot) {return $ballot['user_code'];});					
		}
		switch ($voteinfo['type']) {
			case "yes-no": 
				return \vote_helpers::generate_yes_no_result($ballots_to_count);
			case "prio-vote": 
				return \vote_helpers::generate_prio_vote_result($voteinfo['id']);
			case "candidate-election": 
				return \vote_helpers::generate_candidate_election_result($voteinfo['id']);
			case "workgroup-election": 
				return generate_workgroup_election_result($voteinfo['id']
					, $voteinfo['from_proposition_id']);
			case "median": 
				return \vote_helpers::generate_median_result($ballots_to_count);
			default: throw new \Exception("Unknonw vote type: " . $voteinfo['type']);
		}
	}

	public static function make_vote_end_time_select($vote_end_time, $control_name_prefix = "") {
		echo('<input type="text" value="' . date("Y", $vote_end_time) . '" name="' . 
			$control_name_prefix . 'year" id="year" style="width: 50px;">');
		$month_options = \View\calendar::generate_month_options();
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

	public static function output_vote_header($voteinfo) {
		echo '<h1>' . self::get_vote_header_prefix($voteinfo['type']) . $voteinfo['title'] . '</h1>';
		if($voteinfo['type'] == "workgroup-election") {
			$workgroup_id = $voteinfo['from_proposition_id'];
			$workgroup_title = \db_workgroup::get_name_from_id($workgroup_id);
			echo '<p>';
			__("This vote appoints members to the workgroup ");
			_link($workgroup_title, 'workgroup', 'view', 'id=' . $workgroup_id);
			echo '</p>';
		}		
	}

	private static function get_vote_header_prefix($type) {
		if ($type == "yes-no") return _t("Vote: ");
		if ($type == "workgroup-election") return '';
		$type_descriptions = self::get_vote_type_descriptions();
		return $type_descriptions[$type] . ": ";
	}
	
	public static function get_vote_type_descriptions() {
		return array(
			"yes-no" => _t("Vote (yes/no)")
			, "prio-vote" => _t("Priority vote", array('class' => 'noun'))
			, "candidate-election" => _t("Candidate election")
			, "workgroup-election" => _t("Workgroup election")
			, "median" => _t("Median vote", array('class' => 'noun'))
			, "budget" => _t("Budget vote", array('class' => 'noun'))
			); 
	}	
}
?>
