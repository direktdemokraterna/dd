<?php

class vote_helpers 
{
	public static function ballot_count_yes_no_abstain ($ballots_to_count)
	{
		$yes = 0;
		$no = 0;
		$abstain = 0;
		foreach($ballots_to_count as $ballot){
		    if($ballot['ballot'] == "yes") $yes++;
		    elseif($ballot['ballot'] == "no") $no++;
		    elseif($ballot['ballot'] == "abstain") $abstain++;
		}
		return Array("yes" => $yes, "no" => $no, "abstain" => $abstain);
	}

	public static function ballot_count_median ($ballots_to_count)
	{
		$array_of_values = array();
		foreach ($ballots_to_count as $ballot)
	   		if(is_numeric($ballot['ballot']))
   				$array_of_values[] = $ballot['ballot'];
		$count = count($array_of_values);
		if($count == 0)
			return _t("No value");
		$middle_index = floor($count / 2);
		sort($array_of_values, SORT_NUMERIC);
		$median = $array_of_values[$middle_index]; // assume an odd # of items

		// Handle the even case by averaging the middle 2 items
		if ($count % 2 == 0)
			$median = ($median + $array_of_values[$middle_index - 1]) / 2;
		return $median;
	}

	public static function get_complete_list_of_user_delegations ()
	{
		$list_of_delegations = db_delegate::get_complete_list_of_user_delegations();
		echo "<script>var ballots_to_count = " . \View\general::db_result_to_json($list_of_delegations) . ";</script>";
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

	public static function get_formatted_candidate_election_result ($result_array)
	{
		$ret_val = '';
		$rank = 1;
		$previous_rank = 1;
		$previous_score = PHP_INT_MAX;
		foreach($result_array as $row){
			$alternative_candidate_info = db_vote::get_alternative_candidate_info($row['alternative_id']);
			if($row['score'] < $previous_score){
				$ret_val .= $rank;
				$previous_rank = $rank;
			}
			else
				$ret_val .= $previous_rank;
			$ret_val .= ". <a href=\"index.php?type=member&action=view&id=" . $alternative_candidate_info['user_id'] . "\" class=\"invisible-link\">" . $alternative_candidate_info['user_name'] . "</a><br>";
			$previous_score = $row['score'];
			$rank++;
		}
		return $ret_val;
	}

	public static function get_formatted_workgroup_election_result ($result_array, $workgroup_id)
	{
		$ret_val = '';
		$rank = 1;
		$previous_rank = 1;
		$previous_score = PHP_INT_MAX;
		$number_of_winners = db_workgroup::get_number_of_members($workgroup_id);
		foreach($result_array as $row){
			$alternative_candidate_info = db_vote::get_alternative_candidate_info($row['alternative_id']);
			if($row['score'] < $previous_score){
				$ret_val .= $rank;
				$previous_rank = $rank;
			}
			else
				$ret_val .= $previous_rank;
			$ret_val .= ". <a href=\"index.php?type=member&action=view&id=" . $alternative_candidate_info['user_id'] . "\" class=\"invisible-link\">";
			if(db_workgroup::is_member($workgroup_id, $alternative_candidate_info['user_id']))
				$ret_val .= "<strong>" . $alternative_candidate_info['user_name'] . "</strong>";
			else
				$ret_val .= $alternative_candidate_info['user_name'];
			$ret_val .= "</a><br>";
			if($rank == $number_of_winners)
				$ret_val .= "<hr><br>";
			$previous_score = $row['score'];
			$rank++;
		}
		return $ret_val;
	}

	public static function make_result_array_of_json_prio_ranking ($prio_ranking)
	{
		$prio_ranking_array = json_decode($prio_ranking, true);
		$ballot = Array();
		foreach($prio_ranking_array as $key => $value)
			$ballot[] = Array("alternative_id" => $key, "score" => $value);
		return $ballot;
	}

	public static function find_shared_constituencies ($voter_id, $delegate_id)
	{
		$voter_constituencies = db_constituency::get_constituencies_for_voter($voter_id);
		$matching_constituencies = Array();
		foreach($voter_constituencies as $row){
			$delegate_constituency_access = db_constituency::check_voter_constituency_access($delegate_id, $row['id']);
			if($delegate_constituency_access)
				$matching_constituencies[] = $row;
		}
		return $matching_constituencies;
	}

	public static function generate_yes_no_result ($ballots_to_count)
	{
		$ballot_counter = vote_helpers::ballot_count_yes_no_abstain($ballots_to_count);
		$yes_percentage = $ballot_counter['yes'] || $ballot_counter['no']
			? round($ballot_counter['yes'] / ($ballot_counter['yes'] + $ballot_counter['no']), 4) * 100
			: 0;
		$no_percentage = $ballot_counter['no']
			? 100 - $yes_percentage
			: 0;
		return _t("Yes: ") . $ballot_counter['yes'] . " (" . $yes_percentage . " %)<br>"
			. _t("No: ") . $ballot_counter['no'] . " (" . $no_percentage . " %)<br>"
			. _t("Abstain: ") . $ballot_counter['abstain'] . "<br>";
	}

	public static function generate_median_result ($ballots_to_count)
	{
		$ballot_counter = vote_helpers::ballot_count_median($ballots_to_count);
		return $ballot_counter . "<br>";
	}

	public static function generate_prio_vote_result ($vote_id)
	{
		$prio_vote_result = vote_helpers::calculate_prio_vote_result($vote_id);
		return empty($prio_vote_result)
			? __t("No alternatives")
			: self::get_formatted_prio_vote_result($prio_vote_result);
	}

	public static function generate_candidate_election_result ($vote_id)
	{
		$prio_vote_result = vote_helpers::calculate_prio_vote_result($vote_id);
		return empty($prio_vote_result)
			? _t("No candidates")
			: self::get_formatted_candidate_election_result($prio_vote_result);
	}

	public static function generate_workgroup_election_result ($vote_id, $workgroup_id)
	{
		$prio_vote_result = vote_helpers::calculate_prio_vote_result($vote_id);
		return empty($prio_vote_result)
			? _t("No candidates")
			: self::get_formatted_workgroup_election_result($prio_vote_result, $workgroup_id);
	}

	public static function get_formatted_prio_vote_result ($result_array)
	{
		$ret_val = '';
		$rank = 1;
		$previous_rank = 1;
		$previous_score = PHP_INT_MAX;
		foreach($result_array as $row){
			$alternative_title = db_vote::get_alternative_title($row['alternative_id']);
			if($row['score'] < $previous_score){
				$ret_val .= $rank;
				$previous_rank = $rank;
			}
			else
				$ret_val .= $previous_rank;
			$ret_val .= ". " . $alternative_title . "<br>";
			$previous_score = $row['score'];
			$rank++;
		}
		return $ret_val;
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
	}

	public static function get_prio_vote_result_for_single_voter ($vote_id, $prio_ranking)
	{
		$vote_type = db_vote::get_vote_type_from_id($vote_id);
		$alternatives = db_vote::get_alternative_ids_from_vote_id($vote_id);
		$result_array = Array();
		foreach($alternatives as $row){
			$alternative_id = $row[0];
			$score = isset($prio_ranking[$alternative_id]) 
				? $prio_ranking[$alternative_id]
				: 0;
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
		switch ($vote_type) {
			case "prio-vote": 
				return vote_helpers::get_formatted_prio_vote_result($result_array);
			case "candidate-election":
				return vote_helpers::get_formatted_candidate_election_result($result_array);
			case "workgroup-election":
				$voteinfo = db_vote::get_vote_info($vote_id);
				return vote_helpers::get_formatted_workgroup_election_result($result_array, $voteinfo['from_proposition_id']);
			default: throw new Exception("Unknown vote_type: " . $vote_type);
		}
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