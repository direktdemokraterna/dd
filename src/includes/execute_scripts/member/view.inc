<?php 

if(isset($_POST['delete_user'])){
    if (isset($_SESSION['is_member_admin'])) {
        $ok = \Logic\user::delete_user($_GET['id']);
        if($ok) {
            $_SESSION['report_message'] = "Användaren har tagits bort från medlemslistan";
        } else {
            $_SESSION['report_message'] = "Det gick inte att ta bort användaren";
        }
    } else {
        $_SESSION['report_message'] = "Du saknar behörighet att ta bort användaren";
    }

}
//elseif(isset($_POST['restore_user'])){
//	$user_data = db_user::get_user_data($_GET['id']);
//	$error = \Logic\user::validate_user($user_data['social_security_number'], $user_data['email']);
//	if ($error)
//		\Logic\util::report_error($error);
//	else {
//		$ok = \Logic\user::restore_user($_GET['id']);
//		if($ok)
//			$_SESSION['report_message'] = "Användaren har lagts till medlemslistan";
//	}
//}

?>
