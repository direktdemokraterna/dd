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
		return $string . (self::is_genitive($string) ? "" : "s");
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
		return \Logic\calendar::$week_day_names[$weekday];
	}

	public static function get_month($timestamp, $month = 0){
		$month = $timestamp > 0 
			? date("n", $timestamp) 
			: $month;
		return \Logic\calendar::$months[$month];
	}

	public static function admin_mail ($receiver, $title, $text) {
		// https://github.com/PHPMailer/PHPMailer
		require_once('PHPMailer-master/PHPMailerAutoload.php');
		$mail = new PHPMailer();
		$mail->setFrom(MAIL_FROM_ADDRESS, MAIL_FROM_NAME);
		$mail->addReplyTo(MAIL_REPLY_TO_ADDRESS, MAIL_REPLY_TO_NAME);
		$mail->AddAddress($receiver);
		$mail->Subject = $title;
		$mail->Body = $text;
        $mail->IsSMTP();
        $mail->SMTPAuth = true;
        $mail->SMTPSecure = 'ssl';
        $mail->Port = 465;
        $mail->Host = MAIL_HOST;
        $mail->Username = MAIL_USERNAME;
        $mail->Password = MAIL_PASSWORD;
        $mail->CharSet = 'utf-8';

		$ok = $mail->send();
		return $ok 
			? "success" 
			: $mail->ErrorInfo;
	}
	
	// makes the top links for choosing page and sorting alternatives for a list_of_links
	public static function make_list_of_links_header ($page, $result_counter, $sort_alternatives = null, $filter_title = null, $filter_alternatives = null){
		if (!$filter_title)
			$filter_title = "Filtrering:";
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

	public static function check_personnummer ($personal_number) {
		$clean_personal_number = substr(self::clean_personnummer($personal_number), 2);
		return self::luhn_algorithm_check($clean_personal_number);
	}

	// Removes "-" and converts to 12 digits.
    // If 10 digits and starting with 0 or 1 then 20 is added as prefix, when starting with another digit 19 is added
    // This logic is not 100 % accurate so best is to always require 12 digits to avoid problems
	public static function clean_personnummer ($personal_number) {
		$personal_number = str_replace("-", "", $personal_number);
        if (strlen($personal_number) === 10) {
            if (substr($personal_number, 0, 1) === "0" || substr($personal_number, 0, 1) === "1") {
                return "20" . $personal_number;
            } else {
                return "19" . $personal_number;
            }
        }
		if (strlen($personal_number) !== 12) return null;
		return $personal_number;
	}

	private static function luhn_algorithm_check ($short_personal_number) {
        if ($short_personal_number === null || strlen($short_personal_number) !== 10)
            return false;
        $one_two = 2;
        $control_sum = 0;
        for ($i=0; $i<9; $i++){
            $temp = $short_personal_number[$i] * $one_two;
            $control_sum += ($temp > 9 ? 1 + ($temp % 10) : $temp);
            $one_two = $one_two == 2 ? 1 : 2;
        }
        $control_digit = (10 - $control_sum % 10) % 10;
        return ($control_digit == $short_personal_number[9]);
    }

	public static function clean ($data, $flags = ENT_COMPAT, $charset = 'ISO-8859-1', $dblencode = true ) {
		return htmlspecialchars($data, $flags, $charset, $dblencode);
	}
	
	///////////////////////////////////
	/// Private methods starts here ///
	///////////////////////////////////

	private static function is_genitive ($str){
		return mb_strlen($str) > 0 && mb_strtolower(substr($str, -1)) == "s";
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
	
	// makes the top links for choosing page and sorting alternatives for a list_of_links
	private static function make_generic_list_filter ($get_parameters, $filter_title = null, $filter_alternatives = null){
		if (!$filter_title)
			$filter_title = "Filtrering:";
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
		echo '<span class="list_sort_alternative">' . "Län: ";
		self::makeSelectBox('region', $region_id, \db_constituency::get_regions(), "Alla län"
			, 'set_default_county_if_region_set();');
		echo '</span>';
		echo '<span class="list_sort_alternative">' . "Kommun: ";
		self::makeSelectBox('county', $county_id, self::getCounties($region_id), "Alla kommuner");
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
		echo "Visar " . $first_showed_item_number . " - " . $last_showed_item_number . " av " . $result_counter;
		echo "</span>";
	}
	
	private static function make_list_sorting ($get_parameters, $sort_alternatives = null){
		if($sort_alternatives){
			echo '<span class="list_sort_alternative">' . "Sortering: " . '</span>';
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

	public static function resize_image($file, $w) { // modifierad från http://stackoverflow.com/questions/14649645/resize-image-in-php
		list($width, $height, $type) = getimagesize($file);
		$r = $width / $height;
		$newheight = $w/$r;
		$newwidth = $w;
		if($type==1){  // image is gif
			$src = imagecreatefromgif($file);
			$src = self::flatten_image($src);
		}
		elseif($type==2)  // image is jpg
			$src = imagecreatefromjpeg($file);
		elseif($type==3){  // image is png
			$src = imagecreatefrompng($file);
			$src = self::flatten_image($src);
		}
		$dst = imagecreatetruecolor($newwidth, $newheight);
		imagecopyresampled($dst, $src, 0, 0, 0, 0, $newwidth, $newheight, $width, $height);

		return $dst;
	}

	public static function flatten_image($image) { // modifierad från http://stackoverflow.com/questions/3538106/how-to-delete-transparent-color-in-images
		$width = imagesx($image);
		$height = imagesy($image);
		$bg = imagecreatetruecolor($width, $height);
		$white = imagecolorallocate($bg, 255, 255, 255);
		imagefill($bg, 0, 0, $white);
		imagecopyresampled($bg, $image, 0, 0, 0, 0, $width, $height, $width, $height);
		return $bg;
	}

	public static function output_notice_link($id) {
		$notice_info = db_notice::get_notice_info($id);
		if($notice_info['type_of_notification'] == "quoting_post"){
			$post_info = db_forum::get_post_info($notice_info['action_id']);
			return _link($post_info['full_name'] . " har citerat ditt inlägg i " . $post_info['title'], 'forum', 'show_posts', 'post_id=' . $post_info['post_id'] . '&remove_notice=' . $id . '#post' . $post_info['post_id']);
		}
		elseif($notice_info['type_of_notification'] == "vote_started"){
			$vote_info = db_vote::get_vote_info($notice_info['action_id']);
			return _link("Omröstningen " . $vote_info['title'] . " har startat", 'vote', 'view_vote', 'id=' . $vote_info['id'] . '&remove_notice=' . $id);
		}
		elseif($notice_info['type_of_notification'] == "vote_finished"){
			$vote_info = db_vote::get_vote_info($notice_info['action_id']);
			return _link("Omröstningen " . $vote_info['title'] . " har avslutats", 'vote', 'view_vote', 'id=' . $vote_info['id'] . '&remove_notice=' . $id);
		}
		elseif($notice_info['type_of_notification'] == "proposition_created"){
			$prop_info = db_prop::get_prop_info($notice_info['action_id']);
			return _link($prop_info['user_full_name'] . " har skapat propositionen " . $prop_info['title'], 'vote', 'view_prop', 'id=' . $prop_info['prop_id'] . '&remove_notice=' . $id);
		}
	}

	public static function remove_notices() {
		if(isset($_REQUEST['remove_all_notices'])){
			db_notice::remove_all_view_notices($_SESSION['id']);
			$redirect = str_replace("&remove_all_notices=1", "", $_SERVER['REQUEST_URI']);
			header("Location: $redirect");
		}
		if(isset($_REQUEST['remove_notice'])){
			db_notice::remove_own_notice($_REQUEST['remove_notice']);
		}
	}

	public static function initiate_csrf_protection() {
        $csrf_token = self::produce_csrf_token();
		echo '<input type="hidden" name="csrf_token" value="' . $csrf_token . '">';
	}

	public static function produce_csrf_token() {
        if (empty($_SESSION['csrf_token'])) {
            $_SESSION['csrf_token'] = uniqid();
        }
        return $_SESSION['csrf_token'];
    }

} //End of class