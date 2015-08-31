<?php 
if(isset($_POST['edit_user'])){
	if(!filter_var($_POST['email'], FILTER_VALIDATE_EMAIL)){
		$_SESSION['report_message'] = "Mejladressen är inte korrekt."; 
		$_SESSION['red_report_message'] = 1;
	}
	else{
		$region = db_helpers::get_region_from_county($_POST['county']);
		$ok = db_user::update_user_by_admin($_POST['username'], $_POST['first_name'], $_POST['last_name'], $_POST['street_address'], $_POST['zip_code'], $_POST['city_address'], $_POST['county'], $region, $_POST['social_security_number'], $_POST['email'], $_POST['skype_name'], $_POST['telephone1'], $_POST['telephone2'], $_GET['id']);
		if($ok){
			forum_helpers::update_county_region_forum_access($_GET['id'], $_POST['county']);
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
	require("helpers/class-phpass.php");
	$random_password = general_helpers::GenerateRandomString(12);
	$hasher = new PasswordHash(8, FALSE);
	$password = $hasher->HashPassword($random_password);

	$ok = db_user::update_password($password, $_GET['id']);
	if($ok){
		$_SESSION['report_message'] = "Lösenordet har ändrats, nytt lösenord är: " . $random_password;
		$redirect = $_SERVER['REQUEST_URI'];
	}
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