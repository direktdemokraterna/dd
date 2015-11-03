<?php
namespace View;

class member 
{
	public static function output_edit_fields($result) {
		$tab_index = 1;
		\View\general::make_textfield("email", "Mejladress", $tab_index++, $result);
		\View\general::make_textfield("social_security_number", "Personnummer", $tab_index++, $result);
		\View\general::make_textfield("username", "Användarnamn", $tab_index++, $result);
		\View\general::make_textfield("first_name", "Förnamn", $tab_index++, $result);
		\View\general::make_textfield("last_name", "Efternamn", $tab_index++, $result);
		\View\general::make_textfield("street_address", "Gatuadress", $tab_index++, $result);
		\View\general::make_textfield("zip_code", "Postnummer", $tab_index++, $result);
		\View\general::make_textfield("city_address", "Postort", $tab_index++, $result);
		$counties = \db_constituency::get_counties_with_regions();
		self::set_regions_by_county_in_javascript($counties);
		self::output_county_selector($result, $counties);
		self::output_region_selector($result);
		\View\general::make_textfield("skype_name", "Skype användarnamn", $tab_index++, $result);
		\View\general::make_textfield("telephone1", "Primärt telefonnummer", $tab_index++, $result);
		\View\general::make_textfield("telephone2", "Sekundärt telefonnummer", $tab_index++, $result);
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

	private static function output_county_selector($result, $counties) {
		$county_options = \db_general::make_hash($counties, 'county', 'county');
		\View\general::make_labeled_selector("county", "Kommun", $county_options, $result['county']
			, 'onchange="county_changed()"');
	}

	private static function output_region_selector($result) {
		$selected_county = $result['county'];
		$selected_region = $selected_county 
			? \db_constituency::get_region_from_county($selected_county)
			: null;
		$regions = \db_constituency::get_regions();
		$region_options = \db_general::make_hash($regions, 'title', 'title');
		$region_options['EMPTY'] = '- Alla län - ';
		\View\general::make_labeled_selector("region", "Län", $region_options, $selected_region
			, 'onchange="region_changed()"');
	}
}
?>
