<?php
class db_user_password_reset_token {
    public static function get_user_id($reset_token) {
        $query = "select user_id from user_password_reset_token where reset_token = ?";
        $values = Array($reset_token);
        return db::select_single_value($query, $values);
    }

    public static function add_token($user_id, $reset_token) {
        $query = "insert into user_password_reset_token (user_id, reset_token, timestamp_insertion) values (?, ?, ?)";
        $values = Array($user_id, $reset_token, time());
        return db::insert($query, $values);
    }

    public static function delete_token($user_id) {
        $query = "delete from user_password_reset_token where $user_id = ?";
        $values = Array($user_id);
        $result = db::delete($query, $values);
        return $result;
    }

    public static function delete_old_tokens() {
        $query = "delete from user_password_reset_token where timestamp_insertion < ?";
        $values = Array(time() - 24 * 60 * 60);
        $result = db::delete($query, $values);
        return $result;
    }
}