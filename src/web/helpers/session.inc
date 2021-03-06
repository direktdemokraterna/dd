<?php
class session 
{
	public static function update_acting_as_delegate() 
	{
		preg_match('/[\?|&]act_as_delegate=(1|0)$/', $_SERVER['REQUEST_URI'], $act_as_delegate_param_match);
		if ($act_as_delegate_param_match) {
			$param = $act_as_delegate_param_match[0];
			$act_as_delegate = $act_as_delegate_param_match[1];
			if ($act_as_delegate)
				\Logic\delegate::act_as_delegate();
			else 
				\Logic\delegate::act_as_individual();
			self::continue_to_page($param);
		}		
	}

	private static function continue_to_page($remove_param) 
	{
		$redirect = str_replace($remove_param, '', $_SERVER['REQUEST_URI']);
		header("Location: $redirect");
		exit();
	}

	public static function login_logout() {
		if(isset($_GET['logout']))
			self::destroy_session();
		elseif(self::is_session_open())
			crypt_helpers::ensure_user_code_on_client($_SESSION['id']);
		elseif(isset($_POST['login'])) {
			self::create_session();
			header("Location: " . $_SERVER['REQUEST_URI']);
			exit();
		}
		elseif(isset($_COOKIE['user_id']) && isset($_COOKIE['user_token']))
			self::restore_session();
		else
			self::destroy_session();
	}

	public static function is_session_open() 
	{
		return isset($_SESSION['id']);		
	}

	private static function restore_session() {
		$user_data = db_user::get_user_data($_COOKIE['user_id']);
		if(self::is_user_suspended($user_data)) {
			self::destroy_session();
			echo '<div class="red_message">' . "Användaren är tillfälligt avstängd." . '</div>';
			return;
		}
		$hasher = new PasswordHash(8, FALSE);
		if ($hasher->CheckPassword($_COOKIE['user_token'], $user_data['remember_me_token']))
			self::open_session($user_data);
		else
			self::destroy_session();
	}

	private static function create_session() {
		if (!isset($_POST['username']) || !isset($_POST['password'])) {
			\Logic\util::report_error("Användarnamn eller lösenord saknas.", false);
			return;
		}
		$user_data = db_user::get_user_data_from_username($_POST['username']);
		if(self::is_user_suspended($user_data)) {
			\Logic\util::report_error("Användaren är tillfälligt avstängd.", false);
			return;
		}
		$hasher = new PasswordHash(8, FALSE);
		if($hasher->CheckPassword($_POST['password'], $user_data['password']))
			self::open_session($user_data);
		else
			\Logic\util::report_error("Felaktigt användarnamn eller lösenord.", false);
	}

	private static function is_user_suspended($user_data) 
	{
		return isset($user_data['deletion_time']);
	}

	private static function open_session($user_data)
	{
		$user_id = $user_data['id'];
		$_SESSION['id'] = $user_id;
		$_SESSION['last_login_time'] = $user_data['last_login_time'];
		self::set_delegate_role($user_data);
		self::set_admin_roles($user_id);
		crypt_helpers::retrieve_user_code_on_client($user_id);
		db_user::update_last_login_time($user_id);
		if(isset($_POST['rememberme']))
			self::remember_user();
	}

	private static function set_delegate_role($user_data)
	{
		$_SESSION['delegate_id'] = $user_data['acting_as_delegate']
			? db_delegate::get_delegate_id_from_user_id($user_data['id'])
			: 0;
	}

	private static function set_admin_roles($user_id)
	{
		$admin_roles = db_admin::get_admin_roles_for_user($user_id);
		foreach($admin_roles as $row){
			$_SESSION['admin'] = 1;
			$admin_type = "is_" . $row['type'];
			$_SESSION[$admin_type] = 1;
		}
	}

	private static function remember_user() 
	{
		$random_token = general_helpers::GenerateRandomString(32);
		$hasher = new PasswordHash(8, FALSE);
		$hashed_random_token = $hasher->HashPassword($random_token);
		$ok = db_user::set_remember_me_token($hashed_random_token, $_SESSION['id']);
		if(!$ok) 
			throw new Exception("Could not store user token");
		setcookie('user_id', $_SESSION['id'], strtotime('+30 days'));
		setcookie('user_token', $random_token, strtotime('+30 days'));
	}

	private static function destroy_session() 
	{
		setcookie('user_id', '', strtotime('-30 days'));
		setcookie('user_token', '', strtotime('-30 days'));
		session_unset();
		session_destroy();
		echo "<script>sessionStorage.clear();</script>";
	}
}
?>