<?php
namespace I18n;

class template_engine 
{
	private static $templates = null;

	public static function translate($original, $translation_hints = null) 
	{
		//echo 'translate: ' . $original . '<br>';
		$trimmed_original = trim($original);
		$phrases = translation_helper::split_phrases($trimmed_original);
		$translations = array_map(function($phrase) use ($translation_hints) {
			return self::translate_original_phrase($phrase, $translation_hints);
		}, $phrases);
		$translation = translation_helper::apply_translations($trimmed_original, $phrases, $translations);		
		return $translation;
	}

	private static function translate_original_phrase($original, $translation_hints = null)
	{
		$translation = self::translate_phrase($original, $translation_hints );
		$translation = translation_helper::preserve_case($translation, $original);
		return $translation;
	}	

	private static function translate_phrase($phrase, $translation_hints = null) 
	{
		$candidate_matches = self::get_candidate_matches($phrase, $translation_hints);
		$phrase_matches = self::combine_candidate_matches($candidate_matches);
		$template_match = self::find_best_template($phrase_matches);
		$translation = $template_match
			? $template_match->translate($translation_hints)
			: $phrase;
		return $translation;
	}

	private static function get_candidate_matches($phrase, $translation_hints = null) 
	{
		$candidate_matches = array();
		$remaining_words = null;
		do {
			$words = $remaining_words;
			$remaining_words = array();
			$candidate_match = self::get_next_candidate_match($phrase, $words, $remaining_words, $translation_hints);
			array_unshift($candidate_matches, $candidate_match);
		}
		while (count($remaining_words));
		return $candidate_matches; 
	}

	private static function get_next_candidate_match($fragment, &$words, &$remaining_words, $translation_hints) 
	{
		while (true) {
			if ($words)
				$fragment = implode(' ', $words);
			$candidates = self::match_translator($fragment, $translation_hints);
			if ($candidates) 
				return new translation_match($fragment, $candidates);
			if ($words == null)
				$words = translation_helper::split_words($fragment);
			if (count($words) == 1)
				return new translation_match($fragment, array(new untranslated($fragment)));
			$remaining_words[] = array_shift($words);
		}
	}

	private static function match_translator($fragment, $translation_hints = null) 
	{
		$candidates = translation_storage::get_translators(strtolower($fragment));
		if ($translation_hints && $candidates)
			$candidates = translation_storage::filter_translators($candidates, $translation_hints);
		return $candidates;
	}

	private static function combine_candidate_matches($candidate_matches) 
	{
		if (!$candidate_matches) return array(array());
		$first_match = array_shift($candidate_matches);
		$first_matches = $first_match->split();
		$remainder_matches = self::combine_candidate_matches($candidate_matches);
		return self::combine_matches($first_matches, $remainder_matches);
	}

	private static function combine_matches($first_matches, $remainder_matches) 
	{
		$candidates = array();
		foreach ($first_matches as $first_word_match)
			foreach ($remainder_matches as $remainder_match) {
				$candidate = array_merge(array($first_word_match), $remainder_match);
				if (self::partial_match_end($candidate))
					$candidates[] = $candidate;	
			}
		return $candidates;
	}

	private static function partial_match_end($candidate_end) {
		$templates = self::get_templates();
		foreach ($templates as $template) {
			if ($template->partial_match_end($candidate_end))
				return true;
		}
		return false;
	}

	private static function find_best_template($candidates) 
	{
		$best_template_index = -1;
		$best_template = null;
		$best_matches = null;
		foreach ($candidates as $matches) {
			$template = self::find_template($matches, $best_template_index);
			if ($template) {
				$best_template = $template;				
				$best_matches = $matches;				
			}
		}
		return $best_template
			? new template_match($best_template, $best_matches)
			: null;
	}

	private static function find_template($translator_matches, &$best_template_index) 
	{
		$templates = self::get_templates();
		$count = $best_template_index >= 0
			? $best_template_index
			: count($templates);
		for ($index = 0; $index < $count; $index++) {
			$template = $templates[$index];
			if ($template->matches($translator_matches)) {
				$best_template_index = $index;
				return $template;
			}
		}
		return null;
	}

