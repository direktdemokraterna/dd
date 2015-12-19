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
			: LANG;
	}

	private static function set_language($lang) {
		$_SESSION['lang'] = $lang;
	}
}
?>
