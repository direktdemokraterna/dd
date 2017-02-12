<?php
namespace View;

class vote 
{
	public static function output_vote_finish_status($voteinfo) {
		if($voteinfo['status'] == "ended" || $voteinfo['status'] == "finished")
			echo '<tr><td>Avslutad:</td><td>'
			. \general_helpers::show_date($voteinfo['timestamp_ended']) . '</td>';
		elseif($voteinfo['status'] == "del_ended")
			echo '<tr><td>Avslutas:</td><td>'
				. \general_helpers::show_date($voteinfo['timestamp_ended']) . '</td></tr><tr><td>'
				. '. Delegatröstning avslutades ' . '</td></td>'
				. \general_helpers::show_date($voteinfo['timestamp_delegate_ended']) . '</td></tr>';
		elseif($voteinfo['status'] == "continuous")
			echo '	<tr><td>Avslutas: </td><td>Kontinuerlig</td></tr>
					<tr><td>Delegatröstning: </td><td>Kontinuerlig</td></tr>';
		else
			echo '<tr><td>Avslutas:</td><td>' 
				. \general_helpers::show_date($voteinfo['timestamp_ended']) . '</td></tr>';
			echo '<tr><td>Delegatröstning avslutas:</td><td>'
				. \general_helpers::show_date($voteinfo['timestamp_delegate_ended'])
				. '</td></tr>';
	}

	public static function output_ballot_info($voteinfo, $delegate_ballot) {
		if($_SESSION['delegate_id']) {
			if(empty($delegate_ballot))
				echo "Du som delegat har ännu inte röstat i denna omröstning.";
			else {
				if(isset($delegate_ballot['delegate_id']))
					echo "Du som delegat har röstat i denna omröstning.";
				else
					echo "Du som delegat har själv röstat i denna omröstning.";
				__br();
				echo "Din röst:";
				__br();
				echo self::get_ballot_content($voteinfo['type'], $delegate_ballot['ballot']);
			}
		}
		else echo "Ingen röst har lämnats i ditt namn i denna omröstning.";
	}

	public static function output_proposition_creation_info($voteinfo) {
		if($voteinfo['proposition_created']) {
			echo '<tr><td>Proposition skapad: </td><td>';
			echo \general_helpers::show_date($voteinfo['proposition_created']);
			echo '</td></tr>';
			echo '<tr><td>Proposition skapad av: </td><td>';
			__link($voteinfo['user_full_name'], 'member', 'view', 'id=' . $voteinfo['user_id']);
			echo '</td></tr>';
		}
	  	else 
			echo '<tr><td colspan="2">Omröstning skapad av administratör';
			echo '</td></tr>';
	}

	public static function output_vote_started_info($voteinfo) {
		echo '<tr><td>Omröstning startad: </td><td>';
		echo \general_helpers::show_date($voteinfo['timestamp_created']);
		echo '</td></tr>';
	}

	public static function output_number_of_cast_ballots_info($voteinfo, $number_of_delegate_ballots) {
		echo '<tr><td>Antal röster</td><td>' . $voteinfo['number_of_ballots'] . '</td></tr>';
		echo '<tr><td>Antal personligt lagda röster</td><td>' . $voteinfo['number_of_direct_ballots'] . '</td></tr>';
		echo '<tr><td>Antal delegatröster</td><td>' . $number_of_delegate_ballots . '</td></tr>';
	}

	public static function output_vote_description($voteinfo) {
		__info("<h2>Beskrivning</h2>", \Logic\text::make_html_from_wiki_text($voteinfo['description']));
	}

	public static function output_view_cast_ballots($voteinfo) {
		if($voteinfo['number_of_ballots'] > $voteinfo['number_of_direct_ballots']
			&& ($voteinfo['type'] == "yes-no" || $voteinfo['type'] == "median")) {
			echo '<a href="javascript:void(0)" onclick="show_delegate_votes(\'' . $voteinfo['type'] . '\')" class="link-icon">Se delegatröster</a>';
		}
		echo '<tr><td>';
		__link("Se alla röster", 'vote', 'view_ballots', 'id=' . $voteinfo['id'], 'link-icon');
		echo '</td></tr>';
		
	}

	public static function output_vote_debate_link($voteinfo) {
		__link("<span>Länk till diskussion</span>", 'forum', 'show_posts', 'topic_id=' . $voteinfo['forum_topic_id'], 'btn-blue bubble');
	}

	public static function output_proposition_debate_link($voteinfo) {
		__link("<span>Länk till diskussion</span>", 'forum', 'show_posts', 'topic_id=' . $voteinfo['forum_topic_id'], 'btn-blue bubble');
	}
	