	private static function get_templates() 
	{
		if (self::$templates == null)
			self::$templates = self::expand_templates();
		return self::$templates;
	}

	private static function expand_templates() 
	{
		$templates = array();
		$compact_templates = templates::create_templates();
		foreach ($compact_templates as $from => $to)
			$templates[] = self::expand_template($from, $to);
		return $templates;
	}

	private static function expand_template($from, $to) 
	{
		$from_pattern = self::expand_pattern($from);
		$to_pattern = self::expand_pattern($to);
		return new template($from_pattern, $to_pattern);
	}

	private static function expand_pattern($pattern) 
	{
		$word_parts = self::split_word_patterns($pattern);
		$word_forms = array_map('self::expand_word_form', $word_parts);
		return $word_forms;
	}

	private static function split_word_patterns($pattern) 
	{
		$word_parts = array();
		$word_part = '';
		foreach (str_split($pattern) as $char) {
			if (ctype_upper($char) && $word_part) {
				$word_parts[] = $word_part;
				$word_part = '';
			}
			$word_part .= $char;
		}
		$word_parts[] = $word_part;
		return $word_parts;
	}

	private static function expand_word_form($word_part) 
	{
		$class = self::expand_class($word_part[0]);
		return new word_form($class);
	}

	private static function expand_class($class_code) 
	{
		switch($class_code) {
			case 'A': return 'adj';
			case 'Q': return 'quant';
			case 'N': return 'noun';
			case 'V': return 'verb';
			case 'P': return 'prep';
			case 'D': return 'definite';
			case 'W': return null;
			default: throw new \Exception("Unknown class_code: " . $class_code);
		}
	}
}

class template_match
{
	public $template;
	public $matches;

	public function __construct($template, $matches) 
	{
		$this->template = $template;
		$this->matches = $matches;
	}

	public function translate($translation_hints = null) {
		$translated_words = $this->get_translated_parts($translation_hints);
		return implode('', $translated_words);
	}

	private function get_translated_parts($translation_hints = null) 
	{
		$translators_after = array_map(function($match) {return $match->translator;}, $this->matches);
		$translators_before = array();
		$localized_strings = array();
		foreach ($this->matches as $match) {
			$translator = array_shift($translators_after);
			$localized_strings[] = $match->translate($translators_before, $translators_after, $translation_hints);
			$translators_before[] = $translator;
		}
		return $localized_strings;
	}	
}

class template
{
	public $from_sequence;
	public $to_sequence;

	public function __construct($from_sequence, $to_sequence) 
	{
		$this->from_sequence = $from_sequence;
		$this->to_sequence = $to_sequence;
	}

	public function matches($translator_matches) 
	{
		if (count($this->from_sequence) != count($translator_matches))
			return false;
		$matches_after = $translator_matches;
		$matches_before = array();
		$localized_strings = array();
		for ($index = 0; $index < count($this->from_sequence); $index++) {
			$match = array_shift($matches_after);
			if (!$this->from_sequence[$index]->matches_in_context($match->translator
				, $matches_before, $matches_after))
				return false;			
			$matches_before[] = $match;
		}
		return true;
	}

	public function partial_match_end($candidate_end) {
		$offset = count($this->from_sequence) - count($candidate_end);
		if ($offset < 0)
			return false;
		for ($index = 0; $index < count($candidate_end); $index++)
			if (!$this->from_sequence[$index + $offset]->matches($candidate_end[$index]->translator))
				return false;
		return true;
	}
}

class word_form 
{
	public $class;

	public function __construct($class) 
	{
		$this->class = $class;
	}

	public function matches_in_context($translator, $matches_before, $matches_after) 
	{
		return $this->matches($translator) 
			&& $translator->identifier->match($matches_before, $matches_after);
	}

	public function matches($translator) 
	{
		return !$this->class || $this->class == $translator->identifier->class;
	}
}
?>
