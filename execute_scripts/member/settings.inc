<?php
	if(!empty($_POST)){
		if($_POST['form_type']=="password"){
			if($_POST['new_password1']!=$_POST['new_password2']){
				$message = "De nya lösenorden matchade inte"; 
				db_helpers::insert_error_message($_SESSION['id'], $message, "red");
			}
			else{
				require("helpers/class-phpass.php");
				$old_password_hash = db_user::get_password($_SESSION['id']);

				$hasher = new PasswordHash(8, FALSE);
				if ($hasher->CheckPassword($_POST['old_password'], $old_password_hash)) { // Old password correct
					$new_password_hash = $hasher->HashPassword($_POST['new_password1']);
					$ok = db_user::update_password($new_password_hash, $_SESSION['id']);
					if($ok){
						$message = "Lösenordet har blivit uppdaterat."; 
						db_helpers::insert_error_message($_SESSION['id'], $message);
						$redirect = $_SERVER['REQUEST_URI'];
					}
				}
				else{ // Old password incorrect
					$message = "Lösenordet var inte korrekt"; 
					db_helpers::insert_error_message($_SESSION['id'], $message, "red");
				}
			}
		}

		elseif($_POST['form_type']=="settings"){
			if($_POST['show_email']!=1) $_POST['show_email']=0;
			if($_POST['show_telephone']!=1) $_POST['show_telephone']=0;
			if($_POST['show_skype']!=1) $_POST['show_skype']=0;
			$ok = db_user::update_settings($_POST['show_email'], $_POST['show_telephone'], $_POST['show_skype'], $_SESSION['id']);
			if($ok){
				$message = "Dina inställningar har uppdaterats"; 
				db_helpers::insert_error_message($_SESSION['id'], $message);
				$redirect = $_SERVER['REQUEST_URI'];
			}
			else{
				$message = "Inga inställningar ändrade"; 
				db_helpers::insert_error_message($_SESSION['id'], $message, "red");
			}
		}

		elseif($_POST['form_type']=="description"){
			$presentation = forum_helpers::process_text($_POST['settings_description']);
			$ok = db_user::update_description($presentation, $_SESSION['id']);
			if($ok){
				$message = "Presentationen har uppdaterats."; 
				db_helpers::insert_error_message($_SESSION['id'], $message);
				$redirect = $_SERVER['REQUEST_URI'];
			}
			else{
				$message = "Ingenting ändrat."; 
				db_helpers::insert_error_message($_SESSION['id'], $message, "red");
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
				$message = "Felaktig filtyp"; 
				db_helpers::insert_error_message($_SESSION['id'], $message, "red");
			}

			if(isset($image_filename)){ // Execute file upload and database update
				move_uploaded_file($_FILES['image']['tmp_name'], USERIMG_PATH . $image_filename);
				$ok = db_user::update_image($image_filename, $_SESSION['id']);
				if($ok){
					$message = "Bild uppdaterad."; 
					db_helpers::insert_error_message($_SESSION['id'], $message);
					$redirect = $_SERVER['REQUEST_URI'];
				}
			}
		}

		elseif($_POST['form_type']=="profile"){
			if(!filter_var($_POST['email'], FILTER_VALIDATE_EMAIL)){
				$message = "Mejladressen är inte korrekt."; 
				db_helpers::insert_error_message($_SESSION['id'], $message, "red");
			}
			elseif(isset($_POST['first_name']) && isset($_POST['last_name']) && isset($_POST['street_address']) && isset($_POST['zip_code']) && isset($_POST['city_address']) && isset($_POST['county']) && isset($_POST['email'])){
			
				$region = db_helpers::get_region_from_county($_POST['county']);
				$ok = db_user::update_profile($_POST['first_name'], $_POST['last_name'], $_POST['street_address'], $_POST['zip_code'], $_POST['city_address'], $_POST['county'], $region, $_POST['email'], $_POST['skype_name'], $_POST['telephone1'], $_POST['telephone2'], $_SESSION['id']);
				if($ok){
					$message = "Din profil är uppdaterad";
					db_helpers::insert_error_message($_SESSION['id'], $message);
					$redirect = $_SERVER['REQUEST_URI'];
				}
				else{
					$message = "Ingen uppdatering gjord";
					db_helpers::insert_error_message($_SESSION['id'], $message, "red");
				}
			}
			else{
				$message = "Något fält som måste vara ifyllt var inte ifyllt.";
				db_helpers::insert_error_message($_SESSION['id'], $message, "red");
			}
		}
	}
?>