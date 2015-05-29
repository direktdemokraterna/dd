<?php 
if($_POST){
	if(!filter_var($_POST['email'], FILTER_VALIDATE_EMAIL)){
		$_SESSION['report_message'] = "Mejladressen var inte korrekt.";
		$_SESSION['red_report_message'] = 1;
	}
	else{
		$region = db_helpers::get_region_from_county($_POST['county']);
		
		require("helpers/class-phpass.php");
		$random_password = general_helpers::GenerateRandomString(12);
		$hasher = new PasswordHash(8, FALSE);
		$password = $hasher->HashPassword($random_password);
		
		$insert_id = db_user::add_user($_POST['username'], $password, $_POST['first_name'], $_POST['last_name'], $_POST['street_address'], $_POST['zip_code'], $_POST['city_address'], $_POST['county'], $region, $_POST['social_security_number'], $_POST['email'], $_POST['skype_name']);
		if($insert_id){
			// Adding forum accesses for new user
			$public_forums = db_helpers::get_public_forum_ids();
			foreach($public_forums as $row){
				db_forum_admin::add_forum_access($insert_id, $row['id']);
			}
			$local_county_forum = db_helpers::get_local_county_forum($_POST['county']);
			db_forum_admin::add_forum_access($insert_id, $local_county_forum);
			$local_region_forum = db_helpers::get_local_region_forum($region);
			db_forum_admin::add_forum_access($insert_id, $local_region_forum);

			// Adding constituency access for new user
			$public_constituencies = db_constituency::get_public_constituency_ids();
			foreach($public_constituencies as $row){
				db_constituency::add_constituency_access($insert_id, $row['id']);
			}
			$local_county_constituency = db_constituency::get_local_county_constituency($_POST['county']);
			db_constituency::add_constituency_access($insert_id, $local_county_constituency);
			$local_region_constituency = db_constituency::get_local_region_constituency($region);
			db_constituency::add_constituency_access($insert_id, $local_region_constituency);

			$_SESSION['report_message'] = "Användaren är skapad. Lösenordet är: " . $random_password;
			$redirect = $_SERVER['REQUEST_URI'];
		}
	}
}

?>