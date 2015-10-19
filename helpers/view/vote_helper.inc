<?php
namespace View;

class vote_helper 
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
		general_helper::make_control_label("type_of_vote", "Typ av omröstning");
		general_helper::make_selector("type_of_vote", $options, $selected_option, 'tabindex = "1"');
	}	

	public static function make_constituency_selector() {
		$options = array();
		$constituencies = \db_constituency::get_constituencies_for_user($_SESSION['id']);
		foreach($constituencies as $row)
			$options[$row['id']] = $row['name'];
		$selected_option = isset($_POST["constituency_id"]) ? $_POST["constituency_id"] : null;
		general_helper::make_control_label("constituency_id", "Valkrets");
		general_helper::make_selector("constituency_id", $options, $selected_option, 'tabindex = "1"');
	}	

	public static function make_title_input() {
		general_helper::make_textfield("new_prop_title", "Titel", 3);
	}	

	public static function make_description_input() {
		general_helper::make_textarea("new_prop_description", "Beskrivning", 4);
	}

	public static function make_vote_list($vote_groups, $type, $action) {
		general_helper::open_div("list_of_links");
		foreach($vote_groups as $vote_group) {
			echo '<h2>' . $vote_group->constituency . '</h2>';
			foreach($vote_group->votes as $row)
				general_helper::make_internal_link($row['title'], $type, $action, '&id=' . $row['id'], true);
		}
		general_helper::close_div("list_of_links");
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
		general_helper::make_selector($control_name_prefix . "month", $month_options, date("n", $vote_end_time), 
			'style="width: 100px;"');
		$days = array();
		for ($i = 1; $i < 32; $i++)
			$days[$i] = $i;
		general_helper::make_selector($control_name_prefix . "day", $days, date("j", $vote_end_time), 
		'style="width: 60px; margin-right: 12px;"');
		echo "Kl.";
		$hours = array();
		for ($i = 0; $i < 24; $i++)
			$hours[$i] = str_pad("" . $i, 2, "0", STR_PAD_LEFT);
		general_helper::make_selector($control_name_prefix . "hour", $hours, date("G", $vote_end_time), 
			'style="width: 60px;"');
		echo ": ";
		$minutes = array();
		for ($i = 0; $i < 60; $i += 5)
			$minutes[$i] = str_pad("" . $i, 2, "0", STR_PAD_LEFT);;
		general_helper::make_selector($control_name_prefix . "minute", $minutes, date("i", $vote_end_time), 
			'style="width: 60px;"');
	}
}
?>
