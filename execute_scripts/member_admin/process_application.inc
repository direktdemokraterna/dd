<?php 

if($_POST['accept']){
	if(!filter_var($_POST['email'], FILTER_VALIDATE_EMAIL)){
		$_SESSION['report_message'] = _t("The email address is invalid.");
		$_SESSION['red_report_message'] = 1;
	}
	else{
		$region_id = db_constituency::get_region_id_from_county_id($_POST['county']);
		$username = strtolower(general_helpers::clean($_POST['first_name']) . general_helpers::clean($_POST['last_name']));
		$username = str_replace(Array("å", "ä", "ö", "é"), Array("a", "a", "o", "e"), $username);

		if(db_user::get_user_id($username)){
			for($i=2; $i<1000; $i++){
				$username_with_number = $username . $i;
				if(!db_user::get_user_id($username_with_number))
					break;
			}
			$username = $username_with_number;
		}

		$random_password = general_helpers::GenerateRandomString(12);
		$hasher = new PasswordHash(8, FALSE);
		$password = $hasher->HashPassword($random_password);
		
		$ok = db_user::add_user($username, $password, general_helpers::clean($_POST['first_name']), general_helpers::clean($_POST['last_name']), general_helpers::clean($_POST['street_address']), (int)$_POST['zip_code'], general_helpers::clean($_POST['city_address']), $_POST['county'], $region_id, general_helpers::clean($_POST['social_security_number']), $_POST['email']);

		if($ok){
			db_user::delete_user_application($_GET['id']);

			$mail_receiver = $_POST['email'];
			$mail_title = _t("Welcome to Direktdemokraterna");
			$mail_text = _t("You have been accepted as a member of Direktdemokraterna and can login on the member-page.") . "\n\n" . _t("Your credentials are as follows:") 
				. "\n\n" . _t("Username: ") . $username . "\n" 
				. _t("Password: ") . $random_password;

			$mail_response = general_helpers::admin_mail($mail_receiver, $mail_title, $mail_text);
			if($mail_response != "success"){
				die($mail_response);
			}

			$_SESSION['report_message'] = _t("A new member has been registered with the username ") . $username . _t(". User information have been sent by email to the member.");
			$redirect = "index.php?type=member_admin&action=list_applications";
		}
		else{
			$_SESSION['report_message'] = _t("Something went wrong. No user created.");
			$_SESSION['red_report_message'] = 1;
		}
	}
}

elseif($_POST['reject']){

	$application_data = db_user::get_user_application($_GET['id']);

	$ok = db_user::delete_user_application($_GET['id']);

	if($ok){
		$mail_receiver = $application_data['email'];
		$mail_title = "Din medlemsansökan till Direktdemokraterna har avslagits";
		$mail_text = "En medlemsadministratör har avslagit din medlemsansökan till Direktdemokraterna. Kontakta en medlemsadministratör för att få veta mer eller lämna in en ny ansökan.";

		general_helpers::admin_mail($mail_receiver, $mail_title, $mail_text);

		$_SESSION['report_message'] = "Medlemsansökan har avslagits.";
		$redirect = "index.php?type=member_admin&action=list_applications";
	}
	else{
		$_SESSION['report_message'] = "Något gick fel, ingen åtgärd vidtagen.";
		$_SESSION['red_report_message'] = 1;		
	}

}

?>