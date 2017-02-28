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
	__h1("Behandla ansökan från " . $application_data['full_name']);
	__open_form();
	__hidden("accept", 1);
	__br();
	__label("Användarnamn", "username");
	echo '<input type="text" name="username" id="username" value="' . $suggested_username . '" style="background: #E8E8E8; color: #B0B0B0;" disabled>';
	__textfield("first_name", "Förnamn", 2, $application_data);
	__textfield("last_name", "Efternamn", 3, $application_data);
	__textfield("street_address", "Gatuadress", 4, $application_data);
	__textfield("zip_code", "Postnummer", 5, $application_data);
	__textfield("city_address", "Postort", 6, $application_data);
	$counties = db_constituency::get_counties();
	$county_options = \db_general::make_hash($counties, 'id', 'title');
	\View\controls::output_labeled_selector("county_id", "Kommun", $county_options, $application_data['county_id']
		, 'tabindex="7"');
	__textfield("telephone", "Telefonnummer", 8, $application_data['telephone1']);
	__textfield("email", "Mejladress", 9, $application_data);
	__textfield("social_security_number", "Personnummer", 10, $application_data);
	__br();
	__submit_and_close("Registrera som medlem");
	__open_form();
	__hidden("reject", 1);
	__submit_and_close("Avslå ansökan");
?>
