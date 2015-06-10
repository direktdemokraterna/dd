<?php

if(!isset($_SESSION['id'])){

	require("helpers/class-phpass.php");
	$hasher = new PasswordHash(8, FALSE);

	if(isset($_COOKIE['user_id']) && isset($_COOKIE['user_token'])){
		$user_data = db_user::get_user_data($_COOKIE['user_id']);

		if ($hasher->CheckPassword($_COOKIE['user_token'], $user_data['remember_me_token'])) { // Cookie matches db token
			$_SESSION['id'] = $user_data['id'];
			$_SESSION['last_login_time'] = $user_data['last_login_time'];
			$_SESSION['acting_as_delegate'] = $user_data['acting_as_delegate'];
			$admin_roles = db_admin::get_admin_roles_for_user($user_data['id']);
			$counter = 0;
			foreach($admin_roles as $row){
				$admin_type = "is_" . $row['type'];
				$_SESSION[$admin_type] = 1;
				$counter++;
			}
			if($counter>0){
				$_SESSION['admin'] = 1;
			}
			crypt_helpers::send_user_codes_to_user($user_data['id']);
			db_user::update_last_login_time($_SESSION['id']);

			$random_token = general_helpers::GenerateRandomString(32);
			$hasher = new PasswordHash(8, FALSE);
			$hashed_random_token = $hasher->HashPassword($random_token);
			$ok = db_user::set_remember_me_token($hashed_random_token, $_SESSION['id']);
			if($ok){
				setcookie('user_id', $_SESSION['id'], strtotime('+30 days'));
				setcookie('user_token', $random_token, strtotime('+30 days'));
			}
		}
	}

	if(isset($_POST['login'])){
		if(isset($_POST['username']) && isset($_POST['password'])){
			$user_data = db_user::get_user_data_from_username($_POST['username']);

			if ($hasher->CheckPassword($_POST['password'], $user_data['password'])) { // Password is correct
				$_SESSION['id'] = $user_data['id'];
				$_SESSION['last_login_time'] = $user_data['last_login_time'];
				$_SESSION['acting_as_delegate'] = $user_data['acting_as_delegate'];
				$admin_roles = db_admin::get_admin_roles_for_user($user_data['id']);
				$counter = 0;
				foreach($admin_roles as $row){
					$admin_type = "is_" . $row['type'];
					$_SESSION[$admin_type] = 1;
					$counter++;
				}
				if($counter>0){
					$_SESSION['admin'] = 1;
				}
				crypt_helpers::send_user_codes_to_user($user_data['id']);
				db_user::update_last_login_time($_SESSION['id']);

				if(isset($_POST['rememberme'])){
					$random_token = general_helpers::GenerateRandomString(32);
					$hasher = new PasswordHash(8, FALSE);
					$hashed_random_token = $hasher->HashPassword($random_token);
					$ok = db_user::set_remember_me_token($hashed_random_token, $_SESSION['id']);
					if($ok){
						setcookie('user_id', $_SESSION['id'], strtotime('+30 days'));
						setcookie('user_token', $random_token, strtotime('+30 days'));
					}
				}
			}
			else{ // Password is incorrect
				echo "<div class=\"red_message\">Lösenordet var inte korrekt</div>";
			}
		}
	}
}

else{
	if(isset($_GET['logout'])){
		setcookie('user_id', '', strtotime('-30 days'));
		setcookie('user_token', '', strtotime('-30 days'));

		session_unset();
		session_destroy();

		echo "<script>sessionStorage.clear();</script>";
	}
}

?>