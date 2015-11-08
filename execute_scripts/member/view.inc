<?php 

if(isset($_POST['delete_user'])){
	$ok = db_member_admin::delete_user($_GET['id']);
	if($ok)
		$_SESSION['report_message'] = "Användaren är borttagen ur medlemslistan";
}
elseif(isset($_POST['restore_user'])){
	$user_data = db_user::get_user_data($_GET['id']);
	$error = \Logic\user::validate_user($user_data['social_security_number'], $user_data['email']);
	if ($error)
		\Logic\util::report_error($error);
	else {
		$ok = db_member_admin::restore_user($_GET['id']);
		if($ok)
			$_SESSION['report_message'] = "Användaren har återställts i medlemslistan";
	}
}

?>