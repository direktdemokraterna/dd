<?php
namespace I18n;

class controller
{
	public static function update_language($lang) {
		if ($lang == self::get_language())
			return false;
		self::set_language($lang);
		return true;
	}

	public static function get_language() {
		return isset($_SESSION['lang'])
			? $_SESSION['lang']
			: (isset($_COOKIE['lang']) ? $_COOKIE['lang'] : LANG);
	}

	private static function set_language($lang) {
		if (\session::is_session_open())
			$_SESSION['lang'] = $lang;
		else setcookie('lang', $lang, strtotime('+30 days'));
	}
}
?>
