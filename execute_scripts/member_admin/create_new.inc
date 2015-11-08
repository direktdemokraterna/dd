<?php 
if($_POST){
	if(!filter_var($_POST['email'], FILTER_VALIDATE_EMAIL)){
		$_SESSION['report_message'] = "Mejladressen var inte korrekt.";
		$_SESSION['red_report_message'] = 1;
	}
	else{
		$region = db_constituency::get_region_from_county($_POST['county']);
		
		$random_password = general_helpers::GenerateRandomString(12);
		$hasher = new PasswordHash(8, FALSE);
		$password = $hasher->HashPassword($random_password);
		
		$ok = db_user::add_user($_POST['username'], $password, $_POST['first_name'], $_POST['last_name'], $_POST['street_address'], $_POST['zip_code'], $_POST['city_address'], $_POST['county'], $region, $_POST['social_security_number'], $_POST['email'], $_POST['skype_name']);
		if($ok)
			$_SESSION['report_message'] = "Användaren är skapad. Lösenordet är: " . $random_password;
		else
			\Logic\general::report_error("Något gick fel, ingen användare skapad.");
	}
}

?>