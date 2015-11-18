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

		public static function translate_phrase($phrase) 
		{
			$translation_matches = self::get_translation_matches($phrase);
			if (count($translation_matches) == 1)
				return $translation_matches[0]->translate(array());
			$localized_strings = array();
			$remaining_translation_matches = $translation_matches;
			while ($remaining_translation_matches) {
				$translation_match = array_shift($remaining_translation_matches);
				$localized_strings[] = $translation_match->translate($remaining_translation_matches);
			}
			$translated_phrase = implode(' ', $localized_strings);
			self::store_new_translation($phrase, $translated_phrase);
			return $translated_phrase;
		}

		private static function store_new_translation($phrase, $translated_phrase) 
		{
			$key = strtolower($phrase);
			$translation = strtolower($translated_phrase);
			self::$translations[$key] = phrase::create($key, $translation);
		}

		private static function get_translation_matches($phrase) 
		{
			$translation_matches = array();
			$remaining_words = null;
			do {
				$words = $remaining_words;
				$remaining_words = array();
				$translation_match = self::get_translation_match($phrase, $words, $remaining_words);
				array_unshift($translation_matches, $translation_match);
			}
			while (count($remaining_words));
			return $translation_matches; 
		}

		private static function get_translation_match($phrase, &$words, &$remaining_words) 
		{
			while (true) {
				if ($words)
					$phrase = implode(' ', $words);
				$translation = self::match_phrase($phrase);
				if (is_string($translation)) {
					throw new Exception($translation);
				}
				if (get_class($translation) != 'untranslated') 
					return translation_match::create($phrase, $translation);
				if ($words == null)
					$words = preg_split('/\s+/', $phrase, 0, PREG_SPLIT_NO_EMPTY);
				if (count($words) == 1)
					return translation_match::create($phrase, $translation);
				$remaining_words[] = array_shift($words);
			}
		}

		private static function match_phrase($phrase) 
		{
			$translation = self::get_translation(strtolower($phrase));
			return $translation 
				? $translation
				: untranslated::create($phrase);
		}

		private static function get_translation($phrase_lower) 
		{
			self::init_translations();
			return isset(self::$translations[$phrase_lower]) 
				? self::$translations[$phrase_lower] 
				: null;
		}

		private static function init_translations() 
		{
			if (self::$translations == null)
				self::$translations = self::expand_translations(translations::create_translations());
		}

		private static function expand_translations($compact_translations) 
		{
			$translations = array();
			foreach (array_keys($compact_translations) as $key) {
				$parts = explode(':', $key);
				self::expand_translation($translations, count($parts) == 2 ? $parts[1] : 'phrase'
					, $parts[0], $compact_translations[$key]);
			}
			return $translations;
		}

		private static function expand_translation(&$translations, $word_type, $key, $compact_translation) 
		{
			$new_translations = self::get_expanded_translations($word_type, $key, $compact_translation);
			foreach ($new_translations as $translation)
				$translations[$translation->key] = $translation;
		}

		private static function get_expanded_translations($word_type, $key, $compact_translation) 
		{
			switch ($word_type) {
				case 'phrase':
				case 'verb':
					yield phrase::create($key, $compact_translation[LANG]);
					break;
				case 'adj':
					yield adjective::create($key, $compact_translation[LANG]);
					break;
				case 'noun1':
					yield noun_singular::create($key, $compact_translation, 1);
					yield noun_plural::create($key, $compact_translation);
					break;
				case 'noun2':
					yield noun_singular::create($key, $compact_translation, 2);
					yield noun_plural::create($key, $compact_translation);
					break;
				default:
					throw new Exception("Unknown word class: " . $parts[1]);
			}
		}
	}

	class translation_match
	{
		public $phrase;
		public $translation;

		public static function create($phrase, $translation) 
		{
			$translation_match = new translation_match();
			$translation_match->phrase = $phrase;
			$translation_match->translation = $translation;
			return $translation_match;
		}

		public function translate($remaining_translation_matches) 
		{
			$lower_translation = $this->translation->translate(strtolower($this->phrase), $remaining_translation_matches);
			return self::match_case($lower_translation, $this->phrase);
		}

		private static function match_case($target, $template) 
		{
			return (ctype_upper($template[0]) 
					? strtoupper($target[0]) 
					: strtolower($target[0]))
			. substr($target, 1);
		}		
	}

	class untranslated 
	{
		public $phrase;

		public static function create($phrase) 
		{
			$untranslated = new untranslated();
			$untranslated->phrase = $phrase;
			return $untranslated;
		}

		public function translate($lower_phrase, $remaining_translation_matches) 
		{
			return $this->phrase;
		}
	}

	class phrase 
	{
		public $key;
		public $translation;

		public static function create($key, $translation) 
		{
			$phrase = new phrase();
			$phrase->key = $key;
			$phrase->translation = $translation;
			return $phrase;
		}

		public function translate($lower_phrase, $remaining_translation_matches) 
		{
			if ($lower_phrase == $this->key) return $this->translation;
			throw new Exception("mismatched translation: " . $lower_phrase . " != " . $this->key);
		}
	}

	class adjective 
	{
		public $key;
		public $translation_noun1;
		public $translation_noun2;
		public $translation_plural;

		public static function create($key, $compact_translation) 
		{
			$adjective = new adjective();
			$adjective->key = $key;
			$parts = explode(':', $compact_translation);
			$singular_parts = explode('|', $parts[0]);
			$singular = $singular_parts[0];
			$alt_singular_ending = $singular_parts[1];
			$plural_ending = $parts[1];
			$adjective->translation_noun1 = $singular;
			$adjective->translation_noun2 = word_helper::create_word_form($singular
				, $alt_singular_ending);
			$adjective->translation_plural = word_helper::create_word_form($singular, $plural_ending);
			return $adjective;
		}

		public function translate($lower_phrase, $remaining_translation_matches) 
		{
			if ($lower_phrase != $this->key)
			throw new Exception("mismatched translation: " . $lower_phrase . " != " . $this->key);
			$significant_noun = self::get_significant_noun($remaining_translation_matches);
			if ($significant_noun == null)
				return $this->translation_noun1;
			if (get_class($significant_noun) == 'noun_plural')
				return $this->translation_plural;
			if (get_class($significant_noun) == 'noun_singular') {
				if ($significant_noun->type == 1)
					return $this->translation_noun1;
				if ($significant_noun->type == 2)
					return $this->translation_noun2;
				throw new Exception('Invalid noun type: ' . $significant_noun->type);
			}
			throw new Exception('Invalid word class: ' . get_class($significant_noun));
		}

		private static function get_significant_noun($remaining_translation_matches) 
		{
			$found_noun = null;
			foreach ($remaining_translation_matches as $next_translation_match) {
				if (self::is_noun($next_translation_match->translation))
					$found_noun = $next_translation_match->translation;
				else if ($found_noun)
					return $found_noun; 
			}
			return $found_noun;
		}

		private static function is_noun($translation) 
		{
			return in_array(get_class($translation), array('noun_singular', 'noun_plural'));
		}
	}

	class noun_singular 
	{
		public $key;
		public $translation;
		public $type;

		public static function create($key, $compact_translation, $type) 
		{
			$noun_singular = new noun_singular();
			$noun_singular->type = $type;
			$noun_singular->key = self::get_singular($compact_translation[BASE_LANG]);
			$noun_singular->translation = self::get_singular($compact_translation[LANG]);
			return $noun_singular;
		}

		public function translate($lower_phrase, $remaining_translation_matches) 
		{
			if ($lower_phrase == $this->key) return $this->translation;
			throw new Exception("mismatched translation: " . $lower_phrase . " != " . $this->key);
		}

		private static function get_singular($compact_translation) 
		{
			$parts = explode(':', $compact_translation);
			return $parts[0];
		}
	}

	class noun_plural 
	{
		public $key;
		public $translation;

		public static function create($key, $compact_translation) 
		{
			$noun_plural = new noun_plural();
			$noun_plural->key = self::get_plural($compact_translation[BASE_LANG]);
			$noun_plural->translation = self::get_plural($compact_translation[LANG]);
			return $noun_plural;
		}

		public function translate($lower_phrase, $remaining_translation_matches) 
		{
			if ($lower_phrase == $this->key) return $this->translation;
			throw new Exception("mismatched translation: " . $lower_phrase . " != " . $this->key);
		}

		private static function get_plural($compact_translation) 
		{
			$parts = explode(':', $compact_translation);
			if (count($parts) == 1)
				return $compact_translation;
			return word_helper::create_word_form($parts[0], $parts[1]);
		}
	}

	class word_helper 
	{
		public static function create_word_form($base_form, $ending) 
		{
			$suffix = str_replace('_', '', $ending);
			$del_char_count = strlen($ending) - strlen($suffix);
			$word_stem = substr($base_form, 0, strlen($base_form) - $del_char_count);
			return $word_stem . $suffix;
		}
	}
?>
