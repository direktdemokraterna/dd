<?php 

if($_POST['accept']){
	if(!filter_var($_POST['email'], FILTER_VALIDATE_EMAIL)){
		$_SESSION['report_message'] = "Mejladressen var inte korrekt.";
		$_SESSION['red_report_message'] = 1;
	}
	else{
		$region = db_constituency::get_region_from_county($_POST['county']);
		
		$username = strtolower(general_helpers::clean($_POST['first_name']) . general_helpers::clean($_POST['last_name']));
		$username = str_replace(Array("å", "ä", "ö", "é"), Array("a", "a", "o", "e"), $username);

		if(db_user::get_user_id($username)){
			for($i=2; $i<1000; $i++){
				$username_with_number = $username . $i;
				if(!db_user::get_user_id($username_with_number)){
					break;
				}
			}
			$username = $username_with_number;
		}

		require("helpers/class-phpass.php");
		$random_password = general_helpers::GenerateRandomString(12);
		$hasher = new PasswordHash(8, FALSE);
		$password = $hasher->HashPassword($random_password);
		
		$ok = db_user::add_user($username, $password, general_helpers::clean($_POST['first_name']), general_helpers::clean($_POST['last_name']), general_helpers::clean($_POST['street_address']), (int)$_POST['zip_code'], general_helpers::clean($_POST['city_address']), $_POST['county'], $region, general_helpers::clean($_POST['social_security_number']), $_POST['email']);

		if($ok){
			db_user::delete_user_application($_GET['id']);

			$mail_receiver = $_POST['email'];
			$mail_title = "Välkommen till Direktdemokraterna";
			$mail_text = "Du har blivit antagen som medlem i Direktdemokraterna och kan logga in på medlems-sidan.\n\nDina inloggningsuppgifter är följande:\n\nAnvändarnamn: " . $username . "\nLösenord: " . $random_password;

			$mail_response = general_helpers::admin_mail($mail_receiver, $mail_title, $mail_text);
			if($mail_response != "success"){
				die($mail_response);
			}

			$_SESSION['report_message'] = "Ny medlem har registrerats med användarnamnet " . $username . ". Användaruppgifter har skickats via e-post till medlemmen.";
			$redirect = "index.php?type=member_admin&action=list_applications";
		}
		else{
			$_SESSION['report_message'] = "Något gick fel, ingen användare skapad.";
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