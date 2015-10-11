<?php
namespace View;
class prop_helper 
{
	public static function make_vote_type_selector() {
		$options = array(
			"yes-no" => "Votering (ja/nej)"
			,"prio-vote" => "Prioritetsomröstning"
			,"candidate-election" => "Personval"
			,"median" => "Medianomröstning"
			,"budget" => "Budgetomröstning"
			);
		general_helper::make_selector("type_of_vote", "Typ av omröstning", 1, $options);
	}	

	public static function make_constituency_selector() {
		$options = array();
		$constituencies = \db_constituency::get_constituencies_for_user($_SESSION['id']);
		foreach($constituencies as $row)
			$options[$row['id']] = $row['name'];
		general_helper::make_selector("constituency_id", "Valkrets", 2, $options);
	}	

	public static function make_title_input() {
		general_helper::make_textfield("new_prop_title", "Titel", 3);
	}	

	public static function make_description_input() {
		general_helper::make_textarea("new_prop_description", "Beskrivning", 4);
	}	
}
?>
