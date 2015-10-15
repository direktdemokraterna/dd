<?php
	if($_POST['form_type']=="password"){
		if($_POST['new_password1']!=$_POST['new_password2']){
			$_SESSION['report_message'] = "De nya lösenorden matchade inte"; 
			$_SESSION['red_report_message'] = 1;
		}
		else{
			require("helpers/class-phpass.php");
			$old_password_hash = db_user::get_password($_SESSION['id']);

			$hasher = new PasswordHash(8, FALSE);
			if ($hasher->CheckPassword($_POST['old_password'], $old_password_hash)) { // Old password correct
				$new_password_hash = $hasher->HashPassword($_POST['new_password1']);
				$ok = db_user::update_password($new_password_hash, $_SESSION['id']);
				if($ok){
					$_SESSION['report_message'] = "Lösenordet har blivit uppdaterat."; 
					$redirect = $_SERVER['REQUEST_URI'];
				}
			}
			else{ // Old password incorrect
				$_SESSION['report_message'] = "Lösenordet var inte korrekt"; 
				$_SESSION['red_report_message'] = 1;
			}
		}
	}

	elseif($_POST['form_type']=="settings"){
		if($_POST['show_email']!=1) $_POST['show_email']=0;
		if($_POST['show_telephone']!=1) $_POST['show_telephone']=0;
		if($_POST['show_skype']!=1) $_POST['show_skype']=0;
		$ok = db_user::update_settings($_POST['show_email'], $_POST['show_telephone'], $_POST['show_skype'], $_SESSION['id']);
		if($ok){
			$_SESSION['report_message'] = "Dina inställningar har uppdaterats"; 
			$redirect = $_SERVER['REQUEST_URI'];
		}
		else{
			$_SESSION['report_message'] = "Inga inställningar ändrade"; 
			$_SESSION['red_report_message'] = 1;
		}
	}

	elseif($_POST['form_type']=="description"){
		$presentation = forum_helpers::process_text($_POST['settings_description']);
		$ok = db_user::update_description($presentation, $_SESSION['id']);
		if($ok){
			$_SESSION['report_message'] = "Presentationen har uppdaterats."; 
			$redirect = $_SERVER['REQUEST_URI'];
		}
		else{
			$_SESSION['report_message'] = "Ingenting ändrat."; 
			$_SESSION['red_report_message'] = 1;
		}
	}

	elseif($_POST['form_type']=="image"){
		$image_info = getimagesize($_FILES['image']['tmp_name']);
		if($image_info['2']==1){  // Checks that file is gif image
			$image_filename = general_helpers::GenerateRandomString(20) . ".gif";
		}
		elseif($image_info['2']==2){  // Checks that file is jpg image
			$image_filename = general_helpers::GenerateRandomString(20) . ".jpg";
		}
		elseif($image_info['2']==3){  // Checks that file is png image
			$image_filename = general_helpers::GenerateRandomString(20) . ".png";
		}
		else{
			$_SESSION['report_message'] = "Felaktig filtyp"; 
			$_SESSION['red_report_message'] = 1;
		}

		if(isset($image_filename)){ // Execute file upload and database update
			move_uploaded_file($_FILES['image']['tmp_name'], USERIMG_PATH . $image_filename);
			$ok = db_user::update_image($image_filename, $_SESSION['id']);
			if($ok){
				$_SESSION['report_message'] = "Bild uppdaterad."; 
				$redirect = $_SERVER['REQUEST_URI'];
			}
		}
	}

	elseif($_POST['form_type']=="profile"){
		if(!filter_var($_POST['email'], FILTER_VALIDATE_EMAIL)){
			$_SESSION['report_message'] = "Mejladressen är inte korrekt."; 
			$_SESSION['red_report_message'] = 1;
		}
		elseif(isset($_POST['first_name']) && isset($_POST['last_name']) && isset($_POST['street_address']) && isset($_POST['zip_code']) && isset($_POST['city_address']) && isset($_POST['county']) && isset($_POST['email'])){
		
			$region = db_constituency::get_region_from_county($_POST['county']);
			$ok = db_user::update_profile(general_helpers::clean($_POST['first_name']), general_helpers::clean($_POST['last_name']), general_helpers::clean($_POST['street_address']), (int)$_POST['zip_code'], general_helpers::clean($_POST['city_address']), $_POST['county'], $region, $_POST['email'], general_helpers::clean($_POST['skype_name']), general_helpers::clean($_POST['telephone1']), general_helpers::clean($_POST['telephone2']), $_SESSION['id']);
			if($ok){
				forum_helpers::update_county_region_forum_access($_SESSION['id'], $_POST['county']);
				vote_helpers::change_county_region_constituencies($_SESSION['id'], $_POST['county']);
				$_SESSION['report_message'] = "Din profil är uppdaterad";
				$redirect = $_SERVER['REQUEST_URI'];
			}
			else{
				$_SESSION['report_message'] = "Ingen uppdatering gjord";
				$_SESSION['red_report_message'] = 1;
			}
		}
		else{
			$_SESSION['report_message'] = "Något fält som måste vara ifyllt var inte ifyllt.";
			$_SESSION['red_report_message'] = 1;
		}
	}
?>