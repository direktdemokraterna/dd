<?php

class general_helpers {
	private static $ALPHANUMERIC_CHARS = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
	private static $WEEK_DAY_NAMES = array("Söndag", "Måndag", "Tisdag", "Onsdag", "Torsdag", "Fredag", "Lördag");
	private static $MONTH_NAMES = array("NO_MONTH", "Januari", "Februari", "Mars", "April", "Maj", "Juni", "Juli", "Augusti", "September", "Oktober", "November", "December");
	private static $DAY_IN_SECONDS = 86400;

	public static function GenerateRandomString ($length){
		$random_string = "";
		for($i=0; $i<$length; $i++)
			$random_string .= self::$ALPHANUMERIC_CHARS[mt_rand(0,61)];
		return $random_string;
	}

	public static function make_genitive ($string){
		return self::is_genitive($string) ? $string : $string . "s";
	}

	private static function is_genitive ($str){
		return strlen($str) > 0 && strtolower(substr($str, -1)) == "s";
	}

	public static function check_report_messages (){
		$return_message = self::generate_report_message();
		self::unset_report_message_flags();
		return $return_message;
	}

	private static function generate_report_message (){
		return isset($_SESSION['report_message'])
			? "<div class=\"" . self::get_report_message_class() . "\">" . $_SESSION['report_message'] . "</div>"
			: "";
	}

	private static function get_report_message_class (){
		return isset($_SESSION['red_report_message']) ? "red_message" : "green_message";
	}

	private static function unset_report_message_flags (){
		self::unset_flag('report_message');
		self::unset_flag('red_report_message');
	}

	private static function unset_flag ($flag){
		if(isset($_SESSION[$flag]))
		unset($_SESSION[$flag]);
	}

	public static function show_date ($time){
		$present_time = getdate(time());
		$dag = self::get_pretty_day_representation($time, $present_time);
		$ar = self::get_pretty_year_representation($time, $present_time);
		$time_of_day = " " . date("H:i",$time);
		return $dag . $ar . $time_of_day;
	}

	private static function get_pretty_day_representation ($time, $present_time){
		$tested_time = getdate($time);
		$tested_time_next_day = getdate($time+self::$DAY_IN_SECONDS);
		$tested_time_previous_day = getdate($time-self::$DAY_IN_SECONDS);
		if(self::is_same_day($tested_time, $present_time))
		return "Idag";
		if(self::is_same_day($tested_time_next_day, $present_time))
		return "Igår";
		if(self::is_same_day($tested_time_previous_day, $present_time))
		return "Imorgon";
		return date("j/n", $time);
	}
	
	private static function is_same_day($firstDate, $secondDate) {
		return $firstDate['yday']==$secondDate['yday'] && $firstDate['year']==$secondDate['year'];
	}

	private static function get_pretty_year_representation ($time, $present_time){
		$tested_time = getdate($time);
		return $tested_time['year']==$present_time['year']
			? ""
			: "-" . date("Y", $time);
	}

	public static function veckodag ($timestamp, $weekday = 0){
		$weekday = $timestamp > 0 
			? date("w", $timestamp) 
			: $weekday;
		return self::$WEEK_DAY_NAMES[$weekday];
	}

	public static function manad ($timestamp, $month = 0){
		$month = $timestamp > 0 
			? date("n", $timestamp) 
			: $month;
		return self::$MONTH_NAMES[$month];
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
		$mail->Host = 'smtp-mail.outlook.com';
		$mail->Username = 'direktdemokraterna@hotmail.com';
		$mail->Password = '475954952T13bwy';
		return $mail->send() 
			? "success" 
			: $mail->ErrorInfo;
	}
	
