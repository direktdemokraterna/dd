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
			$atoms = self::get_atoms($phrase);
			$translated_atoms = array_map("self::translate", $atoms);
			return implode(' ', $translated_atoms);
		}

		private static function translate($atom) {
			$translation = self::get_translation(strtolower($atom));
			return $translation && isset($translation[LANG]) 
				? self::match_case($translation[LANG], $atom) 
				: $atom;
		}

		private static function match_case($target, $template) {
			return (ctype_upper($template[0]) 
					? strtoupper($target[0]) 
					: strtolower($target[0]))
			. substr($target, 1);
		}

		private static function get_atoms($phrase) {
			$sub_phrases = explode(':', $phrase);
			if (count($sub_phrases) == 1)
				return $sub_phrases;
			$atoms = array();
			if ($sub_phrases[0])
				$atoms[] = $sub_phrases[0];
			foreach (array_slice($sub_phrases, 1) as $sub_phrase) {
				$sub_atoms = preg_split('/\s+/', $sub_phrase, 2, PREG_SPLIT_NO_EMPTY);
				$atoms = array_merge($atoms, $sub_atoms);
			}
			return $atoms;
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
