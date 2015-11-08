<?php 
if(isset($_POST['edit_user'])){
	$error = \Logic\user::validate_user($_POST['social_security_number'], $_POST['email'], $_GET['id']);
	if($error)
		\Logic\util::report_error($error);
	else{
		$region = db_constituency::get_region_from_county($_POST['county']);
		$ok = db_user::update_user_by_admin($_POST['username'], $_POST['first_name'], $_POST['last_name'], $_POST['street_address'], $_POST['zip_code'], $_POST['city_address'], $_POST['county'], $region, $_POST['social_security_number'], $_POST['email'], $_POST['skype_name'], $_POST['telephone1'], $_POST['telephone2'], $_GET['id']);
		if($ok){
			forum_helpers::update_county_region_forum_access($_GET['id'], $_POST['county']);
			vote_helpers::update_county_region_constituencies($_SESSION['id'], $_POST['county']);
			$_SESSION['report_message'] = "Användaren uppdaterad";
		}
		else
			\Logic\util::report_error("Ingen uppdatering gjord");
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
	$mail_text = "Dina nya inloggningsuppgifter är följande:\n\nAnvändarnamn: " . $username . "\nLösenord: " . $random_password;

	$mail_response = general_helpers::admin_mail($mail_receiver, $mail_title, $mail_text);
	if($mail_response != "success"){
		die($mail_response);
	}

	$_SESSION['report_message'] = "Medlemmen har fått ett nytt lösenord. E-post med användarnamn och nytt lösenord har skickats till medlemmen.";
}
?>