<?php
	function __($phrase) {
		echo _t($phrase);
	}

	function _h1($phrase) {
		echo '<h1>' . _t($phrase) . '</h1>';
	}

	function _h2($phrase) {
		echo '<h2>' . _t($phrase) . '</h2>';
	}

	function _t($phrase) {
		return internationalization::translate_phrase($phrase);
	}

	class internationalization 
	{
		private static $translations = null;

		public static function translate_phrase($phrase) {
			$translation = self::get_translation($phrase);
			return $translation && isset($translation[LANG]) 
				? $translation[LANG] 
				: $phrase;
		}

		private static function get_translation($phrase) {
			self::init_translations();
			return isset(self::$translations[$phrase]) 
				? self::$translations[$phrase] 
				: null;
		}

		private static function init_translations() {
			if (self::$translations == null)
				self::$translations = translations::create_translations();
		}	
	} 
?>
