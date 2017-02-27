<?php
namespace Logic;

class resetpassword {
    public static function send_reset_token($email) {
        $user_id = \db_user::get_user_id_from_email($email);
        if ($user_id) {
            $username = \db_user::get_username($user_id);
            \db_user_password_reset_token::delete_token($user_id);
            $reset_token = $random_password = \general_helpers::GenerateRandomString(20);
            \db_user_password_reset_token::add_token($user_id, $reset_token);

            $mail_title = "Återställ ditt lösenord i Direktdemokraternas nya medlemssystem";
            $mail_content = "Detta mejl skickas till dig eftersom du begärt att få en återställningskod för att kunna byta ditt lösenord.\n" .
				"Ditt användarnamn är " . $username . "\n\n" .
                "Klicka på nedanstående länk för att komma till återställningssidan:\n" .
				BASE_URL . "aterstall-losenord/?reset_token=" . $reset_token;

            $mail_status = \general_helpers::admin_mail($email, $mail_title, $mail_content);
            return $mail_status;
        }
        return false;
    }

    public static function is_valid_reset_token($reset_token) {
        return !!self::get_user_name_from_valid_reset_token($reset_token);
    }

    public static function change_password($reset_token, $password) {
        if (strlen($password) < 8) {
            return false;
        }
        $user_id = self::get_user_name_from_valid_reset_token($reset_token);
        if (!$user_id) {
            return false;
        }
        \db_user_password_reset_token::delete_token($user_id);
        $hasher = new \PasswordHash(8, FALSE);
        $password_hash = $hasher->HashPassword($password);
        return \db_user::update_password($password_hash, $user_id);
    }

    private static function get_user_name_from_valid_reset_token($reset_token) {
        \db_user_password_reset_token::delete_old_tokens();
        return \db_user_password_reset_token::get_user_id($reset_token);
    }
}
?>