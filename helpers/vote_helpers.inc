<?

class vote_helpers {


public static function ballot_count_yes_no_abstain ($array_of_ballots){

	$yes = 0;
	$no = 0;
	$abstain = 0;

	foreach($array_of_ballots as $row){
	    if($row['alternative'] == "yes") $yes++;
	    elseif($row['alternative'] == "no") $no++;
	    elseif($row['alternative'] == "abstain") $abstain++;
	}

	return Array("yes" => $yes, "no" => $no, "abstain" => $abstain);

}

public static function ballot_count_median ($array_of_ballots){

	$count = count($array_of_ballots);

	if($count == 0){
		return "Inget värde satt";
	}
	else{
		$array_of_values = array();
		foreach ($array_of_ballots as $item) {
    		$array_of_values[] = $item['value'];
		}

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

public static function register_delegate_ballot ($vote_id, $delegate_id, $ballot){

	$type = db_vote::get_vote_type_from_id($vote_id);

	if($type == "yes-no"){
		$ballot_decoded = json_decode($ballot, true);
		return db_delegate::register_yes_no_ballot($vote_id, $delegate_id, $ballot_decoded['alternative']);
	}
	elseif($type == "median"){
		$ballot_decoded = json_decode($ballot, true);
		return db_delegate::register_median_ballot($vote_id, $delegate_id, $ballot_decoded['value']);
	}
	elseif($type == "prio-vote" || $type == "candidate-election"){
		$ballot_decoded = json_decode($ballot, true);
		return db_delegate::register_prio_ballot($vote_id, $delegate_id, json_encode($ballot_decoded['prio_ranking']));
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

		$result_array[] = Array("alternative_id" => $result_row[0], "score" => $row_sum);
	}

	usort($result_array, function($a, $b) { return $b["score"] - $a["score"]; });

	return $result_array;	

}

public static function output_prio_vote_result ($result_array){

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

public static function output_candidate_election_result ($result_array){

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

public static function make_result_array_of_json_prio_ranking ($prio_ranking){

	$prio_ranking_array = json_decode($prio_ranking, true);

	$ballot = Array();

	foreach($prio_ranking_array as $key => $value){
		$ballot[] = Array("alternative_id" => $key, "score" => $value);
	}

	return $ballot;

}

} //End of class