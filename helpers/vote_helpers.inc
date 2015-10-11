<?php

class vote_helpers {


public static function ballot_count_yes_no_abstain ($array_of_ballots){

	$yes = 0;
	$no = 0;
	$abstain = 0;

	foreach($array_of_ballots as $row){
		if($row['user_code'] != null){
		    if($row['alternative'] == "yes") $yes++;
		    elseif($row['alternative'] == "no") $no++;
	    	elseif($row['alternative'] == "abstain") $abstain++;
	    }
	}

	return Array("yes" => $yes, "no" => $no, "abstain" => $abstain);

}

public static function ballot_count_median ($array_of_ballots){

	$array_of_values = array();
	foreach ($array_of_ballots as $item) {
		if($item['user_code'] != null){
	   		if(is_numeric($item['value'])){
   				$array_of_values[] = $item['value'];
   			}
   		}
	}

	$count = count($array_of_values);

	if($count == 0){
		return "Inget värde satt";
	}
	else{
		$middle_index = floor($count / 2);
		sort($array_of_values, SORT_NUMERIC);
		$median = $array_of_values[$middle_index]; // assume an odd # of items

		// Handle the even case by averaging the middle 2 items
		if ($count % 2 == 0) {
			$median = ($median + $array_of_values[$middle_index - 1]) / 2;
		}

		return $median;
	}

}

public static function get_complete_list_of_user_delegations (){
	$list_of_delegations_from_db = db_delegate::get_complete_list_of_user_delegations();

	$list_of_delegations = Array();
	foreach($list_of_delegations_from_db as $row){
		$list_of_votes[] = Array("user_code" => $row['user_code'], "constituency_id" => $row['constituency_id'], "delegate_id" => $row['delegate_id'], "delegate_name" => $row['delegate_name']);
	}

	echo "<script>var list_of_votes = " . json_encode($list_of_delegations) . ";</script>";

	return;

}

public static function calculate_prio_vote_result ($vote_id){

	// Using Joakim Sigvald's matrix method for calculating prio vote results. 
	// Each ballot is converted to a matrix of vote alternatives * vote alternatives where each cell is either 1, 0 or -1 depending on the row or the column has higher ranking or both have equal. All ballot matrices are then added togehter giving a result matrix from which a ranked list of the alternatives is derived. 

	$alternatives = db_vote::get_alternative_ids_from_vote_id($vote_id);

	$ballots = db_vote::get_prio_vote_ballots_without_extra_info($vote_id);

	// Firstly creating the result matrix to which the ballot matrices should be added.
	$result_matrix = Array();
	foreach($alternatives as $row){
		$temp_array = Array();
		foreach($alternatives as $column){
			$column_value = $column[0];
			$temp_array[$column_value] = 0;
		}
		$row_value = $row[0];
		$result_matrix[$row_value] = $temp_array;
	}

	// Iterating through every ballot.
	foreach($ballots as $ballot){
		$ballot_array = json_decode($ballot[0], true);
		
		// Iterating through each row of the result matrix.
		foreach($alternatives as $row){
			$row_value = $row[0];
			
			// Iterating through each column of the result matrix and adding the relevant result.
			foreach($alternatives as $column){
				$column_value = $column[0];

				if(!isset($ballot_array[$row_value])) $ballot_array[$row_value] = 0;
				if(!isset($ballot_array[$column_value])) $ballot_array[$column_value] = 0;
				
				// 1 denotes row alternative ranked higher than column alternative, -1 denotes column value ranked higher than row value, 0 denotes no difference in rank. 
				if($ballot_array[$row_value] > $ballot_array[$column_value]){
					$result_matrix[$row_value][$column_value]++;
				}
				elseif($ballot_array[$row_value] < $ballot_array[$column_value]){
					$result_matrix[$row_value][$column_value]--;
				}
			}
		}
		
	}

	// Calculating the ranked order from the result matrix.
	// First by creating an array of the vote alternatives and their combined score from the result matrix.
	$result_array = Array();
	foreach($alternatives as $result_row){
		// Loop through columns of this particular row in result matrix and combine values
		$result_row_value = $result_row[0];
		$row_sum = 0;
		foreach($alternatives as $result_column){
			$result_column_value = $result_column[0];
			$row_sum += $result_matrix[$result_row_value][$result_column_value];
		}

		// Get age of alternative for secondary sorting
		$alternative_created = db_vote::get_timestamp_added_for_alternative($result_row[0]);

		$result_array[] = Array("alternative_id" => $result_row[0], "score" => $row_sum, "created" => $alternative_created);
	}

	usort($result_array, function($a, $b) 
		{ 
			$score_compare = $b["score"] - $a["score"];
			if($score_compare == 0){
				return $a["created"] - $b["created"];
			}
			return $score_compare; 
		});

	return $result_array;	

}

public static function calculate_and_output_prio_vote_result ($result_array){

	$rank = 1;
	$previous_rank = 1;
	$previous_score = PHP_INT_MAX;
	foreach($result_array as $row){
		$alternative_title = db_vote::get_alternative_title($row['alternative_id']);
		if($row['score'] < $previous_score){
			echo $rank;
			$previous_rank = $rank;
		}
		else{
			echo $previous_rank;
		}
		echo ". " . $alternative_title . "<br>";
		$previous_score = $row['score'];
		$rank++;
	}

}

public static function calculate_and_output_candidate_election_result ($result_array){

	$rank = 1;
	$previous_rank = 1;
	$previous_score = PHP_INT_MAX;
	foreach($result_array as $row){
		$alternative_candidate_info = db_vote::get_alternative_candidate_info($row['alternative_id']);
		if($row['score'] < $previous_score){
			echo $rank;
			$previous_rank = $rank;
		}
		else{
			echo $previous_rank;
		}
		echo ". <a href=\"index.php?type=member&action=view&id=" . $alternative_candidate_info['user_id'] . "\" class=\"invisible-link\">" . $alternative_candidate_info['user_name'] . "</a><br>";
		$previous_score = $row['score'];
		$rank++;
	}

}

public static function calculate_and_output_workgroup_election_result ($result_array, $workgroup_id){

	$rank = 1;
	$previous_rank = 1;
	$previous_score = PHP_INT_MAX;
	$number_of_winners = db_workgroup::get_number_of_members($workgroup_id);
	foreach($result_array as $row){
		$alternative_candidate_info = db_vote::get_alternative_candidate_info($row['alternative_id']);
		if($row['score'] < $previous_score){
			echo $rank;
			$previous_rank = $rank;
		}
		else{
			echo $previous_rank;
		}
		echo ". <a href=\"index.php?type=member&action=view&id=" . $alternative_candidate_info['user_id'] . "\" class=\"invisible-link\">";
		if(db_workgroup::is_member($workgroup_id, $alternative_candidate_info['user_id'])){
			echo "<strong>" . $alternative_candidate_info['user_name'] . "</strong>";
		}
		else{
			echo $alternative_candidate_info['user_name'];
		}
		echo "</a><br>";
		if($rank == $number_of_winners){
			echo "<hr><br>";
		}
		$previous_score = $row['score'];
		$rank++;
	}

}

public static function make_result_array_of_json_prio_ranking ($prio_ranking){

	$prio_ranking_array = json_decode($prio_ranking, true);

	$ballot = Array();

	foreach($prio_ranking_array as $key => $value){
		$ballot[] = Array("alternative_id" => $key, "score" => $value);
	}

	return $ballot;

}

public static function find_user_delegate_matching_constituencies ($user_id, $delegate_id){

	$user_constituencies = db_constituency::get_constituencies_for_user($user_id);

	$matching_constituencies = Array();

	foreach($user_constituencies as $row){
		$delegate_constituency_access = db_constituency::check_delegate_constituency_access($delegate_id, $row['id']);
		if($delegate_constituency_access){
			$matching_constituencies[] = Array("id" => $row['id'], "name" => $row['name']);
		}
	}

	return $matching_constituencies;

}

public static function substitute_active_for_passive_user_codes ($vote_id){

	$ballot_user_codes_for_ended_vote = db_vote_admin::get_user_codes_for_vote($vote_id);

	$ballot_user_codes_for_ended_vote_serialized = serialize($ballot_user_codes_for_ended_vote);

	$post_vars = Array("user_codes" => $ballot_user_codes_for_ended_vote_serialized);
	$reply = crypt_helpers::curl_to_anon_server("get_passive_user_codes.php", $post_vars);
	$passive_user_codes = unserialize($reply);

	foreach ($ballot_user_codes_for_ended_vote as $key => $value) {
		$active_user_code = $key;
		$passive_user_code = $value;

		if(!empty($active_user_code) && !empty($passive_user_code)){
			db_vote_admin::set_active_user_code_to_passive($active_user_code, $passive_user_code, $vote_id);
		}
	}

	return;

}

public static function restore_active_user_codes ($vote_id){

	$ballot_user_codes_for_ended_vote = db_vote_admin::get_user_codes_for_vote($vote_id);

	$ballot_user_codes_for_ended_vote_serialized = serialize($ballot_user_codes_for_ended_vote);

	$post_vars = Array("user_codes" => $ballot_user_codes_for_ended_vote_serialized);
	$reply = crypt_helpers::curl_to_anon_server("get_active_user_code_for_passive.php", $post_vars);
	$active_user_codes = unserialize($reply);

	foreach ($ballot_user_codes_for_ended_vote as $row) {
		$passive_user_code = $row['user_code'];
		$active_user_code = $active_user_codes[$passive_user_code];

		if(!empty($passive_user_code) && !empty($active_user_code)){
			db_vote_admin::set_passive_user_code_to_active($active_user_code, $passive_user_code, $vote_id);
		}
	}

	return;

}

public static function output_yes_no_result ($list_of_votes){

	$ballot_counter = vote_helpers::ballot_count_yes_no_abstain($list_of_votes);

	if($ballot_counter['yes'] > 0 || $ballot_counter['no'] > 0){
		$yes_percentage = round($ballot_counter['yes'] / ($ballot_counter['yes'] + $ballot_counter['no']), 4) * 100;
	}
	else{
		$yes_percentage = 0;
	}
	
	if($ballot_counter['no'] == 0){
		$no_percentage = 0; 
	}
	else{
		$no_percentage = 100 - $yes_percentage;
	}

	echo "Ställningen i denna omröstning är: <br>";
	echo "Ja: " . $ballot_counter['yes'] . " (" . $yes_percentage . " %)<br>";
	echo "Nej: " . $ballot_counter['no'] . " (" . $no_percentage . " %)<br>";
	echo "Avstår: ". $ballot_counter['abstain'] . "<br><br>";

	return;

}

public static function output_median_result ($list_of_votes){

	$ballot_counter = vote_helpers::ballot_count_median($list_of_votes);

	echo "Ställningen i denna omröstning är: <br>";
	echo "Medianvärde: " . $ballot_counter. "<br><br>";

	return;

}

public static function output_prio_vote_result ($vote_id){

	$prio_vote_result = vote_helpers::calculate_prio_vote_result($vote_id);

	echo "Ställningen i denna omröstning är: <br><p>";

	if(empty($prio_vote_result)){
		echo "Inga alternativ att visa.";
	}
	else{
		vote_helpers::calculate_and_output_prio_vote_result($prio_vote_result);
	}

	echo "</p>";

	return;

}

public static function output_candidate_election_result ($vote_id){

	$prio_vote_result = vote_helpers::calculate_prio_vote_result($vote_id);

	echo "Ställningen i denna omröstning är: <br><p>";

	if(empty($prio_vote_result)){
		echo "Inga kandidater att visa.";
	}
	else{
		vote_helpers::calculate_and_output_candidate_election_result($prio_vote_result);
	}

	echo "</p>";

	return;

}

public static function output_workgroup_election_result ($vote_id, $workgroup_id){

	$prio_vote_result = vote_helpers::calculate_prio_vote_result($vote_id);

	echo "Kandidater ovanför strecket är valda till arbetsgruppen, kandidater i fetstil är de som för närvarande upptar platserna: <br><p>";

	if(empty($prio_vote_result)){
		echo "Inga kandidater att visa.";
	}
	else{
		vote_helpers::calculate_and_output_workgroup_election_result($prio_vote_result, $workgroup_id);
	}

	echo "</p>";

	return;

}

public static function change_county_region_constituencies ($user_id, $county){

	$old_county_constituency_id = db_constituency::get_local_county_constituency_for_user($user_id);
	$old_region_constituency_id = db_constituency::get_local_region_constituency_for_user($user_id);

	$new_county_constituency_id = db_constituency::get_local_county_constituency($county);
	$new_region = db_helpers::get_region_from_county($_POST['county']);
	$new_region_constituency_id = db_constituency::get_local_region_constituency($new_region);

	db_constituency::remove_constituency_access($user_id, $old_county_constituency_id);
	db_constituency::remove_constituency_access($user_id, $old_region_constituency_id);

	db_constituency::add_constituency_access($user_id, $new_county_constituency_id);
	db_constituency::add_constituency_access($user_id, $new_region_constituency_id);

	return;
}

public static function workgroup_election_compare_result ($vote_id){

	$voteinfo = db_vote::get_vote_info($vote_id);
	$workgroup_id = $voteinfo['from_proposition_id'];
	$number_of_winners = db_workgroup::get_number_of_members($workgroup_id);

	$election_result = vote_helpers::calculate_prio_vote_result($vote_id);
	$election_result_winners = array_slice($election_result, 0, $number_of_winners);

	$election_winners = Array();
	foreach($election_result_winners as $row){
		$election_winners[] = db_vote::get_alternative_user_id($row['alternative_id']);
	}

	$workgroup_members = db_workgroup::get_member_ids($workgroup_id);

	$members_in = array_diff($election_winners, $workgroup_members);
	$members_out = array_diff($workgroup_members, $election_winners);

	$members_in_from_db = db_workgroup::get_workgroup_election_members_in($workgroup_id);
	$members_out_from_db = db_workgroup::get_workgroup_election_members_out($workgroup_id);

	$new_members_in = array_diff($members_in, $members_in_from_db);
	$new_members_out = array_diff($members_out, $members_out_from_db);

	$old_members_in = array_diff($members_in_from_db, $members_in);
	$old_members_out = array_diff($members_out_from_db, $members_out);

	for($i=0; $i<count($new_members_in); $i++){
		if(isset($new_members_out[$i])){
			db_workgroup::insert_workgroup_election_changes($workgroup_id, $new_members_in[$i], $new_members_out[$i]);
		}
		elseif(!empty($old_members_in)){
			$member_out_to_pair_with = db_workgroup::get_workgroup_election_changes_for_member_in($workgroup_id, $old_members_in[0]);
			db_workgroup::delete_workgroup_election_changes($member_out_to_pair_with['id']);
			db_workgroup::insert_workgroup_election_changes($workgroup_id, $new_members_in[$i], $member_out_to_pair_with['user_id_out']);

			// Removing user_id from old_members_in
			unset($old_members_in[0]);
			if(!empty($old_members_in)){
				$old_members_in = array_values($old_members_in);
			}
		}
		else{
			db_workgroup::insert_workgroup_election_changes($workgroup_id, $new_members_in[$i], null);
		}
	}

	return;
}

public static function get_prio_vote_result_for_single_voter ($vote_id, $prio_ranking){

	$vote_type = db_vote::get_vote_type_from_id($vote_id);

	$alternatives = db_vote::get_alternative_ids_from_vote_id($vote_id);

	$result_array = Array();

	foreach($alternatives as $row){
		$alternative_id = $row[0];
		if(isset($prio_ranking[$alternative_id])){
			$score = $prio_ranking[$alternative_id];
		}
		else{
			$score = 0;
		}
		$result_array[] = Array("alternative_id" => $row[0], "score" => $score, "created" => 0);
	}

	usort($result_array, function($a, $b) 
	{ 
		$score_compare = $b["score"] - $a["score"];
		if($score_compare == 0){
			return $a["created"] - $b["created"];
		}
		return $score_compare; 
	});

	if($vote_type == "prio-vote"){
		vote_helpers::calculate_and_output_prio_vote_result($result_array);
	}
	elseif($vote_type == "candidate-election"){
		vote_helpers::calculate_and_output_candidate_election_result($result_array);
	}
	elseif($vote_type == "workgroup-election"){
		$voteinfo = db_vote::get_vote_info($vote_id);
		vote_helpers::calculate_and_output_workgroup_election_result($result_array, $voteinfo['from_proposition_id']);
	}

}

public static function sort_prio_ranking ($prio_ranking){
	// Ordering JSON prio ranking so that highest rank is top and lowest rank bottom
	$prio_ranking_array = json_decode($prio_ranking, true);
	arsort($prio_ranking_array, SORT_NUMERIC);
	$sorted_prio_ranking = json_encode($prio_ranking_array);

	return $sorted_prio_ranking;
}

public static function get_vote_groups() 
{
	$page = isset($_GET['page']) ? $_GET['page'] : 1;
	$sort = isset($_GET['sort']) ? $_GET['sort'] : null;
	$votes = db_vote::list_active_votes($sort, $page);
	return self::group_vote_entities($votes);
}

public static function get_prop_groups() 
{
	$page = isset($_GET['page']) ? $_GET['page'] : 1;
	$sort = isset($_GET['sort']) ? $_GET['sort'] : null;
	$props = db_prop::list_active_props($sort, $page);
	return self::group_vote_entities($props);
}

public static function make_vote_list_header() 
{
	self::make_list_header(db_vote::list_active_votes_count());
}

public static function make_prop_list_header() 
{
	self::make_list_header(db_prop::list_active_props_count());
}

private static function group_vote_entities($rows) 
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
	$vote_group = Vote_group::create();
	$vote_groups[$constituency] = $vote_group;
	return $vote_group;
}

private static function make_list_header($res_count) 
{
	$page = isset($_GET['page']) ? $_GET['page'] : 1;
	$sort_alternatives = Array("Skapad" => "created", "Alfabetisk" => "alphabetic");
	general_helpers::make_list_of_links_header($page, $res_count, $sort_alternatives); 
}

} //End of class

class Vote_group {
	public $constituency;
	public $votes = array();

	public static function create() {
		$vote_group = new vote_group();
		$vote_group->votes = array();
		return $vote_group;
	}

	public function add_vote($vote) {
		if ($this->constituency == null)
			$this->constituency = $vote["constituency"];
		else if ($this->constituency != $vote["constituency"])
			throw new Exception("Cannot mix votes from different constituencies in same vote group.
				Tried to add " . $vote["constituency"] . " to ". $this->constituency);
		array_push($this->votes, $vote);
	}
} 

?>