	public static function output_vote_buttons($voteinfo, $user_allowed_to_vote) {
		if($user_allowed_to_vote) {
			echo '<div class="vote_box">';
			include(__DIR__ . self::get_vote_form_include($voteinfo['type']));
			echo '</div>';
			echo $_SESSION['delegate_id'] ? "Du röstar som delegat." : "Du röstar som individ.";
		}
	}

	public static function output_javascript_vote_handlers($voteinfo) {
		$vote_script_include = self::get_vote_script_include($voteinfo['type']);
		if ($vote_script_include)
			include(__DIR__ . $vote_script_include);
	}

	public static function make_add_alternative_form($voteinfo) {
		if($voteinfo['type'] == "prio-vote") {
			self::open_add_alternative_form("Add alternative to", $voteinfo);
			__p("Här kan du skapa alternativ till prioritetsomröstningen. Notera att du kan bara skapa alternativ, endast valadministratörer kan ta bort alternativ igen.");
			__textfield("alternative_title", "Titel", 1);
			__textarea("alternative_description", "Beskrivning", 2);
			self::close_add_alternative_form("Skapa alternativ", 3);
		}
		elseif(\db_vote::is_user_candidate_in_vote($_SESSION['id'], $voteinfo['id'])){
			self::open_add_alternative_form("Dra tillbaka din kandidatur till", $voteinfo);
			self::close_add_alternative_form("Dra tillbaka kandidatur");
		}
		else {
			self::open_add_alternative_form("Kandidera till", $voteinfo);
			__textarea("alternative_description", "Kandidatbeskrivning", 1);
			self::close_add_alternative_form("Kandidat", 2);
		}
	}

	public static function output_common_delegate_vote_box_translations_for_js() {
		echo 'var delegate_vote_box_header = "Delegatröster<table><tr style=\'color: white\'><th>Delegat</th><th>Röst</th><th>Röst lagd av</th></tr>";';
		echo 'var abstain_text = "Avstå";';
	}

	private static function open_add_alternative_form($caption_prefix, $voteinfo) {
		__h1($caption_prefix . " omröstningen: " . $voteinfo['title']);
		__p(_link("Tillbaka till omröstningen", 'vote', 'view_vote', 'id=' . $voteinfo['id']));
		__open_form();
		__hidden("vote_id", $voteinfo['id']);
	}

	private static function close_add_alternative_form($submit_text, $submit_tab_index = 1) 
	{
		__submit_and_close($submit_text, null, null, $submit_tab_index);
	}

