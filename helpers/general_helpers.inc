<?php

class general_helpers {


public static function GenerateRandomString ($length){

	$Allowed_Chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';

	$random_string = "";
	for($i=0; $i<$length; $i++)
	{
    	$random_string .= $Allowed_Chars[mt_rand(0,61)];
	}

	return $random_string;

}

public static function make_genitive ($string){

	if(substr($string, -1) == "s" || substr($string, -1) == "S"){
		$return_string = $string;
	}
	else{
		$return_string = $string . "s";
	}

	return $return_string;

}


public static function check_report_messages (){

	if(isset($_SESSION['report_message'])){
		if(isset($_SESSION['red_report_message'])){
			$return_message = "<div class=\"red_message\">" . $_SESSION['report_message'] . "</div>";
			unset($_SESSION['red_report_message']);
		}
		else{
			$return_message = "<div class=\"green_message\">" . $_SESSION['report_message'] . "</div>";
		}
		unset($_SESSION['report_message']);
	}
	else{
		$return_message = "";
	}

	return $return_message;

}


public static function show_date ($time){

	$tested_time = getdate($time);
	$tested_time_yesterday = getdate($time+86400);
	$tested_time_tomorrow = getdate($time-86400);
	$present_time = getdate(time());

	if($tested_time['yday']==$present_time['yday'] && $tested_time['year']==$present_time['year'])
		$dag = "Idag";
	elseif($tested_time_yesterday['yday']==$present_time['yday'] && $tested_time_yesterday['year']==$present_time['year'])
		$dag = "Igår";
	elseif($tested_time_tomorrow['yday']==$present_time['yday'] && $tested_time_tomorrow['year']==$present_time['year'])
		$dag = "Imorgon";
	else{
		$dag = date("j/n", $time);
	}

	if($tested_time['year']==$present_time['year'])
		$ar = "";
	else{
		$ar = "-" . date("Y", $time);
	}

	$time_of_day = " " . date("H:i",$time);

	return($dag . $ar . $time_of_day);

}

public static function veckodag ($timestamp, $weekday = null){

	if($timestamp > 0){
		$weekday = date("w", $timestamp); 
	}

	if($weekday == 0) return "Söndag";
	elseif($weekday == 1) return "Måndag";
	elseif($weekday == 2) return "Tisdag";
	elseif($weekday == 3) return "Onsdag";
	elseif($weekday == 4) return "Torsdag";
	elseif($weekday == 5) return "Fredag";
	elseif($weekday == 6) return "Lördag";
	
}

public static function manad ($timestamp, $month = null){

	if($timestamp > 0){
		$month = date("n", $timestamp); 
	}

	if($month == 1) return "Januari";
	elseif($month == 2) return "Februari";
	elseif($month == 3) return "Mars";
	elseif($month == 4) return "April";
	elseif($month == 5) return "Maj";
	elseif($month == 6) return "Juni";
	elseif($month == 7) return "Juli";
	elseif($month == 8) return "Augusti";
	elseif($month == 9) return "September";
	elseif($month == 10) return "Oktober";
	elseif($month == 11) return "November";
	elseif($month == 12) return "December";
	
}


public static function admin_mail ($receiver, $title, $text) {
	// https://github.com/PHPMailer/PHPMailer
	require_once('PHPMailer-master/PHPMailerAutoload.php');
 
	$mail = new PHPMailer();
 
	$mail->From = 'direktdemokraterna@hotmail.com';
	$mail->FromName = 'Direktdemokraterna';
	$mail->AddAddress($receiver);
	$mail->Subject = $title;
	$mail->Body = $text;

	$mail->IsSMTP();
	$mail->SMTPAuth = true;
	$mail->SMTPSecure = 'tls';
	$mail->Port = 587;
//	$mail->Host = 'smtp.gmail.com';
//	$mail->Username = 'direktdemokraterna.test@gmail.com';
//	$mail->Password = '475954952T13bwy';

	$mail->Host = 'smtp-mail.outlook.com';
	$mail->Username = 'direktdemokraterna@hotmail.com';
	$mail->Password = '475954952T13bwy';


	if(!$mail->send()) {
	    return $mail->ErrorInfo;
	} 
	else {
    	return "success";
	}
}



// makes the top links for choosing page and sorting alternatives for a list_of_links
public static function make_list_of_link_menu ($page, $result_counter, $sort_alternatives = null, $filter_title = "Filtrering:", $filter_alternatives = null){

	$number_of_pages = ceil($result_counter / LIST_ITEMS_PER_PAGE);
	if($result_counter == 0){
		$first_showed_item_number = 0;
	}
	else{
		$first_showed_item_number = $page * LIST_ITEMS_PER_PAGE - (LIST_ITEMS_PER_PAGE - 1);
	}
	$last_showed_item_number = $page * LIST_ITEMS_PER_PAGE;
	if($last_showed_item_number > $result_counter) $last_showed_item_number = $result_counter;

	$get_parameters = $_GET;

	echo "<div class=\"list_of_link_menu\">";
	echo "<span class=\"list_counter\">";
	echo $first_showed_item_number . " - " . $last_showed_item_number . " av totalt " . $result_counter;
	echo "</span>";

	if($sort_alternatives){
		echo "<span class=\"list_sort_alternative\">Sortering: </span>";
		foreach($sort_alternatives as $key => $value){
			echo "<span class=\"list_sort_alternative\">";
			$get_parameters['sort'] = $value;
			$url = "index.php?" . http_build_query($get_parameters);
		
			echo "<a href=\"index.php?" . http_build_query($get_parameters) . "\">" . $key . "</a></span>";
		}
	}

	echo "</div>";

	if($filter_alternatives){
		echo "<div class=\"list_of_link_menu\">";
		echo "<span class=\"list_sort_alternative\">" . $filter_title . "</span>";
		foreach($filter_alternatives as $key => $value){
			echo "<span class=\"list_sort_alternative\">";
			$get_parameters['filter'] = $value;
			$url = "index.php?" . http_build_query($get_parameters);
		
			echo "<a href=\"index.php?" . http_build_query($get_parameters) . "\">" . $key . "</a></span>";
		}
		echo "</div>";
	}

	elseif($filter_title == "county_regions"){
		echo "<div class=\"list_of_link_menu\">";
		
		echo "<span class=\"list_sort_alternative\">Län: ";
		$regions = db_helpers::get_regions();
		echo "<select class=\"standard-form\" onchange='window.location.href=this.value'>";

		$get_parameters['region'] = null;
		$get_parameters['filter'] = null;
		$url = "index.php?" . http_build_query($get_parameters);
		echo "<option value=\"" . $url . "\">Alla län</option>";

		$get_parameters['filter'] = "region";
		foreach($regions as $row){
			$get_parameters['region'] = $row['lan'];
			$url = "index.php?" . http_build_query($get_parameters);
			echo "<option value=\"" . $url . "\"";
			if(isset($_GET['region']) && $row['lan'] == $_GET['region']) echo " selected";
			echo ">" . $row['lan'] . "</option>\n";
		}
		echo "</select>";
		if(isset($_GET['region'])){
			$get_parameters['region'] = $_GET['region'];
		}

		echo "<span class=\"list_sort_alternative\">Kommun: ";
		if(isset($_GET['region'])){
			$counties = db_helpers::get_counties_for_region($_GET['region']);
		}
		else{
			$counties = db_helpers::get_counties();
		}
		echo "<select class=\"standard-form\" onchange='window.location.href=this.value'>";

		$get_parameters['county'] = null;
		if(isset($_GET['region'])){
			$get_parameters['filter'] = "region";
		}
		else{
			$get_parameters['filter'] = null;
		}
		$url = "index.php?" . http_build_query($get_parameters);
		echo "<option value=\"". $url . "\">Alla kommuner</option>";

		$get_parameters['filter'] = "county";
		foreach($counties as $row){
			$get_parameters['county'] = $row['kommun'];
			$url = "index.php?" . http_build_query($get_parameters);
			echo "<option value=\"" . $url . "\"";
			if(isset($_GET['county']) && $row['kommun'] == $_GET['county']) echo " selected";
			echo ">" . $row['kommun'] . "</option>\n";
		}
		echo "</select></span>";
		$get_parameters['county'] = null;

		echo "</span></div>";
	}


}

public static function find_max_in_multidimensional_array ($array, $key) {

	if (!is_array($array) || count($array) == 0){
		return false;
	}

	$max = $array[0][$key];
	foreach($array as $array_row) {
		if($array_row[$key] > $max) {
			$max = $array_row[$key];
		}
	}
	return $max;

}

public static function find_min_in_multidimensional_array ($array, $key) {

	if (!is_array($array) || count($array) == 0){
		return false;
	}

	$min = $array[0][$key];
	foreach($array as $array_row){
		if($array_row[$key] < $min) {
			$min = $array_row[$key];
		}
	}
	return $min;

}

public static function in_multiarray ($array, $key, $value) {

	foreach($array as $array_row){
		if($array_row[$key] == $value){
			return true;
		}
	}

	return false;

}

public static function check_personnummer ($personnummer) { 

	$personnummer = str_replace("-", "", $_POST['social_security_number']);
	if(strlen($personnummer) > 10){
		$personnummer = substr($personnummer, 2);
	}

	$n = 2; 
	$control_sum = 0;
	for ($i=0; $i<9; $i++){ 
		$temp = $personnummer[$i] * $n; 
		if($temp > 9){
			$control_sum += 1 + ($temp % 10);
		}
		else{
			$control_sum += $temp; 
		}

		if($n == 2){
			$n = 1;
		}
		else{
			$n = 2; 
		}
	} 

	$control_digit = (10 - $control_sum % 10) % 10;
	
	if($control_digit == $personnummer[9]){
		return true;
	}
	else{
		return false; 
	}

}

public static function clean ($data) { 

	return htmlspecialchars($data, ENT_COMPAT,'ISO-8859-1', true);

}

} //End of class