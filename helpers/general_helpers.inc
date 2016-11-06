<?php

class general_helpers {
	private static $ALPHANUMERIC_CHARS = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';

	public static function GenerateRandomString ($length){
		$random_string = "";
		for($i=0; $i<$length; $i++)
			$random_string .= self::$ALPHANUMERIC_CHARS[mt_rand(0,61)];
		return $random_string;
	}

	public static function make_genitive ($string){
		return $string . _t(self::is_genitive($string) ? "'" : "'s");
	}

	public static function show_report_messages (){
		$report_message = self::generate_report_message();
		self::unset_report_message_flags();
		echo $report_message;
	}

	public static function show_date ($time){
		if (!$time) return '';
		$present_time = getdate(time());
		$dag = self::get_pretty_day_representation($time, $present_time);
		$ar = self::get_pretty_year_representation($time, $present_time);
		$time_of_day = " " . date("H:i",$time);
		return $dag . $ar . $time_of_day;
	}

	public static function get_weekday ($timestamp, $weekday = 0){
		$weekday = $timestamp > 0 
			? date("w", $timestamp) 
			: $weekday;
		return _t(\Logic\calendar::$week_day_names[$weekday]);
	}

	public static function get_month($timestamp, $month = 0){
		$month = $timestamp > 0 
			? date("n", $timestamp) 
			: $month;
		return _t(\Logic\calendar::$months[$month]);
	}

	public static function admin_mail ($receiver, $title, $text) {
		// https://github.com/PHPMailer/PHPMailer
		require_once('PHPMailer-master/PHPMailerAutoload.php');
		$mail = new PHPMailer();
		$mail->setFrom('admin@direktdemokraterna.se', 'Direktdemokraterna Admin');
		$mail->addReplyTo('no-reply@direktdemokraterna.se', 'Direktdemokraterna Admin');
		$mail->AddAddress($receiver);
		$mail->Subject = $title;
		$mail->Body = $text;
		$ok = $mail->send();
		return $ok 
			? "success" 
			: $mail->ErrorInfo;
	}
	
	// makes the top links for choosing page and sorting alternatives for a list_of_links
	public static function make_list_of_links_header ($page, $result_counter, $sort_alternatives = null, $filter_title = null, $filter_alternatives = null){
		if (!$filter_title)
			$filter_title = _t("Filtrering:");
		$get_parameters = $_GET;
		self::make_list_paging_and_sorting($get_parameters, $page, $result_counter, $sort_alternatives);
		self::make_generic_list_filter($get_parameters, $filter_title, $filter_alternatives);
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
		if(strlen($personnummer) == 12)
		$personnummer = substr($personnummer, 2);
		if(strlen($personnummer) != 10) return null;
		return $personnummer;
	}

	public static function check_personnummer ($personnummer) { 
		if(strlen($personnummer) != 10) return false;
		$n = 2; 
		$control_sum = 0;
		for ($i=0; $i<9; $i++){ 
			$temp = $personnummer[$i] * $n;
			$control_sum += ($temp > 9 ? 1 + ($temp % 10) : $temp);
			$n = $n == 2 ? 1 : 2;
		}
		$control_digit = (10 - $control_sum % 10) % 10;
		return ($control_digit == $personnummer[9]);
	}

	public static function clean ($data, $flags = ENT_COMPAT, $charset = 'ISO-8859-1', $dblencode = true ) {
		return htmlspecialchars($data, $flags, $charset, $dblencode);
	}
	
	///////////////////////////////////
	/// Private methods starts here ///
	///////////////////////////////////

