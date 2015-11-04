<?php 
if(isset($_POST['edit_user'])){
	if(!filter_var($_POST['email'], FILTER_VALIDATE_EMAIL)){
		$_SESSION['report_message'] = "Mejladressen är inte korrekt."; 
		$_SESSION['red_report_message'] = 1;
	}
	else{
		$region = db_constituency::get_region_from_county($_POST['county']);
		$ok = db_user::update_user_by_admin($_POST['username'], $_POST['first_name'], $_POST['last_name'], $_POST['street_address'], $_POST['zip_code'], $_POST['city_address'], $_POST['county'], $region, $_POST['social_security_number'], $_POST['email'], $_POST['skype_name'], $_POST['telephone1'], $_POST['telephone2'], $_GET['id']);
		if($ok){
			forum_helpers::update_county_region_forum_access($_GET['id'], $_POST['county']);
			vote_helpers::update_county_region_constituencies($_SESSION['id'], $_POST['county']);
			$_SESSION['report_message'] = "Användaren uppdaterad";
			$redirect = $_SERVER['REQUEST_URI'];
		}
		else{
			$_SESSION['report_message'] = "Ingen uppdatering gjord";
			$_SESSION['red_report_message'] = 1;
		}
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

elseif(isset($_POST['delete_user'])){

	$ok = db_member_admin::delete_user($_GET['id']);
	if($ok){
		$_SESSION['report_message'] = "Användaren är borttagen ur medlemslistan";
		$redirect = $_SERVER['REQUEST_URI'];
	}

}

elseif(isset($_POST['restore_user'])){

	$ok = db_member_admin::restore_user($_GET['id']);
	if($ok){
		$_SESSION['report_message'] = "Användaren har återställts i medlemslistan";
		$redirect = $_SERVER['REQUEST_URI'];
	}

}

?>