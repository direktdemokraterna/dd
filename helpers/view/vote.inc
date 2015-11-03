<?php
namespace View;

class vote 
{
	public static function get_two_weeks_in_seconds() {
		return 14*24*3600;
	}

	public static function make_vote_type_selector() {
		$options = array(
			"yes-no" => "Votering (ja/nej)"
			,"prio-vote" => "Prioritetsomröstning"
			,"candidate-election" => "Personval"
			,"median" => "Medianomröstning"
			,"budget" => "Budgetomröstning"
			);
		$selected_option = isset($_POST["type_of_vote"]) ? $_POST["type_of_vote"] : null;
		general::make_control_label("type_of_vote", "Typ av omröstning");
		general::make_selector("type_of_vote", $options, $selected_option, 'tabindex = "1"');
	}	

	public static function make_constituency_selector() {
		$options = array();
		$constituencies = \db_constituency::get_constituencies_for_user($_SESSION['id']);
		foreach($constituencies as $row)
			$options[$row['id']] = $row['name'];
		$selected_option = isset($_POST["constituency_id"]) ? $_POST["constituency_id"] : null;
		general::make_control_label("constituency_id", "Valkrets");
		general::make_selector("constituency_id", $options, $selected_option, 'tabindex = "1"');
	}	

	public static function make_title_input() {
		general::make_textfield("new_prop_title", "Titel", 3);
	}	

	public static function make_description_input() {
		general::make_textarea("new_prop_description", "Beskrivning", 4);
	}

	public static function make_vote_list($vote_groups, $type, $action) {
		general::open_div("list_of_links");
		foreach($vote_groups as $vote_group) {
			echo '<h2>' . $vote_group->constituency . '</h2>';
			foreach($vote_group->votes as $row)
				general::make_internal_link($row['title'], $type, $action, 'id=' . $row['id']
					. \View\general::get_from_action_for_url(array('search')), true);
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
		echo self::generate_back_link();
	}

	public static function output_vote_header($voteinfo) {
		echo '<h1>' . self::get_vote_header_prefix($voteinfo['type']) . $voteinfo['title'] . '</h1>';
		if($voteinfo['type'] == "workgroup-election") {
			$workgroup_id = $voteinfo['from_proposition_id'];
			$workgroup_title = \db_workgroup::get_name_from_id($workgroup_id);
			echo '<p>Den här omröstningen utser medlemmarna till arbetsgruppen <a href="index.php?type=workgroup&action=view&id=<?php echo $workgroup_id; ?>"><?php echo $workgroup_title; ?></a></p>';
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

	private static function generate_back_link() {
		switch ($_GET['from_action']) {
			case 'search':
				return \View\general::make_internal_link("Tillbaka till sökresultat",
					$_GET['type'], $_GET['from_action'], null, true);
			default:
				throw new \Exception("Unknown from_action: " . $_GET('from_action'));
		}
	}
}
?>
