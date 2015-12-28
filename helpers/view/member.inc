<?php
namespace View;

class member 
{
	public static function output_edit_fields($result = null, $include_social_security_number = true, &$tab_index = 1) {
		\View\general::make_textfield("username", _t("Username"), $tab_index++, $result);
		\View\general::make_textfield("first_name", _t("Given name"), $tab_index++, $result);
		\View\general::make_textfield("last_name", _t("Last name"), $tab_index++, $result);
		if ($include_social_security_number)
			\View\general::make_textfield("social_security_number", _t("Social security number"), 
				$tab_index++, $result);			
		\View\general::make_textfield("email", _t("Email address"), $tab_index++, $result);
		\View\general::make_textfield("street_address", _t("Street address"), $tab_index++, $result);
		\View\general::make_textfield("zip_code", _t("Zip code"), $tab_index++, $result);
		\View\general::make_textfield("city_address", _t("City"), $tab_index++, $result);
		self::output_county_selectors($result, $tab_index);
		\View\general::make_textfield("telephone1", _t("Telephone 1"), $tab_index++, $result);
		\View\general::make_textfield("telephone2", _t("Telephone 2"), $tab_index++, $result);
		\View\general::make_textfield("skype_name", _t("Skype name"), $tab_index++, $result);
	}
	
	public static function output_county_selectors($result = null, &$tab_index = 1) {
		$counties = \db_constituency::get_counties_with_regions();
		self::set_regions_by_county_in_javascript($counties);
		self::output_region_selector($result, $tab_index++);
		self::output_county_selector($result, $counties, $tab_index++);
	}
	
	// makes the top links for choosing page and sorting alternatives for a list_of_links
	public static function output_member_list_header ($page, $result_counter, $sort_alternatives = null){
		\general_helpers::make_list_pagin_and_sorting($_GET, $page, $result_counter, $sort_alternatives);
		self::make_region_county_list_filter();
	}

	public static function link($user, $id_prop = 'id', $name_prop = 'full_name') {
		return \View\general::generate_internal_link($user[$name_prop]
			, 'member', 'view', 'id=' . $user[$id_prop]);
	}

	// makes the top links for choosing page and sorting alternatives for a list_of_links
	private static function make_region_county_list_filter (){
		echo '<form id="filter_list" name="filter_list" method="get" action="">';
		echo '<input type="hidden" name="type" value="member"/>';
		echo '<input type="hidden" name="action" value="list"/>';
		echo '<input type="hidden" name="filter" value="county"/>';
		echo '<div class="list_of_link_menu">';
		echo '<span class="list_sort_alternative">' . _t("Region: ");
		self::makeSelecBox('region', \db_constituency::get_regions(), _t("All regions"));
		echo '</span>';
		echo '<span class="list_sort_alternative">' . _t("Municipality: ");
		self::makeSelecBox('county', self::getCounties(), _t("All municipalities"));
		echo "</span>";
		if(isset($_SESSION['is_member_admin'])) {
			$show_deleted = isset($_GET['show_deleted']) ? $_GET['show_deleted'] : 0;
			echo '<span class="list_sort_alternative">';
			echo '<input type="checkbox" name="show_deleted"' .
			($show_deleted ? ' checked' : '') . ' id="show_deleted" onchange="this.form.submit()"><label for "show_deleted">' . _t("Show removed members") . '</label>';
			echo '</span>';
		}
		echo "</span></div></form>";
	}

	private static function set_regions_by_county_in_javascript($counties) {
		$county_region_pairs_for_javascript = self::get_county_region_pairs_for_javascript($counties);
		echo '<script>' . $county_region_pairs_for_javascript . '</script>';
	}

	private static function get_county_region_pairs_for_javascript($county_rows) {
		$pairs = 'regions_by_county = {'; //Used by functions in constituency.js
		foreach($county_rows as $row)
			$pairs .= PHP_EOL . '"' . $row['county'] . '": "' . $row['region'] . '",';
		return $pairs . '};';
	}

	private static function output_region_selector($result, $tab_index) {
		$selected_county = $result ? $result['county'] : null;
		$selected_region = $selected_county 
			? \db_constituency::get_region_from_county($selected_county)
			: null;
		$regions = \db_constituency::get_regions();
		$region_options = \db_general::make_hash($regions, 'title', 'title');
		$region_options = array('EMPTY' => _t('- All regions - ')) + $region_options;
		\View\general::make_labeled_selector("region", _t("Region"), $region_options, $selected_region
			, 'onchange="region_changed()" tabindex="' . $tab_index . '"');
	}

	private static function output_county_selector($result, $counties, $tab_index) {
		$county_options = \db_general::make_hash($counties, 'county', 'county');
		\View\general::make_labeled_selector("county", _t("Municipality"), $county_options, $result ? $result['county'] : null, 'onchange="county_changed()" tabindex="' . $tab_index . '"');
	}

	private static function makeSelecBox($paramName, $rows, $unselectedLabel) {
		echo '<select class="standard-form" name="' . $paramName . 
		'" onchange="document.forms[\'filter_list\'].elements[\'filter\'].value = \'' . 
		$paramName . '\';this.form.submit();">';
		$selected = isset($_GET[$paramName]) ? $_GET[$paramName] : null;
		self::makeOption($unselectedLabel);
		foreach($rows as $row)
			self::makeOption($row['title'], $row['title'], $selected);
		echo "</select>";
	}
	
	private static function makeOption($label, $value, $selected) {
		echo '<option value="' . $value . '"' . ($value == $selected ? ' selected' : '') . '>' . 
		$label . '</option>';
	}
	
	private static function getCounties() {
		return isset($_GET['region']) && $_GET['region'] 
			? \db_constituency::get_counties_for_region($_GET['region'])
			: \db_constituency::get_counties();
	}	
}
?>
