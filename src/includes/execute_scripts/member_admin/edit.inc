<?php 
if(isset($_POST['edit_user'])){
	$error = \Logic\user::validate_user($_POST['social_security_number'], $_POST['email'], $_GET['id']);
	if($error)
		\Logic\util::report_error($error);
	else{
		$region_id = db_constituency::get_region_id_from_county_id($_POST['county_id']);
		$ok = db_user::update_user_by_admin(
		    general_helpers::clean($_POST['username']),
            general_helpers::clean($_POST['first_name']),
            general_helpers::clean($_POST['last_name']),
            general_helpers::clean($_POST['street_address']),
            general_helpers::clean($_POST['zip_code']),
            general_helpers::clean($_POST['city_address']),
            general_helpers::clean($_POST['county_id']),
            $region_id,
            general_helpers::clean($_POST['social_security_number']),
            general_helpers::clean($_POST['email']),
            general_helpers::clean($_POST['skype_name']),
            general_helpers::clean($_POST['telephone1']),
            general_helpers::clean($_POST['telephone2']),
            general_helpers::clean($_GET['id'])
        );
		if($ok){
			\Logic\forum::update_county_region_forum_access($_GET['id'], $_POST['county_id']);
			\Logic\constituency::update_county_region_constituencies($_SESSION['id'], $_POST['county_id']);
			$_SESSION['report_message'] = "Användare uppdaterad";
		}
		else
			\Logic\util::report_error("Ingen ändring utförd");
	}
}

elseif(isset($_POST['change_password'])){
	$random_password = general_helpers::GenerateRandomString(12);
	$hasher = new PasswordHash(8, FALSE);
	$password = $hasher->HashPassword($random_password);

	$ok = db_user::update_password($password, $_GET['id']);

	$username = $_POST['username'];
	$mail_receiver = $_POST['user_email'];
	$mail_title = "Du har fått ett nytt lösenord";
	$mail_text = "Dina nya användaruppgifter är:" . "\n\n" . "Användarnamn" . $username . "\n" . "Lösenord" . $random_password;

	$mail_response = general_helpers::admin_mail($mail_receiver, $mail_title, $mail_text);
	if($mail_response != "success"){
		die($mail_response);
	}

	$_SESSION['report_message'] = "Användaren har fått ett nytt lösenord. Användarnamn och det nya lösenordet har mejlats till användaren.";
}
?>