	public static function make_vote_type_selector($selected_option = null, $tab_index = 1) {
		$options = self::get_selectable_vote_type_descriptions();
		echo \View\controls::generate_control_label("type_of_vote", "Omröstningstyp");
		\View\controls::output_selector("type_of_vote", $options, $selected_option, 'tabindex = "' . $tab_index . '"');
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
			"active" => "Tidsbegränsad"
			, "continuous" => "Kontinuerlig"
			); 
		echo \View\controls::generate_control_label("vote_status", "Omröstningstid");
		\View\controls::output_selector("vote_status", $options, $selected_option, 'tabindex = "' . $tab_index . '"');
	}	

	public static function make_constituency_selector($selected_option = null, $user_id = null, $tab_index = 1) {
		$options = array();
		$constituencies = $user_id 
			? \db_constituency::get_constituencies_for_voter($user_id)
			: \db_constituency::get_all_constituencies(1, PHP_INT_MAX);
		foreach($constituencies as $row)
			$options[$row['id']] = $row['name'];
		echo \View\controls::generate_control_label("constituency_id", "Valkrets");
		\View\controls::output_selector("constituency_id", $options, $selected_option, 'tabindex = "' . $tab_index . '"');
	}

	public static function output_vote_status($status) 
	{
		__br();
		__label("Omröstningsstatus: ", "vote_status");
		$status_text = self::get_vote_status_text($status);
		echo $status_text;
		__br();
		$buttons = self::get_vote_status_buttons($status);
		foreach ($buttons as $key => $value) {
			__space();
			echo '<button type="submit" name="action" value="' . $key . '">' 
			. $value . '</button>';			
			__space();
		}
	}

	public static function list_ballots($vote_type, $ballots, $content_prop = 'ballot') 
	{
		if(empty($ballots))
			echo "Inga röster lagda";
		else {
			echo '<table class="view-ballots responsive">';
			echo '<tr><th>Röstande</th><th>Röst</th><th>Delegat</th><th>Tidpunkt</th></tr>';
			foreach ($ballots as $ballot){
				echo '<tr><td>';
				if($ballot['user_code'])
					echo "Användare";
				else 
					__link($ballot['voter_is_delegate_name'], 'vote', 'view_delegate', 'id=' . $ballot['voter_id']);
				echo '</td><td>';
				echo self::get_ballot_content($vote_type, $ballot[$content_prop]);
				echo '</td><td>';
				if($ballot['delegate_id'])
					__link($ballot['delegate_name'], 'vote', 'view_delegate', 'id=' . $ballot['delegate_id']);
				echo '</td><td>';
				echo \general_helpers::show_date($ballot['time_ballot_placed']);
				echo '</td></tr>';
			}
			echo '</table>';
		}
	}

	public static function get_ballot_content($vote_type, $ballot) {
		if($ballot == "abstain")
			return "Avstår";
		switch ($vote_type) {
			case 'yes-no':
				return $ballot == "yes" ? "Ja" : "Nej";
			case 'prio-vote':
			case 'candidate-election':
			case 'workgroup-election':
				return \vote_helpers::get_prio_vote_result_for_single_voter($_GET['id'], 
					json_decode($ballot, true));
			case 'median':
				return $ballot;
			case 'proposition':
				return $ballot ? "Stöder" : "Stöder inte";
			default:
				return '';
		}
	}

	private static function get_vote_status_text($status) {
		switch ($status) {
			case "active": return "Pågående";
			case "del_ended": return "Avslutad för delegater";
			case "ended": return "Avslutad";
			case "continuous": return "Kontinuerlig";
			case "finished": return "Avslutad kontinuerlig";
			default: throw new \Exception("unknown status: " . $status);
		} 
	}

	private static function get_vote_status_buttons($status) 
	{
		switch ($status) {
			case "active": return array(
				"end_vote" => "Avsluta omröstningen"
				, "end_delegate_vote" => "Avsluta delegatomröstningen"
				, "make_continuous" => "Gör om till kontinuerlig");
			case "del_ended": return array(
				"end_vote" => "Avsluta omröstningen"
				, "restore_delegate_vote" => "Återuppta delegatomröstningen");
			case "ended": return array(
				"restore_vote" => "Återuppta omröstningen");
			case "continuous": return array(
				"finish_vote" => "Avbryt omröstningen"
				, "make_active" => "Gör om till tidsbegränsad omröstning");
			case "finished": return array(
				"restore_finished_vote" => "Återuppta omröstningen");
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
			case "budget":
				return "/vote_types/budget.inc";
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
			case "budget":
				return "/vote_types/budget_js.inc";
			default:
				return null;
		}
	}

	public static function make_title_input() {
		__textfield("new_prop_title", "Titel", 3);
	}	

	public static function make_description_input() {
		__textarea("new_prop_description", "Beskrivning", 4);
	}

	public static function make_vote_list($vote_groups, $vote_count, $type, $action, $from_action = null) 
	{
		$page = isset($_GET['page']) ? $_GET['page'] : 1;
		$sort = isset($_GET['sort']) ? $_GET['sort'] : 0;		
		\View\controls::output_paging_row($page, $vote_count);
		self::output_vote_grid($vote_groups, $type, $action, $from_action);
		\View\controls::output_paging_row($page, $vote_count);
	}

	private static function output_vote_grid($vote_groups, $type, $action, $from_action = null) 
	{
		foreach($vote_groups as $vote_group) {
			echo '<h2>' . $vote_group->constituency . '</h2>';
			$columns = array(
				"Omröstning"
				, "Omröstningstyp"
				, "Omröstning startad"
				, "Resultat"
				, "Antal röster");
			$rows = array_map(function($vote) use ($type, $action, $from_action) {
				return array(
					_link($vote['title'], $type, $action
						, 'id=' . $vote['id']
					. \View\general::get_from_action_for_url(array($from_action)))
					, \View\vote::get_vote_type_description($vote['type'])
					, \general_helpers::show_date($vote['timestamp_created'])
					, \View\vote::generate_vote_result($vote)
					, $vote['number_of_ballots']
					);
			}, $vote_group->votes);
			\View\controls::output_grid_view($columns, $rows);
		}
	}

	public static function make_proposition_list($prop_groups, $prop_count
		, $type, $action, $from_action = null) 
	{
		$page = isset($_GET['page']) ? $_GET['page'] : 1;
		$sort = isset($_GET['sort']) ? $_GET['sort'] : 0;		
		\View\controls::output_paging_row($page, $prop_count);
		self::output_proposition_grid($prop_groups, $type, $action, $from_action);
		\View\controls::output_paging_row($page, $prop_count);
	}

	private static function output_proposition_grid($prop_groups, $type, $action, $from_action = null) 
	{
		foreach($prop_groups as $prop_group) {
			echo '<h2>' . $prop_group->constituency . '</h2>';
			$columns = array("Proposition"
				, "Skapad"
				, "Stöd");
			$rows = array_map(function($prop) use ($type, $action, $from_action) {
				return array(
					_link($prop['title'], $type, $action
						, 'id=' . $prop['id']
					. \View\general::get_from_action_for_url(array($from_action)))
					, \general_helpers::show_date($prop['timestamp_created'])
					, $prop['number_of_supporters']
					);
			}, $prop_group->votes);
			\View\controls::output_grid_view($columns, $rows);
		}
	}

	public static function output_vote_result_with_header($voteinfo, $ballots_to_count) {
		echo self::generate_vote_result_header($voteinfo, $ballots_to_count); // todo: wrong parameter count
		echo self::generate_vote_result($voteinfo);
	}

	public static function generate_vote_result_header($voteinfo) {
		switch ($voteinfo['type']) {
			case "budget":
			case "candidate-election": 
			case "median": 
			case "prio-vote": 
			case "yes-no": 
				return "Resultatet är:" . '<br>';
			case "workgroup-election": 
				return 'Kandidater ovanför linjen är valda till platserna i arbetsgruppen, kandidater i fetstil är nuvarande medlemmar: <br>';
			default: throw new \Exception("Unknown vote type: " . $voteinfo['type']);
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
				return \vote_helpers::generate_workgroup_election_result($voteinfo['id']
					, $voteinfo['from_proposition_id']);
			case "median": 
				return \vote_helpers::generate_median_result($ballots_to_count);
			case "budget": 
				return 0;
			default: throw new \Exception("Unknown vote type: " . $voteinfo['type']);
		}
	}

	public static function make_vote_end_time_select($vote_end_time, $control_name_prefix = "") {
		echo('<input type="text" value="' . date("Y", $vote_end_time) . '" name="' . 
			$control_name_prefix . 'year" id="year" style="width: 50px;">');
		$month_options = \View\calendar::generate_month_options();
		\View\controls::output_selector($control_name_prefix . "month", $month_options, date("n", $vote_end_time), 
			'style="width: 100px;"');
		$days = array();
		for ($i = 1; $i < 32; $i++)
			$days[$i] = $i;
		\View\controls::output_selector($control_name_prefix . "day", $days, date("j", $vote_end_time), 
		'style="width: 60px; margin-right: 12px;"');
		echo "Kl.";
		$hours = array();
		for ($i = 0; $i < 24; $i++)
			$hours[$i] = str_pad("" . $i, 2, "0", STR_PAD_LEFT);
		\View\controls::output_selector($control_name_prefix . "hour", $hours, date("G", $vote_end_time), 
			'style="width: 60px;"');
		echo ": ";
		$minutes = array();
		for ($i = 0; $i < 60; $i += 5)
			$minutes[$i] = str_pad("" . $i, 2, "0", STR_PAD_LEFT);;
		\View\controls::output_selector($control_name_prefix . "minute", $minutes, date("i", $vote_end_time), 
			'style="width: 60px;"');
	}

	public static function output_vote_header($voteinfo) {
		echo '<h1>' . self::get_vote_header_prefix($voteinfo['type']) . $voteinfo['title'] . '</h1>';
		if($voteinfo['type'] == "workgroup-election") {
			$workgroup_id = $voteinfo['from_proposition_id'];
			$workgroup_title = \db_workgroup::get_name_from_id($workgroup_id);
			echo '<p>';
			echo "Den här omröstningen utser medlemmar till arbetsgruppen ";
			__link($workgroup_title, 'workgroup', 'view', 'id=' . $workgroup_id);
			echo '</p>';
		}		
	}

	private static function get_vote_header_prefix($type) {
		if ($type == "yes-no") return "Omröstning: ";
		if ($type == "workgroup-election") return '';
		$type_descriptions = self::get_vote_type_descriptions();
		return $type_descriptions[$type] . ": ";
	}
	
	public static function get_vote_type_descriptions() {
		return array(
			"yes-no" => "Omröstning (ja/nej)"
			, "prio-vote" => "Prioritetsomröstning"
			, "candidate-election" => "Personval"
			, "workgroup-election" => "Val till arbetsgrupp"
			, "median" => "Medianomröstning"
			, "budget" => "Budgetomröstning"
			); 
	}	
}
