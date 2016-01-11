<?php
	if(isset($_POST["password"])){
		if($_POST['new_password1']!=$_POST['new_password2'])
			\Logic\util::report_error(_t("The new passwords didn't match")); 
		else{
			$old_password_hash = db_user::get_password($_SESSION['id']);
			$hasher = new PasswordHash(8, FALSE);
			if ($hasher->CheckPassword($_POST['old_password'], $old_password_hash)) { // Old password correct
				$new_password_hash = $hasher->HashPassword($_POST['new_password1']);
				$ok = db_user::update_password($new_password_hash, $_SESSION['id']);
				if($ok)
					$_SESSION['report_message'] = _t("The password has been updated."); 
			}
			else
				\Logic\util::report_error(_t("The password was not correct"));
		}
	}
	elseif(isset($_POST["settings"])){
		if(!isset($_POST['show_email'])) $_POST['show_email']=0;
		if(!isset($_POST['show_telephone'])) $_POST['show_telephone']=0;
		if(!isset($_POST['show_skype'])) $_POST['show_skype']=0;
		$ok = db_user::update_settings($_POST['show_email'], $_POST['show_telephone'], $_POST['show_skype'], $_SESSION['id']);
		if($ok)
			$_SESSION['report_message'] = _t("Your settings has been updated"); 
		else
			\Logic\util::report_error(_t("No settings changed")); 
	}
	elseif(isset($_POST["description_content"])){
		$presentation = forum_helpers::process_text($_POST['description_content']);
		$ok = db_user::update_description($presentation, $_SESSION['id']);
		if($ok)
			$_SESSION['report_message'] = _t("The presentation has been updated."); 
		else
			\Logic\util::report_error(_t("No changes made")); 
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
			\Logic\util::report_error(_t("Wrong file type.")); 
		if(isset($image_filename)){ // Execute file upload and database update
			move_uploaded_file($_FILES['image']['tmp_name'], USERIMG_PATH . $image_filename);
			$ok = db_user::update_image($image_filename, $_SESSION['id']);
			if($ok)
				$_SESSION['report_message'] = _t("Image updated."); 
		}
	}
	elseif(isset($_POST["profile"])){
		if(!filter_var($_POST['email'], FILTER_VALIDATE_EMAIL))
			\Logic\util::report_error(_t("the email address is invalid.")); 
		elseif(isset($_POST['first_name']) && isset($_POST['last_name']) && isset($_POST['street_address']) && isset($_POST['zip_code']) && isset($_POST['city_address']) && isset($_POST['county_id']) && isset($_POST['email'])){
			$region_id = db_constituency::get_region_id_from_county_id($_POST['county_id']);
			$ok = db_user::update_profile(general_helpers::clean($_POST['first_name']), general_helpers::clean($_POST['last_name']), general_helpers::clean($_POST['street_address']), general_helpers::clean($_POST['zip_code']), general_helpers::clean($_POST['city_address']), $_POST['county_id'], $region_id, $_POST['email'], general_helpers::clean($_POST['skype_name']), general_helpers::clean($_POST['telephone1']), general_helpers::clean($_POST['telephone2']), $_SESSION['id']);
			if($ok){
				\Logic\forum::update_county_region_forum_access($_SESSION['id'], $_POST['county_id']);
				\Logic\constituency::update_county_region_constituencies($_SESSION['id'], $_POST['county_id']);
				$_SESSION['report_message'] = _t("Your profile is updated");
			}
			else
				\Logic\util::report_error("No update made."); 
		}
		else
			\Logic\util::report_error(_t("One or more mandatory fields are not filled in.")); 
	}
?>