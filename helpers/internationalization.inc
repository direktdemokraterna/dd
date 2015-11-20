<?php
	function _li($content) {
		echo '<li>' . $content . '</li>';
	}

	function _p($text) {
		echo '<p>' . $text . '</p>';
	}

	function _strong($text) {
		echo '<strong>' . $text . '</strong>';
	}

	function _br() {
		echo '<br>';
	}

	function __($text) {
		echo _t($text);
	}

	function _h1($text) {
		echo '<h1>' . _t($text) . '</h1>';
	}

	function _h2($text) {
		echo '<h2>' . _t($text) . '</h2>';
	}

	function _t($text) {
		return internationalization::translate($text);
	}

	class internationalization 
	{
		private static $translations = null;

		public static function translate($text) 
		{
			$phrases = preg_split('/\s*[[:punct:]]+\s*/', $text, -1, PREG_SPLIT_NO_EMPTY);
			$translations = array_map('self::translate_original_phrase', $phrases);
			for ($i = 0; $i < count($phrases); $i++)
				$text = str_replace($phrases[$i], $translations[$i], $text);
			return $text;
		}

		private static function translate_original_phrase($original_phrase) 
		{
			preg_match_all('/\d+/', $original_phrase, $matches);
			if (!$matches[0]) 
				return self::translate_phrase($original_phrase);
			$phrase = preg_replace('/\d+/', '%d', $original_phrase);
			$translated_phrase = self::translate_phrase($phrase);
			foreach ($matches[0] as $number)
				$translated_phrase = str_replace('%d', $number, $translated_phrase);
			return $translated_phrase;
		}

		private static function translate_phrase($phrase) 
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
			$identifier = translation_identifier::create($key);
			self::$translations[$identifier->key] = new translator($identifier, $translation);
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
					return new translation_match($phrase, $translation);
				if ($words == null)
					$words = preg_split('/\s+/', $phrase, 0, PREG_SPLIT_NO_EMPTY);
				if (count($words) == 1)
					return new translation_match($phrase, $translation);
				$remaining_words[] = array_shift($words);
			}
		}

		private static function match_phrase($phrase) 
		{
			$translation = self::get_translation(strtolower($phrase));
			return $translation ? $translation : new untranslated($phrase);
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
			foreach (array_keys($compact_translations) as $key)
				self::expand_translation($translations, $key, $compact_translations[$key]);
			return $translations;
		}

		private static function expand_translation(&$translations, $identifier_str, $compact_translation) 
		{
			$identifier = translation_identifier::create($identifier_str);
			$new_translations = self::get_expanded_translations($identifier, $compact_translation);
			foreach ($new_translations as $translation)
				$translations[$translation->identifier->key] = $translation;
		}

		private static function get_expanded_translations($identifier, $compact_translation) 
		{
			switch ($identifier->class) {
				case 'phrase':
					yield new translator($identifier, $compact_translation[LANG]);
					break;
				case 'adj':
					yield new adjective($identifier, $compact_translation[LANG]);
					break;
				case 'noun':
					yield new noun_singular($identifier, $compact_translation);
					yield new noun_plural($identifier, $compact_translation);
					break;
				case 'verb':
					$verb_infinitive = new verb_infinitive($identifier, $compact_translation);
					yield $verb_infinitive;
					if ($verb_infinitive->has_perfect_participle)
						yield new verb_perfect_participle($identifier, $compact_translation);
					break;
				default:
					throw new Exception("Unknown word class: " . $word_type);
			}
		}
	}

	class translation_identifier 
	{
		public $key;
		public $class;
		public $type;

		public static function create($identifier_str) 
		{

			$parts = explode(':', $identifier_str);
			$category = count($parts) == 2 ? $parts[1] : 'phrase';
			$key = $parts[0];
			preg_match('/\d+/', $category, $matches);
			return $matches
				? new translation_identifier($key, str_replace($matches[0], '', $category), (int)$matches[0])
				: new translation_identifier($key, $category, 1);
		}

		public function copy($new_key) 
		{
			return new translation_identifier($new_key, $this->class, $this->type);
		}

		function __construct($key, $class, $type = 1) 
		{
			$this->key = $key;
			$this->class = $class;
			$this->type = $type;	
		}
	}

	class translation_match
	{
		public $phrase;
		public $translation;

		function __construct($phrase, $translation) 
		{
			$this->phrase = $phrase;
			$this->translation = $translation;
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

		function construct($phrase) 
		{
			$this->phrase = $phrase;
		}

		public function translate($lower_phrase, $remaining_translation_matches) 
		{
			return $this->phrase;
		}
	}

	class translator {
		public $identifier;		
		public $translation;

		function __construct($identifier, $translation) {
			$this->identifier = $identifier;
			$this->translation = $translation;
		}

		public function translate($lower_phrase, $remaining_translation_matches) 
		{
			if ($lower_phrase != $this->identifier->key)
				throw new Exception("mismatched translation: " . $lower_phrase . " != " . $this->identifier->key);
			return $this->do_translate($lower_phrase, $remaining_translation_matches);
		}

		protected function do_translate($lower_phrase, $remaining_translation_matches) 
		{
			return $this->translation;
		}

		protected static function create_word_form($base_form, $ending) 
		{
			$suffix = str_replace('_', '', $ending);
			$del_char_count = strlen($ending) - strlen($suffix);
			$word_stem = substr($base_form, 0, strlen($base_form) - $del_char_count);
			return $word_stem . $suffix;
		}

		protected static function strip_parenthesis($text_in_parenthesis) 
		{
			return substr($text_in_parenthesis, 1, strlen($text_in_parenthesis) - 2);
		}
	}

	class adjective extends translator
	{
		public $translation_noun2;
		public $translation_plural;

		function __construct($identifier, $compact_translation) 
		{
			$parts = explode(':', $compact_translation);
			$singular_parts = explode('|', $parts[0]);
			$singular = $singular_parts[0];
			$alt_singular_ending = $singular_parts[1];
			$plural_ending = $parts[1];
			parent::__construct($identifier, $singular);
			$this->translation_noun2 = parent::create_word_form($singular
				, $alt_singular_ending);
			$this->translation_plural = parent::create_word_form($singular, $plural_ending);
		}

		protected function do_translate($lower_phrase, $remaining_translation_matches) 
		{
			$significant_noun = self::get_significant_noun($remaining_translation_matches);
			if ($significant_noun == null)
				return $this->translation;
			if (get_class($significant_noun) == 'noun_plural')
				return $this->translation_plural;
			if (get_class($significant_noun) == 'noun_singular') {
				if ($significant_noun->identifier->type == 1)
					return $this->translation;
				if ($significant_noun->identifier->type == 2)
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

	class noun_singular extends translator 
	{
		function __construct($identifier, $compact_translation) 
		{
			$translation = self::get_singular($compact_translation[LANG]);
			parent::__construct($identifier, $translation);
		}

		private static function get_singular($compact_translation) 
		{
			return explode(':', $compact_translation)[0];
		}
	}

	class noun_plural extends translator 
	{
		function __construct($identifier, $compact_translation) 
		{
			$translation = self::get_plural($compact_translation[LANG]);
			$plural_key = self::get_plural($compact_translation[BASE_LANG]);
			parent::__construct($identifier->copy($plural_key), $translation);
		}

		private static function get_plural($compact_translation) 
		{
			$parts = explode(':', $compact_translation);
			if (count($parts) == 1)
				return $compact_translation;
			return parent::create_word_form($parts[0], $parts[1]);
		}
	}

	class verb_infinitive extends translator 
	{
		public $has_perfect_participle;

		function __construct($identifier, $compact_translation) 
		{
			$translation = self::get_infinitive($compact_translation[LANG]);
			$this->has_perfect_participle = ($translation != $compact_translation[LANG]);
			parent::__construct($identifier, $translation);
		}

		private static function get_infinitive($compact_translation) 
		{
			$parts = explode(':', $compact_translation);
			return $parts[0];
		}
	}

	class verb_perfect_participle extends adjective
	{
		function __construct($identifier, $compact_translation) 
		{
			$base_parts = explode(':', $compact_translation[BASE_LANG]);
			$adjective_key = parent::create_word_form($base_parts[0], $base_parts[1]);
			$adjective_compact_translation = self::make_adjective_compact_translation($compact_translation);
			parent::__construct(new translation_identifier($adjective_key, 'adj'),
				$adjective_compact_translation);
		}

		private static function make_adjective_compact_translation($verb_compact_translation) {
			$verb_base_form_and_endings = explode(':', $verb_compact_translation[LANG], 2);
			$verb_base_form = $verb_base_form_and_endings[0];
			$perfect_participle_endings = parent::strip_parenthesis($verb_base_form_and_endings[1]);
			$adjective_compact_translation = self::replace_adjective_suffix_with_base_form($verb_base_form, $perfect_participle_endings);
			return $adjective_compact_translation;
		}

		private static function replace_adjective_suffix_with_base_form($verb_base_form, 
			$perfect_participle_endings) {
			$adjective_suffix_and_endings = explode('|', $perfect_participle_endings);
			$adjective_suffix = $adjective_suffix_and_endings[0];
			$adjective_endings = $adjective_suffix_and_endings[1];
			$adjective_base_form = parent::create_word_form($verb_base_form, $adjective_suffix);
			$adjective_compact_translation = implode('|', array($adjective_base_form, $adjective_endings));
			return $adjective_compact_translation;
		}
	}
?>
