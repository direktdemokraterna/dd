<?php
	if(isset($_POST["password"])){
		if($_POST['new_password1']!=$_POST['new_password2'])
			\Logic\util::report_error("Lösenorden stämde inte"); 
		else{
			$old_password_hash = db_user::get_password($_SESSION['id']);
			$hasher = new PasswordHash(8, FALSE);
			if ($hasher->CheckPassword($_POST['old_password'], $old_password_hash)) { // Old password correct
				$new_password_hash = $hasher->HashPassword($_POST['new_password1']);
				$ok = db_user::update_password($new_password_hash, $_SESSION['id']);
				if($ok)
					$_SESSION['report_message'] = "Lösenordet har uppdaterats"; 
			}
			else
				\Logic\util::report_error("Lösenordet var inte korrekt");
		}
	}
	elseif(isset($_POST["settings"])){
		if(!isset($_POST['show_email'])) $_POST['show_email']=0;
		if(!isset($_POST['show_telephone'])) $_POST['show_telephone']=0;
		if(!isset($_POST['show_skype'])) $_POST['show_skype']=0;
		$ok = db_user::update_settings($_POST['show_email'], $_POST['show_telephone'], $_POST['show_skype'], $_SESSION['id']);
		if($ok)
			$_SESSION['report_message'] = "Dina inställningar har uppdaterats"; 
		else
			\Logic\util::report_error("Inga inställningar ändrade"); 
	}
	elseif(isset($_POST["description_content"])){
		$presentation = Logic\text::process_text($_POST['description_content']);
		$ok = db_user::update_description($presentation, $_SESSION['id']);
		if($ok)
			$_SESSION['report_message'] = "Presentationen har uppdaterats"; 
		else
			\Logic\util::report_error("Inga ändringar utförda"); 
	}
	elseif(isset($_POST["image"])){
		$image_info = getimagesize($_FILES['image']['tmp_name']);
		if($image_info['2']==1)  // Checks that file is gif image
			$image_filename = general_helpers::GenerateRandomString(20) . ".gif";
		elseif($image_info['2']==2)  // Checks that file is jpg image
			$image_filename = general_helpers::GenerateRandomString(20) . ".jpg";
		elseif($image_info['2']==3)  // Checks that file is png image
			$image_filename = general_helpers::GenerateRandomString(20) . ".png";
		else
			\Logic\util::report_error("Fel filtyp."); 
		if(isset($image_filename)){ // Execute file upload and database update
			$image_80_width = general_helpers::resize_image($_FILES['image']['tmp_name'], 80);
			$image_150_width = general_helpers::resize_image($_FILES['image']['tmp_name'], 150);
			move_uploaded_file($_FILES['image']['tmp_name'], USERIMG_FOLDER . $image_filename);

			if($image_info['2']==1){  // if gif
				imagegif($image_80_width, USERIMG_FOLDER . 'userimg_80_width/' . $image_filename);
				imagegif($image_150_width, USERIMG_FOLDER . 'userimg_150_width/' . $image_filename);
			}
			elseif($image_info['2']==2){  // if jpg
				imagejpeg($image_80_width, USERIMG_FOLDER . 'userimg_80_width/' . $image_filename);
				imagejpeg($image_150_width, USERIMG_FOLDER . 'userimg_150_width/' . $image_filename);
			}
			elseif($image_info['2']==3){  // if png
				imagepng($image_80_width, USERIMG_FOLDER . 'userimg_80_width/' . $image_filename);
				imagepng($image_150_width, USERIMG_FOLDER . 'userimg_150_width/' . $image_filename);
			}

			$ok = db_user::update_image($image_filename, $_SESSION['id']);
			if($ok)
				$_SESSION['report_message'] = "Bilden uppdaterad"; 
		}
	}
	elseif(isset($_POST["profile"])){
		if(!filter_var($_POST['email'], FILTER_VALIDATE_EMAIL))
			\Logic\util::report_error("Det är inte en giltig mejladress"); 
		elseif(isset($_POST['first_name']) && isset($_POST['last_name']) && isset($_POST['street_address']) && isset($_POST['zip_code']) && isset($_POST['city_address']) && isset($_POST['county_id']) && isset($_POST['email'])){
			$region_id = db_constituency::get_region_id_from_county_id($_POST['county_id']);
			$ok = db_user::update_profile(general_helpers::clean($_POST['first_name']), general_helpers::clean($_POST['last_name']), general_helpers::clean($_POST['street_address']), general_helpers::clean($_POST['zip_code']), general_helpers::clean($_POST['city_address']), $_POST['county_id'], $region_id, $_POST['email'], general_helpers::clean($_POST['skype_name']), general_helpers::clean($_POST['telephone1']), general_helpers::clean($_POST['telephone2']), $_SESSION['id']);
			if($ok){
				\Logic\forum::update_county_region_forum_access($_SESSION['id'], $_POST['county_id']);
				\Logic\constituency::update_county_region_constituencies($_SESSION['id'], $_POST['county_id']);
				$_SESSION['report_message'] = "Profilen har uppdaterats";
			}
			else
				\Logic\util::report_error("Inga ändringar gjorda"); 
		}
		else
			\Logic\util::report_error("Ett eller flera obligatoriska fält är inte ifyllda"); 
	}
	elseif(isset($_POST["notice"])){
		$ok = db_notice::update_user_settings($_SESSION['id'], $_POST['view_quoting_post'], $_POST['email_quoting_post'], $_POST['view_subscribed_topic'], $_POST['email_subscribed_topic'], $_POST['view_vote_started'], $_POST['email_vote_started'], $_POST['view_vote_finished'], $_POST['email_vote_finished'], $_POST['view_proposition_created'], $_POST['email_proposition_created'], $_POST['email_message'], $_POST['email_notification_interval']);
		if($ok)
			$_SESSION['report_message'] = "Notifieringsinställningarna har uppdaterats";
		else
			\Logic\util::report_error("Inga ändringar gjorda"); 
	}
?>