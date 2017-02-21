<?php 
if ($_POST) {
	if(!filter_var($_POST['email'], FILTER_VALIDATE_EMAIL)){
		$_SESSION['report_message'] = "Mejladressen är ogiltig";
		$_SESSION['red_report_message'] = 1;
	} else {
		$region_id = db_constituency::get_region_id_from_county_id($_POST['county_id']);
		$random_password = general_helpers::GenerateRandomString(12);
		$hasher = new PasswordHash(8, FALSE);
		$password = $hasher->HashPassword($random_password);
		
		$ok = db_user::add_user(
            general_helpers::clean($_POST['username']),
            $password,
            general_helpers::clean($_POST['first_name']),
            general_helpers::clean($_POST['last_name']),
            general_helpers::clean($_POST['street_address']),
            general_helpers::clean($_POST['zip_code']),
            general_helpers::clean($_POST['city_address']),
            $_POST['county_id'],
            $region_id,
            general_helpers::clean($_POST['social_security_number']),
            $_POST['email'],
            general_helpers::clean($_POST['skype_name'])
        );
		if($ok)
			$_SESSION['report_message'] = "Användaren har skapats. Lösenordet är: " 
				. $random_password;
		else
			\Logic\util::report_error("Något gick fel. Ingen användare skapad.");
	}
}

?>