	private static function is_genitive ($str){
		return strlen($str) > 0 && strtolower(substr($str, -1)) == "s";
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

	private static function get_pretty_day_representation ($time, $present_time){
		$tested_time = getdate($time);
		$tested_time_next_day = getdate($time+DAY_IN_SECONDS);
		$tested_time_previous_day = getdate($time-DAY_IN_SECONDS);
		if(self::is_same_day($tested_time, $present_time))
		return _t("Today");
		if(self::is_same_day($tested_time_next_day, $present_time))
		return _t("Yesterday");
		if(self::is_same_day($tested_time_previous_day, $present_time))
		return _t("Tomorrow");
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
	
	// makes the top links for choosing page and sorting alternatives for a list_of_links
	private static function make_generic_list_filter ($get_parameters, $filter_title = null, $filter_alternatives = null){
		if (!$filter_title)
			$filter_title = _t("Filtering:");
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
	}
	
	public static function make_region_county_list_filter ($extra_filter_controls_html = null){
		$region_id = isset($_GET['region']) ? $_GET['region'] : 0;
		$county_id = isset($_GET['county']) ? $_GET['county'] : 0;
		echo '<form id="filter_list" name="filter_list" method="get" action="">';
		echo '<input type="hidden" name="type" value="' . $_GET['type'] . '"/>';
		echo '<input type="hidden" name="action" value="' . $_GET['action'] . '"/>';
		echo '<div class="list_of_link_menu">';
		echo '<span class="list_sort_alternative">' . _t("Region: ");
		self::makeSelectBox('region', $region_id, \db_constituency::get_regions(), _t("All regions")
			, 'set_default_county_if_region_set();');
		echo '</span>';
		echo '<span class="list_sort_alternative">' . _t("Municipality: ");
		self::makeSelectBox('county', $county_id, self::getCounties($region_id), _t("All municipalities"));
		echo "</span>";
		if ($extra_filter_controls_html)
			echo ($extra_filter_controls_html);
		echo "</div></form>";
	}
	
	public static function make_list_paging_and_sorting ($get_parameters, $page, $result_counter, $sort_alternatives = null){
		echo "<div class=\"list_of_link_menu\">";
		self::make_list_paging($page, $result_counter);
		self::make_list_sorting($get_parameters, $sort_alternatives);
		echo "</div>";
	}
	
	private static function make_list_paging ($page, $result_counter){
		$number_of_pages = ceil($result_counter / LIST_ITEMS_PER_PAGE);
		$first_showed_item_number = $result_counter > 0
			? $page * LIST_ITEMS_PER_PAGE - (LIST_ITEMS_PER_PAGE - 1)
			: 0;
		$last_showed_item_number = min($page * LIST_ITEMS_PER_PAGE, $result_counter);
		echo "<span class=\"list_counter\">";
		echo _t("Showing ") . $first_showed_item_number . " - " . $last_showed_item_number . _t(" of ") . $result_counter;
		echo "</span>";
	}
	
	private static function make_list_sorting ($get_parameters, $sort_alternatives = null){
		if($sort_alternatives){
			echo '<span class="list_sort_alternative">' . _t("Sort order: ") . '</span>';
			foreach($sort_alternatives as $key => $value){
				echo "<span class=\"list_sort_alternative\">";
				$get_parameters['sort'] = $key;
				self::makeLink($get_parameters, $value);
			}
		}
	}

	private static function makeSelectBox($paramName, $selected_value, $rows, $unselectedLabel, $on_change = "") {
		echo '<select class="standard-form" id="' . $paramName . '" name="' . $paramName . 
		'" onchange="' . $on_change . 'this.form.submit();">';
		echo self::generate_option($unselectedLabel);
		foreach($rows as $row)
			echo self::generate_option($row['title'], $row['id'], $selected_value);
		echo "</select>";
	}

	private static function generate_option($label, $value = 0, $selected_value = 0) {
		return '<option value="' . $value . '"' . 
		($value == $selected_value ? ' selected' : '') . '>' . $label . '</option>';
	}
	
	private static function getCounties($region_id) {
		return $region_id
			? \db_constituency::get_counties_for_region($region_id)
			: \db_constituency::get_counties();
	}	
	
	private static function makeLink($get_parameters, $label) {
		echo "<a href=\"index.php?" . http_build_query($get_parameters) . "\">" . $label . "</a>";
	}

} //End of class