	public static function make_list_of_link_menu1 ($page, $result_counter, $sort_alternatives = null, $filter_title = "Filtrering:", $filter_alternatives = null){
		$number_of_pages = ceil($result_counter / LIST_ITEMS_PER_PAGE);
		if($result_counter == 0)
		$first_showed_item_number = 0;
		else
			$first_showed_item_number = $page * LIST_ITEMS_PER_PAGE - (LIST_ITEMS_PER_PAGE - 1);
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
			$get_parameters['county'] = null;
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
			if(isset($_GET['region']))
			$get_parameters['region'] = $_GET['region'];
			echo "<span class=\"list_sort_alternative\">Kommun: ";
			if(isset($_GET['region']))
			$counties = db_helpers::get_counties_for_region($_GET['region']);
			else
				$counties = db_helpers::get_counties();
			echo "<select class=\"standard-form\" onchange='window.location.href=this.value'>";
			if(isset($_GET['region']))
			$get_parameters['filter'] = "region";
			else
				$get_parameters['filter'] = null;
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
	
	// makes the top links for choosing page and sorting alternatives for a list_of_links
	public static function make_list_of_link_menu ($page, $result_counter, $sort_alternatives = null, $filter_title = "Filtrering:", $filter_alternatives = null){
		$number_of_pages = ceil($result_counter / LIST_ITEMS_PER_PAGE);
		$first_showed_item_number = $result_counter > 0
			? $page * LIST_ITEMS_PER_PAGE - (LIST_ITEMS_PER_PAGE - 1)
			: 0;
		$last_showed_item_number = min($page * LIST_ITEMS_PER_PAGE, $result_counter);
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
				self::makeLink($get_parameters, $key);
			}
		}
		echo "</div>";
		if($filter_alternatives){
			echo "<div class=\"list_of_link_menu\">";
			echo "<span class=\"list_sort_alternative\">" . $filter_title . "</span>";
			foreach($filter_alternatives as $key => $value){
				echo "<span class=\"list_sort_alternative\">";
				$get_parameters['filter'] = $value;
				self::makeLink($get_parameters, $key);
				echo("</span>");
			}
			echo "</div>";
		}
		elseif($filter_title == "county_regions"){
			echo "<div class=\"list_of_link_menu\">";
			echo "<span class=\"list_sort_alternative\">Län: ";
			$get_parameters['region'] = null;
			$get_parameters['county'] = null;
			$get_parameters['filter'] = null;
			$regions = db_helpers::get_regions();
			self::makeSelecBox($get_parameters, 'region', $regions, 'lan', "Alla län");
			if(isset($_GET['region']))
				$get_parameters['region'] = $_GET['region'];
			echo "<span class=\"list_sort_alternative\">Kommun: ";
			$get_parameters['filter'] = isset($_GET['region']) ? "region" : null;
			self::makeSelecBox($get_parameters, 'county', self::getCounties(), 'kommun', "Alla kommuner");
			echo "</span>";
			$get_parameters['county'] = null;
			echo "</span></div>";
		}
	}
	
	private static function makeSelecBox($get_parameters, $paramName, $rows, $columnName, $unselectedLabel) {
		echo "<select class=\"standard-form\" onchange='window.location.href=this.value'>";
		self::makeOption($get_parameters, $unselectedLabel);
		$get_parameters['filter'] = $paramName;
		foreach($rows as $row){
			$get_parameters[$paramName] = $row[$columnName];
			$select = isset($_GET[$paramName]) && $row[$columnName] == $_GET[$paramName];
			self::makeOption($get_parameters, $row[$columnName], $select);
		}
		echo "</select>";
	}
	
	private static function makeOption($get_parameters, $label, $selected = false) {
		$url = "index.php?" . http_build_query($get_parameters);
		echo "<option value=\"" . $url . "\"" . ($selected ? " selected" : "") . ">" . $label . "</option>";
	}
	
	private static function getCounties() {
		return isset($_GET['region']) 
			? db_helpers::get_counties_for_region($_GET['region'])
			: db_helpers::get_counties();
	}
	
	private static function makeLink($get_parameters, $key) {
		echo "<a href=\"index.php?" . http_build_query($get_parameters) . "\">" . $key . "</a>";
	}

	public static function find_max_in_multidimensional_array ($array, $key) {
		if (!is_array($array) || count($array) == 0)
		return false;
		$max = $array[0][$key];
		foreach($array as $array_row)
			if($array_row[$key] > $max)
			$max = $array_row[$key];
		return $max;
	}

	public static function find_min_in_multidimensional_array ($array, $key) {
		if (!is_array($array) || count($array) == 0)
		return false;
		$min = $array[0][$key];
		foreach($array as $array_row)
			if($array_row[$key] < $min)
			$min = $array_row[$key];
		return $min;
	}

	public static function in_multiarray ($array, $key, $value) {
		foreach($array as $array_row)
			if($array_row[$key] == $value)
			return true;
		return false;
	}

	public static function clean_personnummer ($personnummer) { 
		$personnummer = str_replace("-", "", $_POST['social_security_number']);
		if(strlen($personnummer) > 10)
		$personnummer = substr($personnummer, 2);
		return $personnummer;
	}

	public static function check_personnummer ($personnummer) { 
		$n = 2; 
		$control_sum = 0;
		for ($i=0; $i<9; $i++){ 
			$temp = $personnummer[$i] * $n; 
			if($temp > 9)
			$control_sum += 1 + ($temp % 10);
			else
				$control_sum += $temp; 
			if($n == 2)
			$n = 1;
			else
				$n = 2; 
		} 
		$control_digit = (10 - $control_sum % 10) % 10;
		if($control_digit == $personnummer[9])
		return true;
		else
			return false; 
	}

	public static function clean ($data) { 
		return htmlspecialchars($data, ENT_COMPAT,'ISO-8859-1', true);
	}

} //End of class