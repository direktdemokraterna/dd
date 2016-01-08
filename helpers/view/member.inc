<?php
namespace View;

class member 
{
	public static function output_edit_fields($user_data = null, $include_social_security_number = true, &$tab_index = 1) {
		\View\general::make_textfield("username", _t("Username"), $tab_index++, $user_data);
		\View\general::make_textfield("first_name", _t("Given name"), $tab_index++, $user_data);
		\View\general::make_textfield("last_name", _t("Last name"), $tab_index++, $user_data);
		if ($include_social_security_number)
			\View\general::make_textfield("social_security_number", _t("Social security number"), 
				$tab_index++, $user_data);			
		\View\general::make_textfield("email", _t("Email address"), $tab_index++, $user_data);
		\View\general::make_textfield("street_address", _t("Street address"), $tab_index++, $user_data);
		\View\general::make_textfield("zip_code", _t("Zip code"), $tab_index++, $user_data);
		\View\general::make_textfield("city_address", _t("City"), $tab_index++, $user_data);
		self::output_county_selectors($user_data, $tab_index);
		\View\general::make_textfield("telephone1", _t("Telephone 1"), $tab_index++, $user_data);
		\View\general::make_textfield("telephone2", _t("Telephone 2"), $tab_index++, $user_data);
		\View\general::make_textfield("skype_name", _t("Skype name"), $tab_index++, $user_data);
	}
	
	public static function output_county_selectors($user_data = null, &$tab_index = 1) {
		$counties = \db_constituency::get_counties_with_regions();
		self::set_regions_by_county_in_javascript($counties);
		self::output_region_selector($user_data, $tab_index++);
		self::output_county_selector($user_data, $counties, $tab_index++);
	}
	
	public static function output_member_list_header ($page, $result_counter, $sort_alternatives = null)
	{
		$show_deleted_control = isset($_SESSION['is_member_admin'])
			? self::generate_show_deleted_control()
			: null;
		\general_helpers::make_list_header_with_region_county_filter($page, $result_counter, $sort_alternatives, $show_deleted_control);
	}

	public static function link($user, $id_prop = 'id', $name_prop = 'full_name') {
		return \View\general::generate_internal_link($user[$name_prop]
			, 'member', 'view', 'id=' . $user[$id_prop]);
	}

	// makes the top links for choosing page and sorting alternatives for a list_of_links
	private static function generate_show_deleted_control (){
		$show_deleted = isset($_GET['show_deleted']) ? $_GET['show_deleted'] : 0;
		$html = '<input type="checkbox" name="show_deleted"' .
			($show_deleted ? ' checked' : '') 
			. ' id="show_deleted" onchange="this.form.submit()"><label for "show_deleted">' 
			. _t("Show removed members") . '</label>';
		return _span("list_sort_alternative", $html);
	}

	private static function set_regions_by_county_in_javascript($counties) {
		$county_region_pairs_for_javascript = self::get_county_region_pairs_for_javascript($counties);
		echo '<script>' . $county_region_pairs_for_javascript . '</script>';
	}

	private static function get_county_region_pairs_for_javascript($county_rows) {
		$pairs = [];
		foreach($county_rows as $row) {
			$county_id = $row['county_id'];
			$county_name = $row['county_name'];
			$region_id = $row['region_id'];
			$pairs[] = '"' . $county_id . '": {id: ' . $county_id . ', name: "' . $county_name 
			. '", region_id: ' . $region_id . '}';
		}
		$json = 'county_name_and_region_by_id = {' . PHP_EOL . implode("," . PHP_EOL, $pairs) . '};';
		return $json;
	}

	private static function output_region_selector($user_data, $tab_index) {
		$selected_county = $user_data ? $user_data['county_id'] : null;
		$selected_region = $selected_county 
			? \db_constituency::get_region_from_county($selected_county)
			: null;
		$regions = \db_constituency::get_regions();
		$region_options = \db_general::make_hash($regions, 'id', 'title');
		$region_options = array(0 => _t('All regions')) + $region_options;
		\View\general::make_labeled_selector("region", _t("Region"), $region_options, $selected_region
			, 'onchange="region_changed()" tabindex="' . $tab_index . '"');
	}

	private static function output_county_selector($user_data, $counties, $tab_index) {
		$county_options = \db_general::make_hash($counties, 'county_id', 'county_name');
		\View\general::make_labeled_selector("county", _t("Municipality"), $county_options, $user_data ? $user_data['county_id'] : null, 'onchange="county_changed()" tabindex="' . $tab_index . '"');
	}
}
?>
