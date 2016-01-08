<?php 
	$application_data = db_user::get_user_application($_GET['id']);
	$suggested_username = strtolower($application_data['first_name'] . $application_data['last_name']);
	$suggested_username = str_replace(Array("å", "ä", "ö", "é"), Array("a", "a", "o", "e"), $suggested_username);
	if(db_user::get_user_id($suggested_username)){
		for($i=2; $i<1000; $i++){
			$suggested_username_with_number = $suggested_username . $i;
			if(!db_user::get_user_id($suggested_username_with_number))
				break;
		}
		$suggested_username = $suggested_username_with_number;
	}
	_h1(_t("Process application from ") . $application_data['full_name']);
	_open_form();
	_hidden("accept", 1);
	_br();
	_label(_t("Username"), "username");
	echo '<input type="text" name="username" id="username" value="' . $suggested_username . '" style="background: #E8E8E8; color: #B0B0B0;" disabled>';
	\View\general::make_textfield("first_name", _t("Given name"), 2, $application_data);
	\View\general::make_textfield("last_name", _t("Last name"), 3, $application_data);
	\View\general::make_textfield("street_address", _t("Street address"), 4, $application_data);
	\View\general::make_textfield("zip_code", _t("Zip code"), 5, $application_data);
	\View\general::make_textfield("city_address", _t("City"), 6, $application_data);
	$counties = db_constituency::get_counties();
	$county_options = \db_general::make_hash($counties, 'title', 'title');
	\View\general::make_labeled_selector("county", _t("Municipality"), $county_options, $application_data['county_id']
		, 'tabindex="7"');
	\View\general::make_textfield("telephone", _t("Telephone"), 8, $application_data['telephone1']);
	\View\general::make_textfield("email", _t("Email"), 9, $application_data);
	\View\general::make_textfield("social_security_number", _t("Social security number"), 10, $application_data);
	_br();
	_submit_and_close(_t("Register as member"));
	_open_form();
	_hidden("reject", 1);
	_submit_and_close(_t("Reject application"));
?>
